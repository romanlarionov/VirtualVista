
#include "vv/ResourceManager.h"
#include "vv/Settings.h"

namespace vv
{
  ResourceManager* ResourceManager::resource_manager_singleton_ = nullptr;

  /////////////////////////////////////////////////////////////////////// public
  ResourceManager* ResourceManager::instance()
  {
    if (!resource_manager_singleton_)
      resource_manager_singleton_ = new ResourceManager;

    return resource_manager_singleton_;
  }


  std::set<Light *>& ResourceManager::getLights()
  {
    return lights_;
  }


  std::set<Model *>& ResourceManager::getModels()
  {
    return models_;
  }


  std::set<Texture *>& ResourceManager::getTextures()
  {
    return textures_;
  }


  Shader* ResourceManager::getLightCubeShader()
  {
    return light_cube_shader_;
  }


  Shader* ResourceManager::getModelShader()
  {
    return model_shader_;
  }


  ////////////////////////////////////////////////////////////////////// private
  ResourceManager::ResourceManager()
  {
    std::string directory = Settings::instance()->getShaderLocation();
    light_cube_shader_ = new Shader(directory + "light_cube.vert", directory + "light_cube.frag");
    model_shader_ = new Shader(directory + "lighting.vert", directory + "lighting.frag");
  }


  void ResourceManager::manage(Light * light)
  {
    lights_.insert(light);
  }


  void ResourceManager::manage(Model * model)
  {
    models_.insert(model);
  }


  void ResourceManager::manage(Texture * texture)
  {
    textures_.insert(texture);
  }


  void ResourceManager::stopManaging(Light * light)
  {
    lights_.erase(light);
  }


  void ResourceManager::stopManaging(Model * model)
  {
    models_.erase(model);
  }


  void ResourceManager::stopManaging (Texture * texture)
  {
    textures_.erase(texture);
  }
} // namespace vv