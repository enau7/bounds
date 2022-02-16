#include <algorithm>
#include <vector>
#include <string>
#include <cmath>
#include "mesh.h"
#include <iostream>
using namespace std;

void Mesh::calibrate_outside_point(){
    if (!faces.size()){return;}
    double max_point[3] = {faces[0].get(0,0),faces[0].get(0,1),faces[0].get(0,2)};
    double check;
    for (int n = 1; n < faces.size(); n++){
        for (int j = 0; j < 3; j++){
            for (int k = 0; k < 3; k++){
                check = faces[n].get(j,k);
                if (check > max_point[k]){
                    max_point[k] = check;
                }
            }
        }
    }
    for (int k = 0; k < 3; k++){
        outside_point[k] = max_point[k] + 1;
    }
    return;
}

struct Mesh::edge {
    double points[2][3];
    int count = 0;
};

bool Mesh::edge_equality(edge edge_a, edge edge_b){
    bool ab_ab = true;
    bool ab_ba = true;

    for (int n = 0; n < 2; n++){
        for (int k = 0; k < 3; k++){
            if (edge_a.points[n][k] != edge_b.points[n][k]) {
                ab_ab = false;
                goto endloop_ab_ab;
            }
        }
    }
    endloop_ab_ab:
    for (int n = 0; n < 2; n++){
        for (int k = 0; k < 3; k++){
            if (edge_a.points[n][k] != edge_b.points[(n + 1) % 2][k]) {
                ab_ba = false;
                goto endloop_ab_ba;
            }
        }
    }
    endloop_ab_ba:
    return (ab_ab || ab_ba);
}

bool Mesh::is_enclosed(){
    vector<edge> edges;
    
    for (int k = 0; k < faces.size(); k++){
        for (int n = 0; n < 3; n++){
            double output[3][3];
            faces[k].get_point(output);
            edge current_edge = {
                                 {
                                  {output[n][0],output[n][1],output[n][2]},
                                  {output[(n + 1) % 3][0],output[(n + 1) % 3][1],output[(n + 1) % 3][2]}
                                 },
                                 1
                                };
            bool append_bool = true;
            for (int k = 0; k < edges.size(); k++){
                if (edge_equality(current_edge,edges[k])) {
                    edges[k].count += 1;
                    append_bool = false;
                    break;
                }
            }
            if (append_bool){
                edges.push_back(current_edge);
            }
        }
    }
    for (int k = 0; k < edges.size();k++){
        if (edges[k].count != 2) {
            return false;
        }
    }
    return true;
}

int Mesh::vec_find(vector<vector<double>> vec, double point[3]){
    for (int k = 0; k < vec.size(); k++){
        int prod = 1;
        for (int n = 0; n < 3; n++){
            prod *= (vec[k][n] == point[n]);
        }
        if (prod) {return k;};
    }
    return -1;
}

void Mesh::cross_prod(double vector_a[3], double vector_b[3], double output[3]){
    output[0] = vector_a[1]*vector_b[2] - vector_a[2]*vector_b[1];
    output[1] = vector_a[2]*vector_b[0] - vector_a[0]*vector_b[2];
    output[2] = vector_a[0]*vector_b[1] - vector_a[1]*vector_b[0];
}

void Mesh::unitize(double vector_a[3]){
    double sum = 0;
    for (int k = 0; k < 3; k++){
        sum += pow(vector_a[k],2);
    }
    double abs = sqrt(sum);
    for (int k = 0; k < 3; k++){
        vector_a[k] *= 1/abs;
    }
}

bool Mesh::is_tangent(Face face_a, Face face_b, double vector_a[3]){
    /*
        C ----- B
         \     / \
          \   /   \
           \ /     \
            A ----- D
    */
    double points_a[3][3]; 
    double points_b[3][3];
    face_a.get_point(points_a);
    face_b.get_point(points_b);
    // cout << points_a[0][0] << ' ' << points_a[0][1] << ' ' << points_a[0][2] << endl;
    // cout << points_a[1][0] << ' ' << points_a[1][1] << ' ' << points_a[1][2] << endl;
    // cout << points_a[2][0] << ' ' << points_a[2][1] << ' ' << points_a[2][2] << endl;
    // cout << endl;
    // cout << points_b[0][0] << ' ' << points_b[0][1] << ' ' << points_b[0][2] << endl;
    // cout << points_b[1][0] << ' ' << points_b[1][1] << ' ' << points_b[1][2] << endl;
    // cout << points_b[2][0] << ' ' << points_b[2][1] << ' ' << points_b[2][2] << endl;
    vector<int> a_indices; int a_index;
    vector<int> b_indices; int b_index;
    for (int l = 0; l < 3; l++){
        for (int k = 0; k < 3; k++){
            for (int j = 0; j < 3; j++)
                if (points_a[k][j] != points_b[l][j]){
                    break;
                } else if (j == 2){
                    a_indices.push_back(k);
                    b_indices.push_back(l);
                }
        }
    }
    if (a_indices.size() != 2){
        cerr << "is_tangent error" << endl;
        cout << a_indices.size() << endl;
        exit(1);
    }
    int a_index_sum = a_indices[0] + a_indices[1];
    int b_index_sum = b_indices[0] + b_indices[1];
    if (a_index_sum == 3) {
        a_index = 2;
    } else if (a_index_sum == 4){
        a_index = 1;
    } else a_index = 0;
    if (b_index_sum == 3) {
        b_index = 2;
    } else if (b_index_sum == 4){
        b_index = 1;
    } else b_index = 0;

    double CA[3] = {points_a[a_indices[0]][0] - points_a[a_index][0],
                    points_a[a_indices[0]][1] - points_a[a_index][1],
                    points_a[a_indices[0]][2] - points_a[a_index][2]};
    double AB[3] = {points_a[a_indices[1]][0] - points_a[a_indices[0]][0],
                    points_a[a_indices[1]][1] - points_a[a_indices[0]][1],
                    points_a[a_indices[1]][2] - points_a[a_indices[0]][2]};
    double AD[3] = {points_b[b_index][0] - points_a[a_indices[0]][0],
                    points_b[b_index][1] - points_a[a_indices[0]][1],
                    points_b[b_index][2] - points_a[a_indices[0]][2]};

    double normal_a[3]; cross_prod(CA,AB,normal_a); unitize(normal_a);
    double normal_b[3]; cross_prod(AD,AB,normal_b); unitize(normal_b);

    double sum_normals[3] = {normal_a[0] + normal_b[0],
                             normal_a[1] + normal_b[1],
                             normal_a[2] + normal_b[2]};
    unitize(sum_normals);
    int times = face_a.find_intersection(sum_normals,vector_a) +
                face_b.find_intersection(sum_normals,vector_a);
    return (times % 2);
}

bool Mesh::contains(double point[3]){
    double output[3];
    vector<vector<double>> points;
    vector<Face*> face_pointers;
    int count = 0;
    for (int k = 0; k < faces.size(); k++){
        bool intersect_bool = faces[k].intersects(point,outside_point,output);
        if (intersect_bool){
            int vf = vec_find(points,output);
            if (vf != -1){
                // If it finds it, the intersection must be either an edge or a point.
                // Check if it's a point by checking each of the points in faces[k].
                // If it is a point, first check if the given point is that point.
                        // If it is not, re-run contains() with some offset on outside_point.
                        // If it is, return true.
                for (int n = 0; n < 3; n++){
                    double fgp[3][3];
                    faces[k].get_point(fgp);
                    if (std::equal(fgp[n], fgp[n] + sizeof(fgp[n]) / sizeof(*fgp[n]), output)){
                        if (std::equal(fgp[n], fgp[n] + sizeof(fgp[n]) / sizeof(*fgp[n]), point)){
                            return true;
                        } else {
                            outside_point[0] += 1;
                            
                            bool result = contains(point);
                            calibrate_outside_point();
                            return result;
                        }
                    }
                }
                    // If it's an edge, run the tangent/intersecting edge checking algorithm. Algo cannot use recursion of contains().
                double vector_a[3] = {output[0]-outside_point[0],
                                      output[1]-outside_point[1],
                                      output[2]-outside_point[2]};
                if (!is_tangent(faces[k],*face_pointers[vf],vector_a)){
                    count++;
                };
            } else {
                vector<double> o_vec = {output[0],output[1],output[2]};
                // cout << o_vec[0] << ' ' << o_vec[1] << ' ' << o_vec[2] << endl;
                points.push_back(o_vec);
                face_pointers.push_back(&faces[k]);
                count++;
            }
        }
    }
    // cout << count << endl;
    return (count % 2);
}

void Mesh::scale(double x){
    for (int k = 0; k < faces.size(); k++){
        double output[3][3];
        faces[k].get_point(output);
        for (int j = 0; j < 3; j++){
            for (int n = 0; n < 3; n++){
                output[j][n] *= x;
            }
        }
        faces[k].set(output);
    }
}