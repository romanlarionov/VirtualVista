
#ifndef VIRTUALVVISTA_MESH_H
#define VIRTUALVVISTA_MESH_H

#include <vector>

#include <glm/gtc/matrix_transform.hpp>
#include <assimp/scene.h>

#include "Texture.h"
#include "Shader.h"
#include "Resource.h"

namespace vv
{
  struct Vertex
  {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 tex_coords;
  };

  class Mesh : public Resource
  {
  public:
    Mesh(const std::vector<Vertex> &vertices);
    Mesh(const std::vector<Vertex> &vertices, const std::vector<GLuint> &indices);
    Mesh(const std::vector<Vertex> &vertices, const std::vector<Texture> &textures);
    Mesh(const std::vector<Vertex> &vertices, const std::vector<GLuint> &indices, const std::vector<Texture> &textures);

    void render(Shader *shader);

  private:
    GLuint VAO_;
    GLuint VBO_;
    GLuint EBO_;

    bool has_indices_;
    bool has_textures_;

    std::vector<Vertex> vertices_;
    std::vector<GLuint> indices_;
    std::vector<Texture> textures_;

    void init();
  };
}

#endif // VIRTUALVVISTA_MESH_H