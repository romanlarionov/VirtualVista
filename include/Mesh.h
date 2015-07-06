
#ifndef VIRTUALVISTA_MESH_H
#define VIRTUALVISTA_MESH_H

#include <vector>

#include <GL/glew.h>
#include <glm/detail/type_vec.hpp>
#include <glm/detail/type_vec3.hpp>

#include "Shader.h"

struct Vertex
{
  glm::vec3 position;
  //glm::vec3 normal;
  //glm::vec3 color;
};

namespace vv
{
  class Mesh
  {
  public:
    Mesh(const std::vector<Vertex> &vertices);
    Mesh(const std::vector<Vertex> &vertices, const std::vector<GLuint> &indices);
    ~Mesh();

    void translate(glm::vec3 translation);
    void rotate(GLfloat angle, glm::vec3 axis);
    void bindMatrices(Shader *shader);
    void render();

  private:
    bool draw_elements_;

    GLuint VAO_;
    GLuint VBO_;
    GLuint EBO_;

    // Array of Structures
    std::vector<Vertex> vertices_;
    std::vector<GLuint> indices_;

    glm::mat4 model_mat_;

    void init();
  };
}

#endif // VIRTUALVISTA_MESH_H