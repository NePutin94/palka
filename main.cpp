#include "palka_core/Engine.h"

using namespace std;

int main(int argc, char* argv[])
{
    palka::Engine e({1280, 720});
    e.run();
    return 0;
}
//
//#include <glad/gl.h>
//#include <GLFW/glfw3.h>
//#include <stb_image.h>
//
//#include <glm/glm.hpp>
//#include <glm/gtc/matrix_transform.hpp>
//#include <glm/gtc/type_ptr.hpp>
//#include <cstdlib>
//#include <iostream>
//#include <ctime>
//#include <string>
//#include <fstream>
//#include <sstream>
//#include <iostream>
//#include "palka_core/VertexData.h"
//#include "palka_core/VertexBuffer.h"
//
//class Shader
//{
//public:
//    unsigned int ID;
//    // constructor generates the shader on the fly
//    // ------------------------------------------------------------------------
//    Shader(const char* vertexPath, const char* fragmentPath, const char* geometryPath = nullptr)
//    {
//        // 1. retrieve the vertex/fragment source code from filePath
//        std::string vertexCode;
//        std::string fragmentCode;
//        std::string geometryCode;
//        std::ifstream vShaderFile;
//        std::ifstream fShaderFile;
//        std::ifstream gShaderFile;
//        // ensure ifstream objects can throw exceptions:
//        vShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
//        fShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
//        gShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
//        try
//        {
//            // open files
//            vShaderFile.open(vertexPath);
//            fShaderFile.open(fragmentPath);
//            std::stringstream vShaderStream, fShaderStream;
//            // read file's buffer contents into streams
//            vShaderStream << vShaderFile.rdbuf();
//            fShaderStream << fShaderFile.rdbuf();
//            // close file handlers
//            vShaderFile.close();
//            fShaderFile.close();
//            // convert stream into string
//            vertexCode = vShaderStream.str();
//            fragmentCode = fShaderStream.str();
//            // if geometry shader path is present, also load a geometry shader
//            if(geometryPath != nullptr)
//            {
//                gShaderFile.open(geometryPath);
//                std::stringstream gShaderStream;
//                gShaderStream << gShaderFile.rdbuf();
//                gShaderFile.close();
//                geometryCode = gShaderStream.str();
//            }
//        }
//        catch (std::ifstream::failure& e)
//        {
//            std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
//        }
//        const char* vShaderCode = vertexCode.c_str();
//        const char * fShaderCode = fragmentCode.c_str();
//        // 2. compile shaders
//        unsigned int vertex, fragment;
//        // vertex shader
//        vertex = glCreateShader(GL_VERTEX_SHADER);
//        glShaderSource(vertex, 1, &vShaderCode, NULL);
//        glCompileShader(vertex);
//        checkCompileErrors(vertex, "VERTEX");
//        // fragment Shader
//        fragment = glCreateShader(GL_FRAGMENT_SHADER);
//        glShaderSource(fragment, 1, &fShaderCode, NULL);
//        glCompileShader(fragment);
//        checkCompileErrors(fragment, "FRAGMENT");
//        // if geometry shader is given, compile geometry shader
//        unsigned int geometry;
//        if(geometryPath != nullptr)
//        {
//            const char * gShaderCode = geometryCode.c_str();
//            geometry = glCreateShader(GL_GEOMETRY_SHADER);
//            glShaderSource(geometry, 1, &gShaderCode, NULL);
//            glCompileShader(geometry);
//            checkCompileErrors(geometry, "GEOMETRY");
//        }
//        // shader Program
//        ID = glCreateProgram();
//        glAttachShader(ID, vertex);
//        glAttachShader(ID, fragment);
//        if(geometryPath != nullptr)
//            glAttachShader(ID, geometry);
//        glLinkProgram(ID);
//        checkCompileErrors(ID, "PROGRAM");
//        // delete the shaders as they're linked into our program now and no longer necessery
//        glDeleteShader(vertex);
//        glDeleteShader(fragment);
//        if(geometryPath != nullptr)
//            glDeleteShader(geometry);
//
//    }
//    // activate the shader
//    // ------------------------------------------------------------------------
//    void use()
//    {
//        glUseProgram(ID);
//    }
//    // utility uniform functions
//    // ------------------------------------------------------------------------
//    void setBool(const std::string &name, bool value) const
//    {
//        glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
//    }
//    // ------------------------------------------------------------------------
//    void setInt(const std::string &name, int value) const
//    {
//        glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
//    }
//    // ------------------------------------------------------------------------
//    void setFloat(const std::string &name, float value) const
//    {
//        glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
//    }
//    // ------------------------------------------------------------------------
//    void setVec2(const std::string &name, const glm::vec2 &value) const
//    {
//        glUniform2fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
//    }
//    void setVec2(const std::string &name, float x, float y) const
//    {
//        glUniform2f(glGetUniformLocation(ID, name.c_str()), x, y);
//    }
//    // ------------------------------------------------------------------------
//    void setVec3(const std::string &name, const glm::vec3 &value) const
//    {
//        glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
//    }
//    void setVec3(const std::string &name, float x, float y, float z) const
//    {
//        glUniform3f(glGetUniformLocation(ID, name.c_str()), x, y, z);
//    }
//    // ------------------------------------------------------------------------
//    void setVec4(const std::string &name, const glm::vec4 &value) const
//    {
//        glUniform4fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
//    }
//    void setVec4(const std::string &name, float x, float y, float z, float w)
//    {
//        glUniform4f(glGetUniformLocation(ID, name.c_str()), x, y, z, w);
//    }
//    // ------------------------------------------------------------------------
//    void setMat2(const std::string &name, const glm::mat2 &mat) const
//    {
//        glUniformMatrix2fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
//    }
//    // ------------------------------------------------------------------------
//    void setMat3(const std::string &name, const glm::mat3 &mat) const
//    {
//        glUniformMatrix3fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
//    }
//    // ------------------------------------------------------------------------
//    void setMat4(const std::string &name, const glm::mat4 &mat) const
//    {
//        glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
//    }
//
//private:
//    // utility function for checking shader compilation/linking errors.
//    // ------------------------------------------------------------------------
//    void checkCompileErrors(GLuint shader, std::string type)
//    {
//        GLint success;
//        GLchar infoLog[1024];
//        if(type != "PROGRAM")
//        {
//            glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
//            if(!success)
//            {
//                glGetShaderInfoLog(shader, 1024, NULL, infoLog);
//                std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
//            }
//        }
//        else
//        {
//            glGetProgramiv(shader, GL_LINK_STATUS, &success);
//            if(!success)
//            {
//                glGetProgramInfoLog(shader, 1024, NULL, infoLog);
//                std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
//            }
//        }
//    }
//};
//void framebuffer_size_callback(GLFWwindow* window, int width, int height);
//void processInput(GLFWwindow *window);
//
//// settings
//const unsigned int SCR_WIDTH = 800;
//const unsigned int SCR_HEIGHT = 600;
//
//int main()
//{
//    // glfw: initialize and configure
//    // ------------------------------
//    glfwInit();
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//
//    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
//    if (window == NULL)
//    {
//        std::cout << "Failed to create GLFW window" << std::endl;
//        glfwTerminate();
//        return -1;
//    }
//    glfwMakeContextCurrent(window);
//    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
//
//    if (!gladLoadGL(glfwGetProcAddress))
//    {
//        std::cout << "Failed to initialize GLAD" << std::endl;
//        return -1;
//    }
//
//
//    glEnable(GL_DEPTH_TEST);
//
//    Shader ourShader("Data\\Shaders\\Default.vert", "Data\\Shaders\\Default.frag");
//
//    float vertices[] = {
//            -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
//            0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
//            0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
//            0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
//            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
//            -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
//
//            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
//            0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
//            0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
//            0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
//            -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
//            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
//
//            -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
//            -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
//            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
//            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
//            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
//            -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
//
//            0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
//            0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
//            0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
//            0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
//            0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
//            0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
//
//            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
//            0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
//            0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
//            0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
//            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
//            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
//
//            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
//            0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
//            0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
//            0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
//            -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
//            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
//    };
//    palka::VertArray cub;
//    palka::VertexBuffer buff;
//    cub.add({{-0.5f, -0.5f,  -0.5f}, palka::Color{255,0,0}});
//    cub.add({{ 0.5f, -0.5f,  -0.5f}, palka::Color{255,0,0}});
//    cub.add({{ 0.5f,  0.5f,  -0.5f}, palka::Color{255,0,0}});
//    cub.add({{ 0.5f,  0.5f,  -0.5f}, palka::Color{255,0,0}});
//    cub.add({{ -0.5f,  0.5f, -0.5f}, palka::Color{255,0,0}});
//    cub.add({{ -0.5f, -0.5f, -0.5f}, palka::Color{255,0,0}});
//    cub.add({{ -0.5f, -0.5f,  0.5f}, palka::Color{0,0,255}});
//    cub.add({{ 0.5f, -0.5f,   0.5f}, palka::Color{0,0,255}});
//    cub.add({{ 0.5f,  0.5f,   0.5f}, palka::Color{0,0,255}});
//    cub.add({{ 0.5f,  0.5f,   0.5f}, palka::Color{0,0,255}});
//    cub.add({{ -0.5f,  0.5f,  0.5f}, palka::Color{0,0,255}});
//    cub.add({{ -0.5f, -0.5f,  0.5f}, palka::Color{0,0,255}});
//    cub.add({{ -0.5f,  0.5f,  0.5f}, palka::Color{0,255,0}});
//    cub.add({{ -0.5f,  0.5f, -0.5f}, palka::Color{0,255,0}});
//    cub.add({{ -0.5f, -0.5f, -0.5f}, palka::Color{0,255,0}});
//    cub.add({{ -0.5f, -0.5f, -0.5f}, palka::Color{0,255,0}});
//    cub.add({{ -0.5f, -0.5f,  0.5f}, palka::Color{0,255,0}});
//    cub.add({{ -0.5f,  0.5f,  0.5f}, palka::Color{0,255,0}});
//    cub.add({{ 0.5f,  0.5f,   0.5f}, palka::Color{255,0,255}});
//    cub.add({{ 0.5f,  0.5f,  -0.5f}, palka::Color{255,0,255}});
//    cub.add({{ 0.5f, -0.5f,  -0.5f}, palka::Color{255,0,255}});
//    cub.add({{ 0.5f, -0.5f,  -0.5f}, palka::Color{255,0,255}});
//    cub.add({{ 0.5f, -0.5f,   0.5f}, palka::Color{255,0,255}});
//    cub.add({{ 0.5f,  0.5f,   0.5f}, palka::Color{255,0,255}});
//    cub.add({{ -0.5f, -0.5f, -0.5f}, palka::Color{255,255,0}});
//    cub.add({{ 0.5f, -0.5f,  -0.5f}, palka::Color{255,255,0}});
//    cub.add({{ 0.5f, -0.5f,   0.5f}, palka::Color{255,255,0}});
//    cub.add({{ 0.5f, -0.5f,   0.5f}, palka::Color{255,255,0}});
//    cub.add({{ -0.5f, -0.5f,  0.5f}, palka::Color{255,255,0}});
//    cub.add({{ -0.5f, -0.5f, -0.5f}, palka::Color{255,255,0}});
//    cub.add({{ -0.5f,  0.5f, -0.5f}, palka::Color{90,155,180}});
//    cub.add({{ 0.5f,  0.5f,  -0.5f}, palka::Color{90,155,180}});
//    cub.add({{ 0.5f,  0.5f,   0.5f}, palka::Color{90,155,180}});
//    cub.add({{ 0.5f,  0.5f,   0.5f}, palka::Color{90,155,180}});
//    cub.add({{ -0.5f,  0.5f,  0.5f}, palka::Color{90,155,180}});
//    cub.add({{ -0.5f,  0.5f, -0.5f}, palka::Color{90,155,180}});
//
//    buff.create(cub.getSize());
//    buff.update(&cub[0], cub.getSize(), ourShader.ID);
//
//    // world space positions of our cubes
//    glm::vec3 cubePositions[] = {
//            glm::vec3( 0.0f,  0.0f,  0.0f),
//            glm::vec3( 2.0f,  5.0f, -15.0f),
//            glm::vec3(-1.5f, -2.2f, -2.5f),
//            glm::vec3(-3.8f, -2.0f, -12.3f),
//            glm::vec3( 2.4f, -0.4f, -3.5f),
//            glm::vec3(-1.7f,  3.0f, -7.5f),
//            glm::vec3( 1.3f, -2.0f, -2.5f),
//            glm::vec3( 1.5f,  2.0f, -2.5f),
//            glm::vec3( 1.5f,  0.2f, -1.5f),
//            glm::vec3(-1.3f,  1.0f, -1.5f)
//    };
////    unsigned int VBO, VAO;
////    glGenVertexArrays(1, &VAO);
////    glGenBuffers(1, &VBO);
////
////    glBindVertexArray(VAO);
////
////    glBindBuffer(GL_ARRAY_BUFFER, VBO);
////    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
////
////    // position attribute
////    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
////    glEnableVertexAttribArray(0);
////    // texture coord attribute
////    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
////    glEnableVertexAttribArray(1);
//
//    ourShader.use();
//
//    std::srand(std::time(nullptr)); // use current time as seed for random generator
//    // render loop
//    // -----------
//    while (!glfwWindowShouldClose(window))
//    {
//        // input
//        // -----
//        processInput(window);
//
//        // render
//        // ------
//        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
//        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // also clear the depth buffer now!
//
//        ourShader.use();
//
//        // create transformations
//        glm::mat4 view          = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
//        glm::mat4 projection    = glm::mat4(1.0f);
//        projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
//        view       = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
//        // pass transformation matrices to the shader
//        ourShader.setMat4("projection", projection); // note: currently we set the projection matrix each frame, but since the projection matrix rarely changes it's often best practice to set it outside the main loop only once.
//        ourShader.setMat4("view", view);
//        // render boxes
//        static float angle = 0;
//        angle += 1;
//        //glBindVertexArray(VAO);
//        buff.bind();
//        for (unsigned int i = 0; i < 10; i++)
//        {
//            glm::mat4 model = glm::mat4(1.0f);
//            model = glm::translate(model, cubePositions[i]);
//            model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, i % 10, 0.5f));
//            ourShader.setMat4("model", model);
//
//            glDrawArrays(GL_TRIANGLES, 0, 36);
//        }
//
//        glfwSwapBuffers(window);
//        glfwPollEvents();
//    }
//
//   // glDeleteVertexArrays(1, &VAO);
//   // glDeleteBuffers(1, &VBO);
//
//    glfwTerminate();
//    return 0;
//}
//
//// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
//// ---------------------------------------------------------------------------------------------------------
//void processInput(GLFWwindow *window)
//{
//    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
//        glfwSetWindowShouldClose(window, true);
//}
//
//// glfw: whenever the window size changed (by OS or user resize) this callback function executes
//// ---------------------------------------------------------------------------------------------
//void framebuffer_size_callback(GLFWwindow* window, int width, int height)
//{
//    // make sure the viewport matches the new window dimensions; note that width and
//    // height will be significantly larger than specified on retina displays.
//    glViewport(0, 0, width, height);
//}