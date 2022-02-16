#pragma once
#include <string>
#include "mesh.h"

class MeshFile {
    private:
        static void mesh_file_exit();
    public:
        static void init_mesh(Mesh &m, std::string file_name);
};