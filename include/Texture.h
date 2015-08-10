
#ifndef VIRTUALVISTA_TEXTURE_H
#define VIRTUALVISTA_TEXTURE_H

#include <GL/glew.h>
#include <assimp/scene.h>

namespace vv
{
  class Texture
  {
  public:
    Texture();
    Texture(std::string file_path, std::string texture_type, bool correct_gamma = true);
    ~Texture();

    GLuint getTextureId();
    std::string getTextureType();
    std::string getFilePath();

  private:
    GLuint texture_id_;
    std::string texture_type_;
    std::string file_path_;
    bool correct_gamma_;

    // TODO: add error checking if texture not created properly
    void loadTextureFromFile();
  };
}

#endif // VIRTUALVISTA_TEXTURE_H