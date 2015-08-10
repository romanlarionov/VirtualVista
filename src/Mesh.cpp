
#include <sstream>

#include "Mesh.h"
#include "ShaderManager.h"

namespace vv
{
  /////////////////////////////////////////////////////////////////////// public
  Mesh::Mesh(const std::vector<Vertex>& vertices)
  {
    vertices_ = vertices;
    has_indices_ = false;
    has_textures_ = false;
    init();
  }

  Mesh::Mesh(const std::vector<Vertex>& vertices,
             const std::vector<GLuint>& indices)
  {
    vertices_ = vertices;
    indices_ = indices;
    has_indices_ = true;
    has_textures_ = false;
    init();
  }

  Mesh::Mesh(const std::vector<Vertex>& vertices,
             const std::vector<Texture>& textures)
  {
    vertices_ = vertices;
    textures_ = textures;
    has_indices_ = false;
    has_textures_ = true;
    init();
  }


  Mesh::Mesh(const std::vector<Vertex>& vertices,
             const std::vector<GLuint>& indices,
             const std::vector<Texture>& textures)
  {
    vertices_ = vertices;
    indices_ = indices;
    textures_ = textures;
    has_indices_ = true;
    has_textures_ = true;
    init();
  }


  void Mesh::render(Shader *shader)
  {
    if (has_textures_)
    {
      GLuint num_diffuse = 1;
      GLuint num_specular = 1;
      for (GLuint i = 0; i < textures_.size(); ++i)
      {
        glActiveTexture(GL_TEXTURE0 + i);
        std::stringstream ss;
        std::string number;
        std::string uniform_name = textures_[i].getTextureType();

        if (uniform_name == "texture_diffuse")
          ss << num_diffuse++;

        else if (uniform_name == "texture_specular")
          ss << num_specular++;

        number = ss.str();

        glUniform1f(glGetUniformLocation(shader->getProgramId(), (uniform_name + number).c_str()), i);
        glBindTexture(GL_TEXTURE_2D, textures_[i].getTextureId());
      }
    }

    glBindVertexArray(VAO_);

    // Render
    if (has_indices_)
      glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(indices_.size()), GL_UNSIGNED_INT, 0);
    else
      glDrawArrays(GL_TRIANGLES, 0, static_cast<GLsizei>(vertices_.size()));

    // Cleanup
    glBindVertexArray(0);

    if (has_textures_)
    {
      for (GLuint i = 0; i < textures_.size(); ++i)
      {
        glActiveTexture(GL_TEXTURE0 + i);
        glBindTexture(GL_TEXTURE_2D, 0);
      }
    }
  }


  ////////////////////////////////////////////////////////////////////// private
  void Mesh::init()
  {
    glGenVertexArrays(1, &VAO_);
    glBindVertexArray(VAO_);

    glGenBuffers(1, &VBO_);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_);
    glBufferData(GL_ARRAY_BUFFER, vertices_.size() * sizeof(Vertex), &vertices_[0], GL_STATIC_DRAW);

    if (has_indices_)
    {
      glGenBuffers(1, &EBO_);
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_);
      glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices_.size() * sizeof(GLuint), &indices_[0], GL_STATIC_DRAW);
    }

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid *)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid *)offsetof(Vertex, normal));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid *)offsetof(Vertex, tex_coords));

    glBindVertexArray(0);
  }
} // namespace vv