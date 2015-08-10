
#include <SOIL/SOIL.h>

#include "Texture.h"

namespace vv
{
  /////////////////////////////////////////////////////////////////////// public
  Texture::Texture()
  {
  }


  Texture::Texture(std::string file_path, std::string texture_type, bool correct_gamma) :
    file_path_(file_path),
    texture_type_(texture_type),
    correct_gamma_(correct_gamma)
  {
    loadTextureFromFile();
  }


  Texture::~Texture()
  {
  }


  GLuint Texture::getTextureId()
  {
    return texture_id_;
  }


  std::string Texture::getTextureType()
  {
    return texture_type_;
  }


  std::string Texture::getFilePath()
  {
    return file_path_;
  }


  ////////////////////////////////////////////////////////////////////// private
  void Texture::loadTextureFromFile()
  {
    glGenTextures(1, &texture_id_);
    int width, height;
    unsigned char *image = SOIL_load_image(file_path_.c_str(), &width, &height, 0, SOIL_LOAD_RGB);

    glBindTexture(GL_TEXTURE_2D, texture_id_);
    glTexImage2D(GL_TEXTURE_2D, 0, correct_gamma_ ? GL_SRGB : GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    glGenerateMipmap(GL_TEXTURE_2D);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);
    SOIL_free_image_data(image);
  }
} // namespace vv