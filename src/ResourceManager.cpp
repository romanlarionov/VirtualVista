
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


  bool ResourceManager::loadModelFromFile(std::string filepath)
  {

  }


  bool ResourceManager::loadTextureFromFile(std::string filepath)
  {

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
} // namespace vv