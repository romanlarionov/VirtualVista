
#ifndef VIRTUALVISTA_SHADERMANAGER_H
#define VIRTUALVISTA_SHADERMANAGER_H

#include "Shader.h"

namespace vv
{
  class ShaderManager
  {
  public:
    static ShaderManager* instance();

    Shader* getLightCubeShader();
    Shader* getModelShader();

  private:
    static ShaderManager *manager_singleton_;

    Shader *light_cube_shader_;
    Shader *model_shader_;

    ShaderManager();
    ShaderManager(ShaderManager const&);
    ShaderManager& operator=(ShaderManager const&);
  };
}

#endif // VIRTUALVISTA_SHADERMANAGER_H