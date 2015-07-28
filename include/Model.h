
#ifndef VIRTUALVVISTA_MODEL_H
#define VIRTUALVVISTA_MODEL_H

#include <string>
#include <vector>

#include <glm/glm.hpp>
#include <glm/vec3.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <SOIL/SOIL.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Entity.h"
#include "Mesh.h"

namespace vv
{
  class Model : public Entity
  {
  public:
    Model(GLchar *path, bool gamma = false);

    void render();

  private:
    std::vector<Texture> textures_loaded_;
    std::vector<Mesh> meshes_;
    std::string directory_;
    bool gamma_correction_;

    void loadModel(std::string path);
    void processNode(aiNode *node, const aiScene *scene);
    Mesh processMesh(aiMesh *mesh, const aiScene *scene);
    std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName);
  };
}

#endif // VIRTUALVVISTA_MODEL_H