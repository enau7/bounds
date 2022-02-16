#include <iostream>
#include "triangle.h"
#include "face.h"
#include "mesh.h"
#include "meshfile.h"
using namespace std;

int main(){
    // Triangle t(0,0,1,0,0,1);
    // t.contains(-3,0);
    // t.contains(-3,1);
    // return 0;
    // for (double k = 2; k > -2; k-= .1){
    //     for (double j = -2; j < 2; j+= .1){
    //         cout << t.contains(j,k);
    //     }
    //     cout << endl;
    // }
    // return 0;
//     double output[3];
//     Face f(0,0,0,1,1,1,1,1,0);
//     double point_a[3] = {0,.5,.2};
//     double point_b[3] = {.5,0,.2};
//     cout << f.intersects(point_a,point_b,output) << endl;
//     double point_c[3] = {0,0,.5};
//     double point_d[3] = {1,1,.5};
//     cout << f.intersects(point_c,point_d) << endl;
//     cout << output[0] << ' ' << output[1] << ' ' << output[2] << endl;
    Mesh m;
    // m.append(Face(0,0,0,1,1,1,0,1,0));
    // m.append(Face(0,0,0,1,1,1,1,0,0));
    // m.append(Face(1,1,1,0,1,0,1,0,0));
    // m.append(Face(0,0,0,0,1,0,1,0,0));
    MeshFile::init_mesh(m,"testobject.stl");
    //m.scale(.001);

    cout << "Is enclosed? " << m.is_enclosed() << endl;

    for (double k = -1; k < 1; k+= .1){
        for (double j = -1; j < 1; j += .1){
            for (double i = -1; i < 1; i += .1){
                m.contains(i,j,k) ? cout << "@@" : cout << ". ";
            }
            cout << endl;
        }
        cout << "k: " << k << endl;
    }
    cout << m.contains(1,1,1) << endl;
    cout << "Is enclosed? " << m.is_enclosed() << endl;
    m.append(Face(0,2,1,1,1,1,0,1,0));
    cout << "Is enclosed? " << m.is_enclosed() << endl;
    cout << m.contains(-.8,-.9,-.9) << endl;
    // Triangle t(0,0,1,0,0,1);
    // cout << t.contains(0,-2) << endl;
}