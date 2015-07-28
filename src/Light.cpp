
#include <vector>

#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/transform.hpp>

#include "Light.h"
#include "ShaderManager.h"

namespace vv
{
  GLfloat cube_vertices_[] = {
    -0.5f, -0.5f, -0.5f,
     0.5f, -0.5f, -0.5f,
     0.5f,  0.5f, -0.5f,
     0.5f,  0.5f, -0.5f,
    -0.5f,  0.5f, -0.5f,
    -0.5f, -0.5f, -0.5f,

    -0.5f, -0.5f,  0.5f,
     0.5f, -0.5f,  0.5f,
     0.5f,  0.5f,  0.5f,
     0.5f,  0.5f,  0.5f,
    -0.5f,  0.5f,  0.5f,
    -0.5f, -0.5f,  0.5f,

    -0.5f,  0.5f,  0.5f,
    -0.5f,  0.5f, -0.5f,
    -0.5f, -0.5f, -0.5f,
    -0.5f, -0.5f, -0.5f,
    -0.5f, -0.5f,  0.5f,
    -0.5f,  0.5f,  0.5f,

     0.5f,  0.5f,  0.5f,
     0.5f,  0.5f, -0.5f,
     0.5f, -0.5f, -0.5f,
     0.5f, -0.5f, -0.5f,
     0.5f, -0.5f,  0.5f,
     0.5f,  0.5f,  0.5f,

    -0.5f, -0.5f, -0.5f,
     0.5f, -0.5f, -0.5f,
     0.5f, -0.5f,  0.5f,
     0.5f, -0.5f,  0.5f,
    -0.5f, -0.5f,  0.5f,
    -0.5f, -0.5f, -0.5f,

    -0.5f,  0.5f, -0.5f,
     0.5f,  0.5f, -0.5f,
     0.5f,  0.5f,  0.5f,
     0.5f,  0.5f,  0.5f,
    -0.5f,  0.5f,  0.5f,
    -0.5f,  0.5f, -0.5f
  };

  std::vector<Vertex> createCube(GLfloat vertices[])
  {
    std::vector<Vertex> cube;
    for (int i = 0; i < 36; ++i)
    {
      Vertex vertex;
      glm::vec3 temp_position(vertices[3*i], vertices[3*i+1], vertices[3*i+2]);
      vertex.position = temp_position;
      vertex.normal = glm::vec3(0.0f, 0.0f, 0.0f);
      vertex.tex_coords = glm::vec2(0.0f, 0.0f);
      cube.push_back(vertex);
    }
    return cube;
  }

  Light::Light(bool point_light) :
    is_point_light_(point_light)
  {
    model_mat_ = glm::mat4(1.0f);
    cube_mesh_ = new Mesh(createCube(cube_vertices_));
  }


  Light::~Light()
  {

  }


  void Light::translate(glm::vec3 translation)
  {
    model_mat_ = glm::translate(model_mat_, translation);
  }


  void Light::rotate(float angle, glm::vec3 axis)
  {
    model_mat_ = glm::rotate(model_mat_, angle, axis);
  }


  void Light::scale(glm::vec3 scaling)
  {
    model_mat_ = glm::scale(model_mat_, scaling);
  }


  void Light::update()
  {

  }


  void Light::render()
  {
    Shader *shader = ShaderManager::instance()->getLightCubeShader();
    shader->useProgram();

    GLint model_location = glGetUniformLocation(shader->getProgramId(), "model");
    glUniformMatrix4fv(model_location, 1, GL_FALSE, glm::value_ptr(model_mat_));

    GLint light_color_location = glGetUniformLocation(shader->getProgramId(), "light_color");
    glUniform3f(light_color_location, 0.0f, 1.0f, 1.0f);

    cube_mesh_->render(shader);
  }
} // namespace vv