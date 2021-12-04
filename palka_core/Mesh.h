//
// Created by dimka on 11/30/2021.
//

#ifndef PALKA_MESH_H
#define PALKA_MESH_H

#include "VertexArray.h"
#include "ShaderProgram.h"
#include "Texture.h"
#include "ConsoleLog.h"
#include <assimp/Importer.hpp>
#include <utility>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

namespace palka
{

    class Material
    {
    public:
        std::unique_ptr<Texture> texture;
        std::string type;

        Material(std::unique_ptr<Texture> textures, std::string_view type) : texture(std::move(textures)), type(type)
        {}
    };

    class Model
    {
    public:
        palka::VertArray array;
        std::vector<unsigned int> indecies;
        VertexBufferObject vbo;
        VertexArrayObject vao;
        VertexBufferObject indecesVbo;

        Model() : indecesVbo(BufferObject::BufferType::EAB)
        {}

        explicit Model(palka::VertArray ar, std::vector<unsigned int> indec) : array(std::move(ar)), indecies(std::move(indec)),
                                                                               indecesVbo(BufferObject::BufferType::EAB)
        {
            create();
        }

//        explicit Model(palka::VertArray ar, std::vector<unsigned int> indec) : array(std::move(ar)), indecies(std::move(indec)),
//                                                                                                          indecesVbo(BufferObject::BufferType::EAB)
//        {
//            create();
//        }

        void create()
        {
            vao.create(1);
            vbo.create(sizeof(Vertex) * array.getSize());
            indecesVbo.create(sizeof(GLuint) * indecies.size());
            vao.bind();

            vbo.setData(sizeof(Vertex) * array.getSize(), &array[0].pos.x);
            indecesVbo.setData(sizeof(GLuint) * indecies.size(), &indecies[0]);
            vao.setPointers(vbo, sizeof(Vertex));

            vbo.unbind();
            indecesVbo.unbind();
            vao.unbind();
        }

        void render()
        {
            vao.bind();
//            unsigned int diffuseNr = 1;
//            unsigned int specularNr = 1;
//            unsigned int normalNr = 1;
//            unsigned int heightNr = 1;
//            int i = 0;
//            for(auto& mat: materials)
//            {
//                glActiveTexture(GL_TEXTURE0 + i); // active proper texture unit before binding
//                // retrieve texture number (the N in diffuse_textureN)
//                std::string number;
//                std::string name = mat.type;
//                if(name == "texture_diffuse")
//                    number = std::to_string(diffuseNr++);
//                else if(name == "texture_specular")
//                    number = std::to_string(specularNr++); // transfer unsigned int to string
//                else if(name == "texture_normal")
//                    number = std::to_string(normalNr++); // transfer unsigned int to string
//                else if(name == "texture_height")
//                    number = std::to_string(heightNr++); // transfer unsigned int to string
//
//                glUniform1i(glGetUniformLocation(shader.getId(), (name + number).c_str()), i);
//                glBindTexture(GL_TEXTURE_2D, mat.texture.textureID);
//                ++i;
//            }
            glDrawElements(GL_TRIANGLES, indecies.size(), GL_UNSIGNED_INT, 0);
            // glActiveTexture(GL_TEXTURE0);
        }
    };

    class Mesh
    {
    private:
        Texture txt;
        std::vector<Material> materials;
        VertexArray model_data;
        std::string path;
        int insize;
        std::vector<Model> models;

    public:
        Mesh() //: indecesVbo(BufferObject::BufferType::EAB)
        {}

        Mesh(std::string_view path) : path(path)//, indecesVbo(BufferObject::BufferType::EAB)
        {
        }

        void load(std::string_view path)
        {
            txt.LoadFromFile("Data//model//diffuse.jpg");
            this->path = path;
            Assimp::Importer importer;
            const aiScene* scene = importer.ReadFile(this->path,
                                                     aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
            if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
            {
                Console::addLog("ASSIMP LOAD ERROR", Console::error);
                return;
            }
            processNode(scene->mRootNode, scene);
        }

        void processNode(aiNode* node, const aiScene* scene)
        {
            for(unsigned int i = 0; i < node->mNumMeshes; i++)
            {
                aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
                processMesh(mesh, scene);
            }
            for(unsigned int i = 0; i < node->mNumChildren; i++)
            {
                processNode(node->mChildren[i], scene);
            }
        }

        void processMesh(const aiMesh* mesh, const aiScene* scene)
        {
            palka::VertArray array;

            for(unsigned int i = 0; i < mesh->mNumVertices; i++)
            {
                glm::vec3 vector;
                vector.x = mesh->mVertices[i].x;
                vector.y = mesh->mVertices[i].y;
                vector.z = mesh->mVertices[i].z;
                array.add(vector);

                if(mesh->HasNormals())
                {
                    vector.x = mesh->mNormals[i].x;
                    vector.y = mesh->mNormals[i].y;
                    vector.z = mesh->mNormals[i].z;
                    array[i].normal = vector;
                }
                if(mesh->mTextureCoords[0]) // does the mesh contain texture coordinates?
                {
                    glm::vec2 vec;
                    vec.x = mesh->mTextureCoords[0][i].x;
                    vec.y = mesh->mTextureCoords[0][i].y;
                    array[i].texCoord = vec;
                } else
                    array[i].texCoord = glm::vec2(0.0f, 0.0f);
            }

            std::vector<GLuint> arr;
            for(unsigned int i = 0; i < mesh->mNumFaces; i++)
            {
                aiFace face = mesh->mFaces[i];
                for(unsigned int j = 0; j < face.mNumIndices; j++)
                    arr.push_back(face.mIndices[j]);
            }
            insize = arr.size();
            aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

            //std::vector<Material> mats;

            std::vector<Material> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
           // mats.insert(mats.end(), diffuseMaps.begin(), diffuseMaps.end());

//            std::vector<Material> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
//            mats.insert(mats.end(), specularMaps.begin(), specularMaps.end());
//
//            std::vector<Material> normalMaps = loadMaterialTextures(material, aiTextureType_HEIGHT, "texture_normal");
//            mats.insert(mats.end(), normalMaps.begin(), normalMaps.end());
//
//            std::vector<Material> heightMaps = loadMaterialTextures(material, aiTextureType_AMBIENT, "texture_height");
//            mats.insert(mats.end(), heightMaps.begin(), heightMaps.end());

            models.emplace_back(array, arr);
        }

        std::vector<Material> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typ)
        {
            std::vector<Material> textures;
            for(unsigned int i = 0; i < mat->GetTextureCount(type); i++)
            {
                aiString str;
                mat->GetTexture(type, i, &str);

                bool skip = false;
                for(auto& j: materials)
                {
                    // if(std::strcmp(j.texture.getFilePath().data(), str.C_Str()) == 0)
                    {
                        //textures.push_back(j);
                        //    skip = true;
                        //    break;
                    }
                }
                if(!skip)
                {
                    auto texture = std::make_unique<Texture>();
                    texture->LoadFromFile(str.C_Str());
                    textures.emplace_back(std::move(texture), typ);
                    // materials.emplace_back(texture, typ);
                }
            }
            return textures;
        }

        void render()
        {
            glBindTexture(GL_TEXTURE_2D, txt.textureID);
            for(auto& m: models)
                m.render();
            glBindTexture(GL_TEXTURE_2D, 0);
        }
    };
}

#endif //PALKA_MESH_H
