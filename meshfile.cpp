#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include "face.h"
#include "mesh.h"
#include "meshfile.h"

void MeshFile::mesh_file_exit(){
    std::cerr << "Bad file formatting." << std::endl;
    exit(1);
};

void MeshFile::init_mesh(Mesh &m, std::string file_name){
    std::ifstream instream;
    instream.open(file_name);
    std::string s;
    double face[3][3];
    bool append_face = false;
    while (instream >> s) {
        if (s == "vertex"){
            for (int k = 0; k < 3; k++){
                instream >> s;
                face[0][k] = std::stod(s);
            }
            instream >> s;
            if (s == "vertex"){
                for (int k = 0; k < 3; k++){
                    instream >> s;
                    face[1][k] = std::stod(s);
                }
                instream >> s;
                if (s == "vertex"){
                    for (int k = 0; k < 3; k++){
                        instream >> s;
                        face[2][k] = std::stod(s);
                    }
                    append_face = true;
                } else mesh_file_exit();

            } else mesh_file_exit();
            instream >> s;
            if (s != "endloop") {mesh_file_exit();}
        }
        if (append_face) {
            m.append(Face(face));
            append_face = false;
        }
    }
}