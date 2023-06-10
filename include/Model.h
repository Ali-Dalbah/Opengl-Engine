#ifndef MODEL_H
#define MODEL_H
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "Mesh.h"
#include "Shader.h"
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
using namespace std;

class Model {
public:
    vector<string> texNames;
    vector<Mesh>    meshes;
    bool gammaCorrection;
    string name;
    string path;
    Model(string const &, bool = false);
    void render(Shader &, Camera& );
    void rotate(float, axis);
    void translate(float, axis);
    void setScale(float);
private:
    void loadModel(string const &);
    void processNode(aiNode *, const aiScene *);
    Mesh processMesh(aiMesh *, const aiScene *);
};

#endif

