# Created by the script cgal_create_cmake_script
# This is the CMake script for compiling a CGAL application.
# CGAL corefinement_polyhedron_union

cmake_minimum_required(VERSION 3.1...3.22)
project(CGAL_Corefine_Excerise)

list(APPEND CMAKE_PREFIX_PATH )
set(CGAL_DATA_DIR "C:/dev/CGAL_Maschining/data")
# CGAL and its components
find_package(CGAL REQUIRED OPTIONAL_COMPONENTS Qt5)

# Boost and its components
find_package(Boost REQUIRED)

if(NOT Boost_FOUND)

  message(
    STATUS "This project requires the Boost library, and will not be compiled.")

  return()

endif()

find_package(OpenMesh QUIET)

if(OpenMesh_FOUND)
  include(UseOpenMesh)
else()
  message(STATUS "Examples that use OpenMesh will not be compiled.")
endif()

# include for local directory

# include for local package
find_package(Eigen3 3.2.0) #(requires 3.2.0 or greater)
include(CGAL_Eigen3_support)

# create a target per cppfile
file(
  GLOB cppfiles
  RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
foreach(cppfile ${cppfiles})
  create_single_source_cgal_program("${cppfile}")
endforeach()


find_package(METIS)
include(CGAL_METIS_support)
if(TARGET CGAL::METIS_support)
  target_link_libraries(hausdorff_bounded_error_distance_example PUBLIC CGAL::METIS_support)
else()
  message(STATUS "Tests, which use the METIS library will not be compiled.")
endif()


find_package(Ceres QUIET)
include(CGAL_Ceres_support)
if(TARGET CGAL::Ceres_support)
  target_link_libraries(mesh_smoothing_example PUBLIC CGAL::Ceres_support)
endif(TARGET CGAL::Ceres_support)


if(CGAL_Qt5_FOUND)
  target_link_libraries(corefinement_polyhedron_union PUBLIC CGAL::CGAL_Basic_viewer)
endif()

