#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Aff_transformation_3.h>

#include <CGAL/Polyhedron_3.h>
#include <CGAL/Polyhedron_items_with_id_3.h>
#include <CGAL/Polygon_mesh_processing/corefinement.h>
#include <CGAL/Polygon_mesh_processing/IO/polygon_mesh_io.h>
#include <CGAL/Polygon_mesh_processing/transform.h>

#include <fstream>
#include <iostream>

using Kernel = CGAL::Exact_predicates_inexact_constructions_kernel;
using Vector_3 = typename Kernel::Vector_3;

using K = CGAL::Exact_predicates_inexact_constructions_kernel;
using Mesh = CGAL::Polyhedron_3<K, CGAL::Polyhedron_items_with_id_3>;
using Affine_transformation_3 = CGAL::Aff_transformation_3<Kernel>;

namespace PMP = CGAL::Polygon_mesh_processing;

int main(int argc, char* argv[])
{

    const std::string Tool = (argc > 1) ? argv[1] : CGAL::data_file_path("Cylinder6.off");
    const std::string Workpiece = (argc > 2) ? argv[2] : CGAL::data_file_path("VB56.off");

    Mesh mesh_Tool, meshWorkpiece;
    if (!PMP::IO::read_polygon_mesh(Tool, mesh_Tool) || !PMP::IO::read_polygon_mesh(Workpiece, meshWorkpiece))
    {
        std::cerr << "Invalid input." << std::endl;
        return 1;
    }

    for (int step = 1; step <= 3; step++) {
        PMP::transform(Affine_transformation_3(CGAL::Translation(), Vector_3(0, 0, -1)), mesh_Tool);
        PMP::corefine_and_compute_difference(meshWorkpiece, mesh_Tool, meshWorkpiece);
    }

    // output file
    std::cout << "Union was successfully computed\n";
    std::ofstream output("NewWorkpiece.off");
    output.precision(17);
    output << meshWorkpiece;
    return 0;

}
