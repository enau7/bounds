// Create a class that is a collection of 3d faces, like an STL.
// Pick a point that is definitely inside the mesh. Assume the mesh is enclosed.
// Draw a line between a specified point and the "definite" point.
// Count how many times that line intersects the faces. Project triangle onto plane to create face.
// If the number of times is odd, the point is inside the mesh. If the number is even, the point is outside the mesh.
#pragma once
#include <vector>
#include <cmath>
#include "face.h"

class Mesh{
    private:
        std::vector<Face> faces;
        double outside_point[3];
        void calibrate_outside_point();
        int vec_find(std::vector<std::vector<double>> vec, double point[3]);
        struct edge;
        bool edge_equality(edge edge_a, edge edge_b);
        void cross_prod(double vector_a[3], double vector_b[3], double output[3]);
        void unitize(double vector_a[3]);
        bool is_tangent(Face face_a, Face face_b,double vector_a[3]);

    public:
        void append(Face f) {faces.push_back(f); calibrate_outside_point();};
        void scale(double x);
        bool is_enclosed();
        bool contains(double point[3]);
        bool contains(double x, double y, double z){double point[3] = {x,y,z}; return contains(point);};
};
