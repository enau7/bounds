#include <cmath>
#include "face.h"

void Face::set(double coords[3][3]){
    // Sets the coords:
    for (int k = 0; k < 3; k++){
        for (int j = 0; j < 3; j++){
            points[k][j] = coords[k][j];
        }
    }
    // Initializes X, Y, and Z projections of the face:
    tri_x.set(points[0][1],points[0][2],
              points[1][1],points[1][2],
              points[2][1],points[2][2]);
    tri_y.set(points[0][0],points[0][2],
              points[1][0],points[1][2],
              points[2][0],points[2][2]);
    tri_z.set(points[0][0],points[0][1],
              points[1][0],points[1][1],
              points[2][0],points[2][1]);
}

void Face::get_point(double output[3][3]){
    for (int k = 0; k < 3; k++){
        for (int j = 0; j < 3; j++){
            output[k][j] = points[k][j];
        }
    }
    return;
}

void Face::cross_prod(double vector_a[3], double vector_b[3], double output[3]){
    output[0] = vector_a[1]*vector_b[2] - vector_a[2]*vector_b[1];
    output[1] = vector_a[2]*vector_b[0] - vector_a[0]*vector_b[2];
    output[2] = vector_a[0]*vector_b[1] - vector_a[1]*vector_b[0];
}

double Face::dot_prod(double vector_a[3],double vector_b[3]){
    double sum = 0;
    for (int k = 0; k < 3; k++){
        sum += vector_a[k]*vector_b[k];
    }
    return sum;
}

bool Face::find_intersection(double point_a[3],double point_b[3],double output[3]){
    /*
        Checks where the line segment AB intersects the plane. Parallel within the plane does not count as an intersection.
        @point_a given point A
        @point_b given point B
        @output the output point
    */

    // https://en.wikipedia.org/wiki/Line%E2%80%93plane_intersection
    
    // Diff vector:
    double diff[3] = {point_a[0] - points[0][0], point_a[1] - points[0][1], point_a[2] - points[0][2]};
    // Find three vectors:
    double vector_a[3] = {points[1][0] - points[0][0], points[1][1] - points[0][1], points[1][2] - points[0][2]};
    double vector_b[3] = {points[2][0] - points[0][0], points[2][1] - points[0][1], points[2][2] - points[0][2]};
    double point_vector[3] = {point_b[0] - point_a[0], point_b[1] - point_a[1], point_b[2] - point_a[2]};
    // Find t;
    double tx[3]; cross_prod(vector_a,vector_b,tx);
    double t = dot_prod(tx,diff) / dot_prod(point_vector,tx);
    // Find where AB intersects the plane:
    for (int k = 0; k < 3; k++){
        output[k] = point_a[k] - point_vector[k]*t;
    };

    // Check if point lies outside the segment between A and B:
    for (int k = 0; k < 3; k++){
        if ((output[k] < point_a[k] && output[k] < point_b[k]) ||
            (output[k] > point_a[k] && output[k] > point_b[k])) {
                    return false;
        };
    };
    return true;
}

bool Face::intersects(double point_a[3],double point_b[3],double output[3]){
    /*
        Checks if the line segment AB intersects the face. Parallel within the plane does not count as an intersection.
        @point_a given point A
        @point_b given point B
        @output the output point
    */
    
    if (!find_intersection(point_a,point_b,output)) {return false;};
    
    // Check if point lies inside the projection of the face onto the YZ,XZ,and XY planes:
    if (tri_x.contains(output[1],output[2]) && 
        tri_y.contains(output[0],output[2]) &&
        tri_z.contains(output[0],output[1])){
            return true;
        }
    return false;
}