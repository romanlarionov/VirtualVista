
#ifndef VIRTUALVISTA_RESOURCEMANAGER_H
#define VIRTUALVISTA_RESOURCEMANAGER_H

#include <unordered_map>

#include "Shader.h"

namespace vv
{
  class ResourceManager
  {
  public:
    ResourceManager();
	  ~ResourceManager();

    Handle addShader(std::string name, std::string path);
    void removeShader(Handle handle);

    bool loadMeshFromFile(std::string path, std::string name);
    bool loadTextureFromFile(std::string path, std::string name);

    void clearResources();

  private:
	  // todo: this class needs to load, cache/arrange, and dispose of all resources automatically.
	  std::unordered_map<ShaderHandle, Shader *> shader_buffer_;

    ResourceManager(ResourceManager const&) {};
    ResourceManager& operator=(ResourceManager const&) {};

    Shader* getShader(std::string name, std::string path);
    ShaderHandle createShaderHandle(std::string input);

  };
}

#endif // VIRTUALVISTA_RESOURCEMANAGER_H