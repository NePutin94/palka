//
// Created by dimka on 11/30/2021.
//

#ifndef PALKA_MESH_H
#define PALKA_MESH_H

#include "VertexArray.h"
#include "ConsoleLog.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

namespace palka
{
    class Mesh
    {
    private:
        VertexArray model_data;
        std::string path;
        std::vector<Mesh> meshes;
        std::vector<int> _meshStartIndices;
        std::vector<int> _meshMaterialIndices;
        std::vector<int> _meshVerticesCount;
        VertexBufferObject vbo;
        VertexArrayObject vao;
        VertexBufferObject indecesVbo;
        int insize;
    public:
        Mesh() : indecesVbo(BufferObject::BufferType::EAB)
        {}

        Mesh(std::string_view path) : path(path), indecesVbo(BufferObject::BufferType::EAB)
        {

        }

        void load(std::string_view path)
        {
            this->path = path;
            Assimp::Importer importer;
            const aiScene* scene = importer.ReadFile(this->path,
                                                     aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
            if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) // if is Not Zero
            {
                Console::addLog("ASSIMP LOAD ERROR", Console::error);
                return;
            }

            processMesh(scene);
        }

        void processMesh(const aiScene* scene)
        {
            auto vertexCount = 0;
            palka::VertArray array;

            const auto mesh = scene->mMeshes[0];
            for(unsigned int i = 0; i < mesh->mNumVertices; i++)
            {
                glm::vec3 vector; // we declare a placeholder vector since assimp uses its own vector class that doesn't directly convert to glm's vec3 class so we transfer the data to this placeholder glm::vec3 first.
                vector.x = mesh->mVertices[i].x;
                vector.y = mesh->mVertices[i].y;
                vector.z = mesh->mVertices[i].z;
                array.add(vector);

                if (mesh->HasNormals())
                {
                    vector.x = mesh->mNormals[i].x;
                    vector.y = mesh->mNormals[i].y;
                    vector.z = mesh->mNormals[i].z;
                    array[i].normal = vector;
                }
            }

            std::vector<GLuint> arr;
            for(unsigned int i = 0; i < scene->mMeshes[0]->mNumFaces; i++)
            {
                aiFace face = scene->mMeshes[0]->mFaces[i];
                for(unsigned int j = 0; j < face.mNumIndices; j++)
                    arr.push_back(face.mIndices[j]);
            }

            vao.create(vertexCount);
            vao.bind();
            vbo.create(sizeof(Vertex) * array.getSize());
            indecesVbo.create(sizeof(GLuint) * arr.size());
            insize = arr.size();
            vbo.setData(&array[0], sizeof(Vertex) * array.getSize(), &array[0].pos.x);
            indecesVbo.setData(&arr[0], sizeof(GLuint) * arr.size(), &arr[0]);
            vao.setPointers(vbo, sizeof(Vertex));

            vbo.unbind();
            indecesVbo.unbind();
            vao.unbind();

//            vbo_coords.create(model_data.coords.size());
//            vbo_normals.create(model_data.normals.size());
//            // vbo_vert_color.create(vertex_color.size());
//            // vbo_tex_coords.create(texture_coords.size());
//
//            vbo_coords.setData(model_data.coords.data(), sizeof(Vec3f) * model_data.coords.size(), &model_data.coords[0].x);
//            vbo_normals.setData(model_data.normals.data(), sizeof(Vec3f) * model_data.normals.size(), &model_data.normals[0].x);
//            //  vbo_vert_color.setData(vertex_color.data(), sizeof(Color) * vertex_color.size(), &vertex_color[0].r);
//            //   vbo_tex_coords.setData(texture_coords.data(), sizeof(Vec2f) * texture_coords.size(), &texture_coords[0].x);
//
//            vao.bind();
//            vao.setPointer_u(vbo_coords, 0, 3, GL_FLOAT, sizeof(Vec3f), 0);
//            //  vao.setPointer_u(vbo_vert_color, 1, 3, GL_FLOAT, sizeof(Color), 0);
//            //  vao.setPointer_u(vbo_tex_coords, 2, 3, GL_FLOAT, sizeof(Vec2f), 0);
//            vao.setPointer_u(vbo_normals, 3, 3, GL_FLOAT, sizeof(Vec3f), 0);
//            vao.unbind();
        }

        void render()
        {
            vao.bind();
            glDrawElements(GL_TRIANGLES, insize, GL_UNSIGNED_INT, 0);
        }
    };
}

#endif //PALKA_MESH_H
