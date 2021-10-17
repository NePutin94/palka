//
// Created by NePutin on 9/15/2021.
//

#include "Renderer.h"

void palka::Renderer::VAODraw(palka::VertexBuffer array, palka::Shader s, palka::RenderContext context)
{
    applyBlend(context.blend);

    if (context.texture != nullptr)
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
    for(int i = 0;i<10;++i)
    {
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, cubePositions[i]);
        model = glm::rotate(model, glm::radians(angle * (i+1)), glm::vec3(1.0f, 0 % 10, 0.5f));
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

void palka::Renderer::VAODraw(palka::VertexArrayObject array, palka::Shader s, palka::RenderContext context)
{
    applyBlend(context.blend);

    if (context.texture != nullptr)
        context.texture->bind();
    static float angle = 0;
    angle += 0.005;
    array.bind();

    glm::mat4 projection = glm::mat4(1.0f);
    projection = camera.getProjectionMatrix();
    auto _view = camera.getViewMatrix();
    t.bind();
    glUseProgram(s.getId());
    s.updateUBO(glm::value_ptr(projection), sizeof(float[16]), sizeof(float[16]));
    s.updateUBO(glm::value_ptr(_view), sizeof(float[16]) * 2, sizeof(float[16]));
    for(int i = 0;i<10;++i)
    {
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, cubePositions[i]);
        model = glm::rotate(model, glm::radians(angle * (i+1)), glm::vec3(1.0f, 0 % 10, 0.5f));
        s.updateUBO(glm::value_ptr(model), 0, sizeof(float[16]));
        // auto mat = glm::lookAt(glm::vec3(0.0f, 0.0f, 20.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
//            s.setValue("model", model);
//            s.setValue("projection", projection);
        glDrawArrays(GL_TRIANGLES, static_cast<GLint>(0), array.getSize());
    }
    glUseProgram(0);
    array.unbind();
}
