//
// Created by NePutin on 9/15/2021.
//

#include "Renderer.h"

void palka::Renderer::VAODraw(palka::VertexBuffer array, palka::Shader s, palka::RenderContext context)
{
    applyBlend(context.blend);

    if(context.texture != nullptr)
        context.texture->bind();
    static float angle = 0;
    angle += 0.005;
    array.bind();

    glm::mat4 projection = glm::mat4(1.0f);
    projection = glm::perspective(glm::radians(45.0f), (float) size.x / (float) size.y, 0.1f, 100.0f);
    auto _view = camera.getViewMatrix();
    t.bind();
    glUseProgram(s.getId());
    s.updateUBO(glm::value_ptr(projection), sizeof(float[16]), sizeof(float[16]));
    s.updateUBO(glm::value_ptr(_view), sizeof(float[16]) * 2, sizeof(float[16]));
    for(int i = 0; i < 10; ++i)
    {
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, cubePositions[i]);
        model = glm::rotate(model, glm::radians(angle * (i + 1)), glm::vec3(1.0f, 0 % 10, 0.5f));
        s.updateUBO(glm::value_ptr(model), 0, sizeof(float[16]));
        // auto mat = glm::lookAt(glm::vec3(0.0f, 0.0f, 20.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
//            s.setValue("model", model);
//            s.setValue("projection", projection);
        glDrawArrays(GL_TRIANGLES, static_cast<GLint>(0), array.getSize());
    }
    glUseProgram(0);
    array.unbind();
}

void palka::Renderer::draw(palka::VertArray array, palka::RenderContext context)
{
    glReset();
    glLoadMatrixf(context.transform.getMatrix());
    applyBlend(context.blend);
    applyView();
    if(context.texture != nullptr)
        context.texture->bind();

    Vertex* pointer = &array[0];
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glVertexPointer(2,
                    GL_FLOAT,
                    sizeof(Vertex),
                    &pointer->pos.x);

    glColorPointer(3,
                   GL_UNSIGNED_BYTE,
                   sizeof(Vertex),
                   &pointer->color.r);

    glTexCoordPointer(2, GL_FLOAT, sizeof(Vertex), &pointer->texCoord.x);

    glDrawArrays(VertArray::type_to_gl(array.getType()), static_cast<GLint>(0), array.getSize());
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void palka::Renderer::VAODraw(palka::VertexArrayObject& array, palka::Shader& s, palka::RenderContext context)
{
    applyBlend(context.blend);

    if(context.texture != nullptr)
        context.texture->bind();
    static float angle = 0;
    angle += 0.05;
    array.bind();

    glm::mat4 projection = glm::mat4(1.0f);
    projection = camera.getProjectionMatrix();
    auto _view = camera.getViewMatrix();
    //t.bind();
    glUseProgram(s.getId());
    s.updateUBO(glm::value_ptr(projection), 0, sizeof(float[16]));
    s.updateUBO(glm::value_ptr(_view), sizeof(float[16]), sizeof(float[16]));
//    for(int i = 0; i < 20; ++i)
//    {
//        glm::mat4 model = glm::mat4(1.0f);
//        model = glm::translate(model, cubePositions[i]);
//        model = glm::rotate(model, glm::radians(angle * (i + 1)), glm::vec3(1.0f, 0 % 10, 0.5f));
//        s.updateUBO(glm::value_ptr(model), 0, sizeof(float[16]));
//        glDrawArrays(GL_TRIANGLES, static_cast<GLint>(0), array.getSize());
//    }
    int offset = 2.5;
    Vec3f pos = {0, 0, 0};
    for(int i = 0; i < 5; ++i)
    {
        pos.x += offset;
        for(int j = 0; j < 5; ++j)
        {
            pos.y += offset;
            for(int k = 0; k < 5; ++k)
            {
                glm::mat4 model = glm::mat4(1.0f);
                pos.z += offset;
                model = glm::translate(model, pos);
                model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0 % 10, 0.5f));
                modelMat[i][j][k] = model;
            }
            pos.z = 0;
        }
        pos.y = 0;
    }
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0 % 10, 0.5f));
    s.updateUBO(glm::value_ptr(model), sizeof(float[16]) * 2, sizeof(float[16]));

    s.setValue("offsets", &modelMat[0][0][0], 125);
    glDrawArraysInstanced(GL_TRIANGLES, static_cast<GLint>(0), array.getSize(), 125);
}

void palka::Renderer::VAODraw2(palka::VertexArrayObject& array, palka::Shader& s, palka::RenderContext context)
{
    applyBlend(context.blend);

    if(context.texture != nullptr)
        context.texture->bind();

    static float angle = 0;
    angle += 0.05;
    array.bind();

    glm::mat4 projection = glm::mat4(1.0f);
    projection = camera.getProjectionMatrix();
    auto _view = camera.getViewMatrix();

    glUseProgram(s.getId());

    s.updateUBO(glm::value_ptr(projection), 0, sizeof(float[16]));
    s.updateUBO(glm::value_ptr(_view), sizeof(float[16]), sizeof(float[16]));

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, {-10, 0, -10});
    //model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0 % 10, 0.5f));
    s.updateUBO(glm::value_ptr(model), sizeof(float[16]) * 2, sizeof(float[16]));

    glDrawArrays(GL_TRIANGLES, static_cast<GLint>(0), array.getSize());
}

void palka::Renderer::VAODtaw(palka::StaticMesh& m, palka::Shader& s, palka::RenderContext context)
{
    applyBlend(context.blend);

    if(context.texture != nullptr)
        context.texture->bind();
    static float angle = 0;
    angle += 0.05;

    glm::mat4 projection = glm::mat4(1.0f);
    projection = camera.getProjectionMatrix();
    auto _view = camera.getViewMatrix();
    //t.bind();

    glUseProgram(s.getId());

    s.updateUBO(glm::value_ptr(projection), 0, sizeof(float[16]));
    s.updateUBO(glm::value_ptr(_view), sizeof(float[16]), sizeof(float[16]));

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, {0, 0, 0});
    // model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0 % 10, 0.5f));
    s.updateUBO(glm::value_ptr(model), sizeof(float[16]) * 2, sizeof(float[16]));
    m.render();
    glUseProgram(0);
}

void palka::Renderer::VAODraw2(palka::VertexArrayObject& array, palka::Shader& s, palka::Vec3f pos, palka::RenderContext context)
{
    applyBlend(context.blend);

    if(context.texture != nullptr)
        context.texture->bind();

    static float angle = 0;
    angle += 0.05;
    array.bind();

    glm::mat4 projection = glm::mat4(1.0f);
    projection = camera.getProjectionMatrix();
    auto _view = camera.getViewMatrix();

    glUseProgram(s.getId());

    s.updateUBO(glm::value_ptr(projection), 0, sizeof(float[16]));
    s.updateUBO(glm::value_ptr(_view), sizeof(float[16]), sizeof(float[16]));

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, pos);
    //model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0 % 10, 0.5f));
    s.updateUBO(glm::value_ptr(model), sizeof(float[16]) * 2, sizeof(float[16]));

    glDrawArrays(GL_TRIANGLES, static_cast<GLint>(0), array.getSize());
}

void palka::Renderer::VAODraw3(palka::VertexArrayObject& array, palka::Shader& s, palka::RenderContext context)
{
    applyBlend(context.blend);

    if(context.texture != nullptr)
        context.texture->bind();

    static float angle = 0;
    angle += 0.05;
    array.bind();

    glm::mat4 projection = glm::mat4(1.0f);
    projection = camera.getProjectionMatrix();
    auto _view = camera.getViewMatrix();

    glUseProgram(s.getId());

    s.setValue("objectColor", {0.9f, 0.1f, 0.20f});
    s.setValue("lightColor", {0.9f, 0.9f, 1.0f});
    s.setValue("lightPos", {-5.f, 0.f, -5.f});
    s.setValue("viewPos", camera.cameraPos);

    s.updateUBO(glm::value_ptr(projection), 0, sizeof(float[16]));
    s.updateUBO(glm::value_ptr(_view), sizeof(float[16]), sizeof(float[16]));

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, {-10, 0, -10});
    //model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0 % 10, 0.5f));
    s.updateUBO(glm::value_ptr(model), sizeof(float[16]) * 2, sizeof(float[16]));

    glDrawArrays(GL_TRIANGLES, static_cast<GLint>(0), array.getSize());
}

void palka::Renderer::VAODtaw2(palka::StaticMesh& m, palka::Shader& s, palka::RenderContext context)
{
    applyBlend(context.blend);

    if(context.texture != nullptr)
        context.texture->bind();
    static float angle = 0;
    angle += 0.05;

    glm::mat4 projection = glm::mat4(1.0f);
    projection = camera.getProjectionMatrix();
    auto _view = camera.getViewMatrix();
    //t.bind();

    glUseProgram(s.getId());

    s.setValue("objectColor", {0.2f, 0.1f, 0.9f});
    s.setValue("lightColor", {1.f, 1.f, 0.1f});
    s.setValue("lightPos", {-5.f, 0.f, -5.f});
    s.setValue("viewPos", camera.cameraPos);

    s.updateUBO(glm::value_ptr(projection), 0, sizeof(float[16]));
    s.updateUBO(glm::value_ptr(_view), sizeof(float[16]), sizeof(float[16]));

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, {0, 0, 0});
    // model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0 % 10, 0.5f));
    s.updateUBO(glm::value_ptr(model), sizeof(float[16]) * 2, sizeof(float[16]));
    m.render();
    glUseProgram(0);
}

void palka::Renderer::VAODraw(palka::VertexArrayObject& array, palka::ShaderProgram& s, UniformBuffer& buff)
{
//    applyBlend(context.blend);
//
//    if(context.texture != nullptr)
//        context.texture->bind();

    static float angle = 0;
    angle += 0.05;
    array.bind();

    glm::mat4 projection = glm::mat4(1.0f);
    projection = camera.getProjectionMatrix();
    auto _view = camera.getViewMatrix();

    s.bind();
    //glUseProgram(s.getId());

//    s.setValue("objectColor", {0.9f, 0.1f, 0.20f});
//    s.setValue("lightColor", {0.9f, 0.9f, 1.0f});
//    s.setValue("lightPos", {-5.f, 0.f, -5.f});
//    s.setValue("viewPos", camera.cameraPos);

    buff.setData(glm::value_ptr(projection), 0, sizeof(float[16]));
    buff.setData(glm::value_ptr(_view), sizeof(float[16]), sizeof(float[16]));

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, {-10, 0, -10});
    //model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0 % 10, 0.5f));
    buff.setData(glm::value_ptr(model), sizeof(float[16]) * 2, sizeof(float[16]));

    glDrawArrays(GL_TRIANGLES, static_cast<GLint>(0), array.getSize());
}

void palka::Renderer::VAODraw2(palka::Mesh& m, palka::Shader& s, palka::RenderContext context)
{
    applyBlend(context.blend);

    if(context.texture != nullptr)
        context.texture->bind();

    glm::mat4 projection = glm::mat4(1.0f);
    projection = camera.getProjectionMatrix();
    auto _view = camera.getViewMatrix();

    glUseProgram(s.getId());

    s.setValue("objectColor", {0.2f, 0.1f, 0.9f});
    s.setValue("lightColor", {1.f, 1.f, 0.1f});
    s.setValue("lightPos", {-5.f, 0.f, -5.f});
    s.setValue("viewPos", camera.cameraPos);

    s.updateUBO(glm::value_ptr(projection), 0, sizeof(float[16]));
    s.updateUBO(glm::value_ptr(_view), sizeof(float[16]), sizeof(float[16]));

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, {0, 0, 0});
    // model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0 % 10, 0.5f));
    s.updateUBO(glm::value_ptr(model), sizeof(float[16]) * 2, sizeof(float[16]));
    m.render();
    glUseProgram(0);
}
