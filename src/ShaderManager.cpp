
#include "ShaderManager.h"
#include "Settings.h"

namespace vv
{
  ShaderManager* ShaderManager::manager_singleton_ = nullptr;

  ShaderManager::ShaderManager()
  {
    std::string directory = Settings::instance()->getShaderLocation();
    light_cube_shader_ = new Shader(directory + "light_cube.vert", directory + "light_cube.frag");
    model_shader_ = new Shader(directory + "lighting.vert", directory + "lighting.frag");
  }


  ShaderManager* ShaderManager::instance()
  {
    if (!manager_singleton_)
      manager_singleton_ = new ShaderManager;

    return manager_singleton_;
  }


  Shader* ShaderManager::getLightCubeShader()
  {
    return light_cube_shader_;
  }


  Shader* ShaderManager::getModelShader()
  {
    return model_shader_;
  }
} // namespace vv