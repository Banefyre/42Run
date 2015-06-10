#ifndef _42RUN_MODEL_CLASS_HPP_
#define _42RUN_MODEL_CLASS_HPP_

#include <string>
#include <Shader.class.hpp>
#include <Mesh.class.hpp>
#include <vector>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <assimp/types.h>
#include <Camera.class.hpp>

#include <SOIL/SOIL.h>

class Model {

public:
    Model(std::string path, Shader * s);
    ~Model(void);

    void draw(Camera *camera);


    void setPosition(glm::vec3 pos);
    void setRotation(glm::vec3 rot);
    void setScale(glm::vec3 scale);

private:
    std::string          _directory;
    std::vector<Mesh>    _meshes;
    std::vector<Texture> _textures_loaded;

    Shader *             _shader;

    glm::vec3 _position;										// The model's position
    glm::vec3 _rotation;										// The model's rotation
    glm::vec3 _scale;										// The model's scale


    void loadModel(std::string path);
    void processNode(aiNode * node, const aiScene * scene);
    Mesh processMesh(aiMesh * mesh, const aiScene * scene);
    std::vector<Texture> loadMaterialTextures(aiMaterial * mat, aiTextureType type, std::string typeName);
    GLint TextureFromFile(const char* path, std::string directory);

};

#endif //_42RUN_MODEL_CLASS_HPP_
