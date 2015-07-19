
#ifndef VIRTUALVISTA_MESH_H
#define VIRTUALVISTA_MESH_H

#include <vector>

#include <GL/glew.h>
#include <glm/detail/type_vec.hpp>
#include <glm/detail/type_vec3.hpp>
#include <glm/detail/type_mat4x4.hpp>
#include <assimp/scene.h>

#include "Shader.h"

struct Vertex
{
  glm::vec3 position;
  //glm::vec3 normal;
  //glm::vec3 color;
};

struct Texture
{
  GLuint id;
  std::string type;
  aiString path;
};

namespace vv
{
  class Mesh
  {
  public:
    Mesh(const std::vector<Vertex> &vertices);
    Mesh(const std::vector<Vertex> &vertices, const std::vector<GLuint> &indices);
    Mesh(const std::vector<Vertex> &vertices, const std::vector<Texture> &textures);
    Mesh(const std::vector<Vertex> &vertices,
         const std::vector<GLuint> &indices,
         const std::vector<Texture> &textures);
    ~Mesh();

    void translate(glm::vec3 translation);
    void rotate(GLfloat angle, glm::vec3 axis);
    void bindUniforms(Shader *shader);
    void render();

  private:
    bool has_indices_;
    bool has_textures_;

    GLuint VAO_;
    GLuint VBO_;
    GLuint EBO_;

    // Array of Structures
    std::vector<Vertex> vertices_;
    std::vector<GLuint> indices_;
    std::vector<Texture> textures_;

    glm::mat4 model_mat_;

    void init();
  };
}

#endif // VIRTUALVISTA_MESH_H