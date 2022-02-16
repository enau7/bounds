#pragma once
#include "triangle.h"

class Face{
    private:
        double points[3][3]; //[number of points][dimention]

        Triangle tri_x;
        Triangle tri_y;
        Triangle tri_z;
        
        void cross_prod(double vector_a[3], double vector_b[3], double output[3]);
        double dot_prod(double vector_a[3], double vector_b[3]);
    
    public:
        bool find_intersection(double point_a[3],double point_b[3],double output[3]);
        bool find_intersection(double point_a[3],double point_b[3]) {double output[3]; return find_intersection(point_a,point_b,output);};

        bool intersects(double point_a[3],double point_b[3],double output[3]);
        bool intersects(double point_a[3],double point_b[3]){double output[3]; return intersects(point_a,point_b,output);};

        void set(double coords[3][3]);

        void get_point(double output[3][3]);
        double get(int j, int k){return points[j][k];};

        Face(double coords[3][3]) {set(coords);};
        Face(double x1, double y1, double z1, double x2, double y2, double z2, double x3, double y3, double z3) {double coords[3][3] = {{x1,y1,z1},{x2,y2,z2},{x3,y3,z3}}; set(coords);};
};