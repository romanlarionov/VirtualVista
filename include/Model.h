
#ifndef VIRTUALVISTA_MODEL_H
#define VIRTUALVISTA_MODEL_H

#include <string>
#include <vector>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <SOIL/SOIL.h>

#include "Shader.h"
#include "Mesh.h"

namespace vv
{
  class Model
  {
  public:
    Model(std::string path);

    void render(Shader shader);
  private:
    std::vector<Mesh> meshes_;
    std::string directory_;

    std::vector<Texture> textures_loaded_;

    void loadModel(std::string path);
    void processNode(aiNode *node, const aiScene *scene);
    Mesh processMesh(aiMesh *mesh, const aiScene *scene);

    std::vector<Texture> loadMaterialTextures(aiMaterial *material,
                                              aiTextureType type,
                                              std::string type_name);
  };
}

#endif //VIRTUALVISTA_MODEL_H
