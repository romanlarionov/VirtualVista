
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
    is_point_light_(point_light),
    intensity_(100.0f)
  {
    transform_ = new Transform;
    cube_mesh_ = new Mesh(createCube(cube_vertices_));
    color_ = glm::vec3(1.0f, 1.0f, 1.0f);
  }


  Light::~Light()
  {
    delete transform_;
    delete cube_mesh_;
  }


  Transform* Light::getTransform()
  {
    return transform_;
  }


  void Light::update(Shader *shader)
  {
    GLint light_color_location = glGetUniformLocation(shader->getProgramId(), "light_color");
    glUniform3f(light_color_location, color_.x, color_.y, color_.z);

    GLint light_position_location = glGetUniformLocation(shader->getProgramId(), "light_position");
    glm::vec3 position = transform_->getTranslation();
    glUniform3f(light_position_location, position.x, position.y, position.z);
  }


  void Light::render()
  {
    Shader *shader = ShaderManager::instance()->getLightCubeShader();

    GLint model_location = glGetUniformLocation(shader->getProgramId(), "model");
    glUniformMatrix4fv(model_location, 1, GL_FALSE, glm::value_ptr(transform_->getMatrix()));

    GLint light_color_location = glGetUniformLocation(shader->getProgramId(), "light_color");
    glUniform3f(light_color_location, color_.x, color_.y, color_.z);

    cube_mesh_->render(shader);
  }
} // namespace vv