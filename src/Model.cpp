
#include <iostream>

#include "Model.h"

namespace vv
{
  Model::Model(std::string path)
  {
    loadModel(path);
  }


  void Model::render(Shader shader)
  {
    for (int i = 0; i < meshes_.size(); ++i)
      meshes_[i].render();
  }


  void Model::loadModel(std::string path)
  {
    Assimp::Importer importer;
    const aiScene *scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

    if (!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
      std::cerr << "ERROR: loading model from path: " << path << " failed.\n";
      std::cerr << "Assimp: " << importer.GetErrorString() << "\n";
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

    // Vertices
    for (GLuint i = 0; i < mesh->mNumVertices; ++i)
    {
      Vertex vertex;
      glm::vec3 temp_pos(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z);
      vertex.position = temp_pos;

      // TODO: eventually add in support for more intricate data, like normals, texture coords, etc.
      vertices.push_back(vertex);
    }

    // Indices
    bool has_faces = mesh->mNumFaces != 0;

    for (GLuint i = 0; i < mesh->mNumFaces; ++i)
    {
      aiFace face = mesh->mFaces[i];
      for (int j = 0; j < face.mNumIndices; ++j)
        indices.push_back(face.mIndices[j]);
    }

    // Materials
    if (mesh->mMaterialIndex >= 0)
    {
      aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];

      std::vector<Texture> diffuse_textures =
              loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
      textures.insert(textures.end(), diffuse_textures.begin(), diffuse_textures.end());

      std::vector<Texture> specular_textures =
              loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
      textures.insert(textures.end(), specular_textures.begin(), specular_textures.end());

      if (has_faces)
        return Mesh(vertices, indices, textures);

      return Mesh(vertices, textures);
    }

    if (has_faces)
      return Mesh(vertices, indices);

    return Mesh(vertices);
  }


  // TODO: create proper texture class
  GLuint TextureFromFile(const char *texture_name, std::string directory)
  {
    std::string path = directory + "/" + std::string(texture_name);
    GLuint texture_id;
    glGenTextures(1, &texture_id);
    int width, height;

    unsigned char *image = SOIL_load_image(path.c_str(), &width, &height, 0, SOIL_LOAD_RGB);

    glBindTexture(GL_TEXTURE_2D, texture_id);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    glGenerateMipmap(GL_TEXTURE_2D);

    // Parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);

    SOIL_free_image_data(image);
    return texture_id;
  }


  std::vector<Texture> Model::loadMaterialTextures(aiMaterial *material,
                                                   aiTextureType type,
                                                   std::string type_name)
  {
    std::vector<Texture> textures;

    // loop through all textures of this type and append them to the return variable
    for (GLuint i = 0; i < material->GetTextureCount(type); ++i)
    {
      aiString str;
      material->GetTexture(type, i, &str);
      bool previously_loaded = false;

      // loop through all previously loaded textures and see if they are the same as
      // this current one. if any of them are, add the previously loaded texture and break.
      for (auto t : textures_loaded_)
      {
        if (t.path == str)
        {
          textures.push_back(t);
          previously_loaded = true;
          break;
        }
      }

      if (!previously_loaded)
      {
        Texture texture;
        texture.id = TextureFromFile(str.C_Str(), directory_);
        texture.type = type_name;
        texture.path = str;

        textures.push_back(texture);
        textures_loaded_.push_back(texture);
      }
    }
  }
} // namespace vv
