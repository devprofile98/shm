#include <Model.hpp>

//#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


unsigned int TextureFromFile(const char *path, const std::string &directory, bool gamma)
{
    std::string filename = std::string(path);
    filename = directory + '/' + filename;

    unsigned int textureID;
    glGenTextures(1, &textureID);

    int width, height, nrComponents;
    unsigned char *data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);
    if (data)
    {
        GLenum format;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        glActiveTexture(GL_TEXTURE0 + Model::texture_layout_counter);
        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        std::cout<<
                    "Engine::TEXTURE::DEBUG::-> loaded succesfully in slot number "<<
                    Model::texture_layout_counter <<
                    std::endl;

        Model::texture_layout_counter++;
//        glActiveTexture(GL_TEXTURE0);
        stbi_image_free(data);
    }
    else
    {
        std::cout << "Texture failed to load at path: " << path << std::endl;
        stbi_image_free(data);
    }

    return textureID;
}

Model::Model(const char *path, std::shared_ptr<shader> sh ): shader_program(sh)
{
    if (shader_program.get() == nullptr) return;
    loadModel(path);
    std::cout<<"LOADING MODEL COMPLETED"<<std::endl;
    m_position = glm::vec3{0,0,0};
    m_scale = glm::vec3{1.0f};
    m_rotation = glm::vec3{0.0f, 1.0f, 0.0f};
}

void Model::Draw(std::shared_ptr<shader> sh){

    glm::mat4 model{1.0f};
    model = glm::translate(model, m_position);
    model = glm::scale(model, m_scale);
        model = glm::rotate(model, glm::radians(90.0f), m_rotation);

    if (sh){
        // calculate for shadow map
        sh->use();
        sh->setMat4("model", model);
    }
    else{
        shader_program->use();
        shader_program->setMat4("model", model);
    }

    for(uint32_t i = 0; i<meshes.size();i++){
        if (sh){
            meshes[i].Draw(sh);
        }
        else{
            meshes[i].Draw(shader_program);
        }
    }
}

std::shared_ptr<shader> Model::getShader()
{
    return shader_program;
}

void Model::setPosition(const glm::vec3 &pos)
{
    this->m_position = pos;
}

void Model::setScale(const glm::vec3 &scale)
{
    this->m_scale = scale;
    std::cout << m_scale.x << m_scale.y <<m_scale.z<<std::endl;
}

void Model::setRotation(const glm::vec3 &rot)
{
    this->m_rotation = rot;
}

const glm::vec3 *Model::getPosition() const
{
    return &m_position;
}

const glm::vec3 *Model::getScale() const
{
    return &m_scale;
}

const glm::vec3 *Model::getRotation() const
{
    return &m_rotation;
}

void Model::loadModel(std::string path){
    Assimp::Importer import;
    const aiScene *scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);
    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode){
        std::cout<<"ERROR::ASSIMP::"<<import.GetErrorString()<<std::endl;
        return;
    }
    directory = path.substr(0,path.find_last_of('/'));
    processNode(scene->mRootNode, scene);
}

void Model::processNode(aiNode *node, const aiScene *scene){
    for(uint32_t i=0; i<node->mNumMeshes;i++){
        aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
        meshes.push_back(processMesh(mesh,  scene));
    }
    for(uint32_t i=0; i<node->mNumChildren;i++){
        processNode(node->mChildren[i], scene);
    }
}

Mesh Model::processMesh(aiMesh *mesh, const aiScene *scene){
    std::vector<Vertex> vertices;
    std::vector<Texture_INT> textures;
    std::vector<uint32_t> indices;

    for(uint32_t i=0;i < mesh->mNumVertices; i++){
        Vertex vertex;
        glm::vec3 vector;

        vector.x = mesh->mVertices[i].x;
        vector.y = mesh->mVertices[i].y;
        vector.z = mesh->mVertices[i].z;

        vertex.Position = vector;

        if (mesh->HasNormals()){

            vector.x = mesh->mNormals[i].x;
            vector.y = mesh->mNormals[i].y;
            vector.z = mesh->mNormals[i].z;
            vertex.Normal = vector;
        }

        if(mesh->mTextureCoords[0]){
            
            glm::vec2 vec;
            vec.x = mesh->mTextureCoords[0][i].x;
            vec.y = mesh->mTextureCoords[0][i].y;
            vertex.TexCoords = vec;
            // // tangent
            // vector.x = mesh->mTangents[i].x;
            // vector.y = mesh->mTangents[i].y;
            // vector.z = mesh->mTangents[i].z;
            // vertex.Tangent = vector;
            // // bitangent
            // vector.x = mesh->mBitangents[i].x;
            // vector.y = mesh->mBitangents[i].y;
            // vector.z = mesh->mBitangents[i].z;
            // vertex.Bitangent = vector;
        }
        else{
            vertex.TexCoords = glm::vec2{0.0f,0.0f};
        }

        vertices.push_back(vertex);
    }

    for(uint32_t i = 0;i<mesh->mNumFaces;i++){
        aiFace face = mesh->mFaces[i];
        for(uint32_t j=0; j<face.mNumIndices;j++){
            indices.push_back(face.mIndices[j]);
        }
    }

    aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

    aiColor3D color;
    Material_INT mat;
    // Read mtl file vertex data
    material->Get(AI_MATKEY_COLOR_AMBIENT, color);
    mat.ka = glm::vec4(color.r, color.g, color.b, 1.0);
    std::cout <<color.r << color.g << color.b<<std::endl;
    material->Get(AI_MATKEY_COLOR_DIFFUSE, color);
    mat.kd = glm::vec4(color.r, color.g, color.b, 1.0);
    material->Get(AI_MATKEY_COLOR_SPECULAR, color);
    mat.ks = glm::vec4(color.r, color.g, color.b, 1.0);


    std::cout << "\n\n\n\n material colors is " << mat << std::endl;

    std::vector<Texture_INT> diffuseMap = loadMaterialTexture(material, aiTextureType_DIFFUSE, "texture_diffuse");
    textures.insert(textures.end(), diffuseMap.begin(), diffuseMap.end());

    std::vector<Texture_INT> specularMap = loadMaterialTexture(material, aiTextureType_SPECULAR, "texture_specular");
    textures.insert(textures.end(), specularMap.begin(), specularMap.end());

    // 3. normal maps
    std::vector<Texture_INT> normalMaps = loadMaterialTexture(material, aiTextureType_HEIGHT, "texture_normal");
    textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());

    // 4. height maps
    std::vector<Texture_INT> heightMaps = loadMaterialTexture(material, aiTextureType_AMBIENT, "texture_height");
    textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());

    if(textures.size() <= 0) mat.should_draw = true;
    
    // return a mesh object created from the extracted mesh data
    return Mesh(vertices, indices, textures, mat);
}

std::vector<Texture_INT> Model::loadMaterialTexture(aiMaterial *material, aiTextureType type, std::string typeName){
    std::vector<Texture_INT> textures;
    for(uint32_t i=0; i<material->GetTextureCount(type); i++){
        aiString str;
        material->GetTexture(type, i, &str);
        bool skip = false;
        for(uint32_t j=0; j< textures_loaded.size();j++ ){

            if(std::strcmp(textures_loaded[j].path.data(), str.C_Str()) == 0)
            {
                textures.push_back(textures_loaded[j]);
                skip = true; // a texture with the same filepath has already been loaded, continue to next one. (optimization)
                break;
            }
        }
        if(!skip)
        {   // if texture hasn't been loaded already, load it
            Texture_INT texture;
            texture.id = TextureFromFile(str.C_Str(), this->directory);
            texture.type = typeName;
            texture.path = str.C_Str();
            texture.bounded_slot = Model::texture_layout_counter -1;
            textures.push_back(texture);
            textures_loaded.push_back(texture);  // store it as texture loaded for entire model, to ensure we won't unnecesery load duplicate textures.
        }
    }
    return textures;
} 

uint32_t Model::texture_layout_counter =0;
