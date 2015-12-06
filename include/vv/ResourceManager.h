
#ifndef VIRTUALVISTA_RESOURCEMANAGER_H
#define VIRTUALVISTA_RESOURCEMANAGER_H

#include <unordered_map>

#include "Shader.h"
#include "Model.h"
#include "Texture.h"

namespace vv
{
  class ResourceManager
  {
  public:
    static ResourceManager* instance();

    bool loadModelFromFile(std::string filepath);
    bool loadTextureFromFile(std::string filepath);

	// todo: remove such non-generic shader get functions
    Shader* getLightCubeShader();
    Shader* getModelShader();

  private:
    static ResourceManager *resource_manager_singleton_;

    // todo: find good handle to give each resource.
    std::unordered_map<std::string, Shader *> shaders_;
    std::unordered_map<std::string, Texture *> textures_;
    std::unordered_map<std::string, Mesh *> meshes_;

    Shader *light_cube_shader_;
    Shader *model_shader_;

    ResourceManager();
    ResourceManager(ResourceManager const&) {};
    ResourceManager& operator=(ResourceManager const&) {};

    // todo: this class needs to load, cache/arrange, and dispose of all resources automatically.
  };
}

#endif // VIRTUALVISTA_RESOURCEMANAGER_H