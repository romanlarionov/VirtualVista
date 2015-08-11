
#ifndef VIRTUALVISTA_RESOURCEMANAGER_H
#define VIRTUALVISTA_RESOURCEMANAGER_H

#include <set>

#include "Light.h"
#include "Model.h"
#include "Texture.h"
#include "Shader.h"

namespace vv
{
  class ResourceManager
  {
    friend class Light;
    friend class Model;
    friend class Texture;

  public:
    static ResourceManager* instance();

    std::set<Light *>& getLights();
    std::set<Model *>& getModels();
    std::set<Texture *>& getTextures();

    Shader* getLightCubeShader();
    Shader* getModelShader();

  private:
    static ResourceManager *resource_manager_singleton_;

    std::set<Light *> lights_;
    std::set<Model *> models_;
    std::set<Texture *> textures_;

    Shader *light_cube_shader_;
    Shader *model_shader_;

    ResourceManager();
    ResourceManager(ResourceManager const&) {};
    ResourceManager& operator=(ResourceManager const&) {};

    void manage(Light *light);
    void manage(Model *model);
    void manage(Texture *texture);

    void stopManaging(Light *light);
    void stopManaging(Model *model);
    void stopManaging(Texture *texture);
  };
}

#endif // VIRTUALVISTA_RESOURCEMANAGER_H