
#include <iostream>
#include <glm/gtc/type_ptr.hpp>

#include "Model.h"

namespace vv
{
  Model::Model(GLchar *path, bool gamma) :
    gamma_correction_(gamma)
  {
    model_mat_ = glm::mat4(1.0f);
    loadModel(path);
  }


  void Model::translate(glm::vec3 translation)
  {
    model_mat_ = glm::translate(model_mat_, translation);
  }


  void Model::rotate(float angle, glm::vec3 axis)
  {
    model_mat_ = glm::rotate(model_mat_, angle, axis);
  }


  void Model::scale(glm::vec3 scaling)
  {
    model_mat_ = glm::scale(model_mat_, scaling);
  }


  void Model::render(Shader *shader)
  {
    // model matrix
    GLint model_location = glGetUniformLocation(shader->getProgramId(), "model");
    glUniformMatrix4fv(model_location, 1, GL_FALSE, glm::value_ptr(model_mat_));

    for (GLuint i = 0; i < meshes_.size(); ++i)
      meshes_[i].render(shader);
  }


  void Model::loadModel(std::string path)
  {
    Assimp::Importer importer;
    const aiScene *scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

    if (!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
      std::cerr << "ERROR: model from directory " << directory_ << " failed to load.\n";
      std::cerr << "assimp: " << importer.GetErrorString() << "\n";
      return;
    }

    directory_ = path.substr(0, path.find_last_of('/'));
    processNode(scene->mRootNode, scene);
  }


  void Model::processNode(aiNode *node, const aiScene *scene)
  {
    for (GLuint i = 0; i < node->mNumMeshes; ++i)
    {
      aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
      meshes_.push_back(processMesh(mesh, scene));
    }

    for (GLuint i = 0; i < node->mNumChildren; ++i)
      processNode(node->mChildren[i], scene);
  }


  Mesh Model::processMesh(aiMesh *mesh, const aiScene *scene)
  {
    std::vector<Vertex> vertices;
    std::vector<GLuint> indices;
    std::vector<Texture> textures;

    for (GLuint i = 0; i < mesh->mNumVertices; ++i)
    {
      Vertex vertex;
      glm::vec3 vector;

      vector.x = mesh->mVertices[i].x;
      vector.y = mesh->mVertices[i].y;
      vector.z = mesh->mVertices[i].z;
      vertex.position = vector;

      vector.x = mesh->mNormals[i].x;
      vector.y = mesh->mNormals[i].y;
      vector.z = mesh->mNormals[i].z;
      vertex.normal = vector;

      if (mesh->mTextureCoords[0])
      {
        glm::vec2 vec;
        vec.x = mesh->mTextureCoords[0][i].x;
        vec.y = mesh->mTextureCoords[0][i].y;
        vertex.tex_coords = vec;
      }
      else
        vertex.tex_coords = glm::vec2(0.0f, 0.0f);

      vertices.push_back(vertex);
    }

    bool has_faces = (mesh->mNumFaces > 0);
    for (GLuint i = 0; i < mesh->mNumFaces; ++i)
    {
      aiFace face = mesh->mFaces[i];
      for (GLuint j = 0; j < face.mNumIndices; ++j)
        indices.push_back(face.mIndices[j]);
    }

    if (mesh->mMaterialIndex >= 0)
    {
      aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];

      std::vector<Texture> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
      textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

      std::vector<Texture> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
      textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());

      if (has_faces)
        return Mesh(vertices, indices, textures);

      return Mesh(vertices, textures);
    }

    if (has_faces)
      return Mesh(vertices, indices);

    return Mesh(vertices);
  }


  // TODO: make proper texture container
  GLuint TextureFromFile(const char *path, std::string directory, bool gamma)
  {
    std::string filename = directory + "/" + std::string(path);
    GLuint texture_id;
    glGenTextures(1, &texture_id);
    int width, height;
    unsigned char *image = SOIL_load_image(filename.c_str(), &width, &height, 0, SOIL_LOAD_RGB);

    glBindTexture(GL_TEXTURE_2D, texture_id);
    glTexImage2D(GL_TEXTURE_2D, 0, gamma ? GL_SRGB : GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    glGenerateMipmap(GL_TEXTURE_2D);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);
    SOIL_free_image_data(image);
    return texture_id;
  }


  std::vector<Texture> Model::loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName)
  {
    std::vector<Texture> textures;
    for (GLuint i = 0; i < mat->GetTextureCount(type); ++i)
    {
      aiString str;
      mat->GetTexture(type, i, &str);

      bool already_loaded = false;
      for (auto t : textures_loaded_)
      {
        if (t.path == str)
        {
          textures.push_back(t);
          already_loaded = true;
          break;
        }
      }
      if (!already_loaded)
      {
        Texture texture;
        texture.id = TextureFromFile(str.C_Str(), directory_, false);
        texture.type = typeName;
        texture.path = str;
        textures.push_back(texture);
        textures_loaded_.push_back(texture);
      }
    }
    return textures;
  }
} // namespace vv