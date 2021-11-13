#include "palka_core/Engine.h"

using namespace std;

int main(int argc, char* argv[])
{
    palka::Engine e({1280, 720});
    e.run();
    return 0;
}
////
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
//#include "palka_core/Engine.h"
//
//class Shader
//{
//public:
//    unsigned int ID;
//
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
//        vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
//        fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
//        gShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
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
//        const char* fShaderCode = fragmentCode.c_str();
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
//            const char* gShaderCode = geometryCode.c_str();
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
//
//    // activate the shader
//    // ------------------------------------------------------------------------
//    void use()
//    {
//        glUseProgram(ID);
//    }
//
//    // utility uniform functions
//    // ------------------------------------------------------------------------
//    void setBool(const std::string& name, bool value) const
//    {
//        glUniform1i(glGetUniformLocation(ID, name.c_str()), (int) value);
//    }
//
//    // ------------------------------------------------------------------------
//    void setInt(const std::string& name, int value) const
//    {
//        glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
//    }
//
//    // ------------------------------------------------------------------------
//    void setFloat(const std::string& name, float value) const
//    {
//        glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
//    }
//
//    // ------------------------------------------------------------------------
//    void setVec2(const std::string& name, const glm::vec2& value) const
//    {
//        glUniform2fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
//    }
//
//    void setVec2(const std::string& name, float x, float y) const
//    {
//        glUniform2f(glGetUniformLocation(ID, name.c_str()), x, y);
//    }
//
//    // ------------------------------------------------------------------------
//    void setVec3(const std::string& name, const glm::vec3& value) const
//    {
//        glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
//    }
//
//    void setVec3(const std::string& name, float x, float y, float z) const
//    {
//        glUniform3f(glGetUniformLocation(ID, name.c_str()), x, y, z);
//    }
//
//    // ------------------------------------------------------------------------
//    void setVec4(const std::string& name, const glm::vec4& value) const
//    {
//        glUniform4fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
//    }
//
//    void setVec4(const std::string& name, float x, float y, float z, float w)
//    {
//        glUniform4f(glGetUniformLocation(ID, name.c_str()), x, y, z, w);
//    }
//
//    // ------------------------------------------------------------------------
//    void setMat2(const std::string& name, const glm::mat2& mat) const
//    {
//        glUniformMatrix2fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
//    }
//
//    // ------------------------------------------------------------------------
//    void setMat3(const std::string& name, const glm::mat3& mat) const
//    {
//        glUniformMatrix3fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
//    }
//
//    // ------------------------------------------------------------------------
//    void setMat4(const std::string& name, const glm::mat4& mat) const
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
//                std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog
//                          << "\n -- --------------------------------------------------- -- " << std::endl;
//            }
//        } else
//        {
//            glGetProgramiv(shader, GL_LINK_STATUS, &success);
//            if(!success)
//            {
//                glGetProgramInfoLog(shader, 1024, NULL, infoLog);
//                std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog
//                          << "\n -- --------------------------------------------------- -- " << std::endl;
//            }
//        }
//    }
//};
//
//void framebuffer_size_callback(GLFWwindow* window, int width, int height);
//
//void mouse_callback(GLFWwindow* window, double xpos, double ypos);
//
//void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
//
//void processInput(GLFWwindow* window);
//
//// settings
//const unsigned int SCR_WIDTH = 800;
//const unsigned int SCR_HEIGHT = 600;
//
//// camera
//glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
//glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
//glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
//
//bool firstMouse = true;
//float yaw = -90.0f;    // yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right so we initially rotate a bit to the left.
//float pitch = 0.0f;
//float lastX = 800.0f / 2.0;
//float lastY = 600.0 / 2.0;
//float fov = 45.0f;
//
//// timing
//float deltaTime = 0.0f;    // time between current frame and last frame
//float lastFrame = 0.0f;
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
//#ifdef __APPLE__
//    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
//#endif
//
//    // glfw window creation
//    // --------------------
//    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
//    if(window == NULL)
//    {
//        std::cout << "Failed to create GLFW window" << std::endl;
//        glfwTerminate();
//        return -1;
//    }
//    glfwMakeContextCurrent(window);
//    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
//    glfwSetCursorPosCallback(window, mouse_callback);
//    glfwSetScrollCallback(window, scroll_callback);
//
//    // tell GLFW to capture our mouse
//    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
//
//    // glad: load all OpenGL function pointers
//    // ---------------------------------------
//    if(!gladLoadGL(glfwGetProcAddress))
//    {
//        std::cout << "Failed to initialize GLAD" << std::endl;
//        return -1;
//    }
//
//    // configure global opengl state
//    // -----------------------------
//    glEnable(GL_DEPTH_TEST);
//
//    // build and compile our shader zprogram
//    // ------------------------------------
//    //   Shader ourShader("Data\\Shaders\\Default.vert", "Data\\Shaders\\Default.frag");
//    palka::Shader s;
//    s.loadVF("Data\\Shaders\\Default.frag", "Data\\Shaders\\Default.vert");
//    s.UseUbo();
//    // set up vertex data (and buffer(s)) and configure vertex attributes
//    // ------------------------------------------------------------------
//    float vertices[] = {
//            -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
//            0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
//            0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
//            0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
//            -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
//            -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
//            -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
//            0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
//            0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
//            0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
//            -0.5f, 0.5f, 0.5f, 0.0f, 1.0f,
//            -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
//            -0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
//            -0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
//            -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
//            -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
//            -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
//            -0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
//            0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
//            0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
//            0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
//            0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
//            0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
//            0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
//            -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
//            0.5f, -0.5f, -0.5f, 1.0f, 1.0f,
//            0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
//            0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
//            -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
//            -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
//            -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
//            0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
//            0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
//            0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
//            -0.5f, 0.5f, 0.5f, 0.0f, 0.0f,
//            -0.5f, 0.5f, -0.5f, 0.0f, 1.0f
//    };
//    palka::VertArray cub;
//    cub.add({{-0.5f, -0.5f, -0.5f,},
//             {0.0f,  0.0f}});
//    cub.add({{0.5f, -0.5f, -0.5f,},
//             {1.0f, 0.0f}});
//    cub.add({{0.5f, 0.5f, -0.5f,},
//             {1.0f, 1.0f}});
//    cub.add({{0.5f, 0.5f, -0.5f,},
//             {1.0f, 1.0f}});
//    cub.add({{-0.5f, 0.5f, -0.5f,},
//             {0.0f,  1.0f}});
//    cub.add({{-0.5f, -0.5f, -0.5f,},
//             {0.0f,  0.0f}});
//    cub.add({{-0.5f, -0.5f, 0.5f,},
//             {0.0f,  0.0f}});
//    cub.add({{0.5f, -0.5f, 0.5f,},
//             {1.0f, 0.0f}});
//    cub.add({{0.5f, 0.5f, 0.5f,},
//             {1.0f, 1.0f}});
//    cub.add({{0.5f, 0.5f, 0.5f,},
//             {1.0f, 1.0f}});
//    cub.add({{-0.5f, 0.5f, 0.5f,},
//             {0.0f,  1.0f}});
//    cub.add({{-0.5f, -0.5f, 0.5f,},
//             {0.0f,  0.0f}});
//    cub.add({{-0.5f, 0.5f, 0.5f,},
//             {1.0f,  0.0f}});
//    cub.add({{-0.5f, 0.5f, -0.5f,},
//             {1.0f,  1.0f}});
//    cub.add({{-0.5f, -0.5f, -0.5f,},
//             {0.0f,  1.0f}});
//    cub.add({{-0.5f, -0.5f, -0.5f,},
//             {0.0f,  1.0f}});
//    cub.add({{-0.5f, -0.5f, 0.5f,},
//             {0.0f,  0.0f}});
//    cub.add({{-0.5f, 0.5f, 0.5f,},
//             {1.0f,  0.0f}});
//    cub.add({{0.5f, 0.5f, 0.5f,},
//             {1.0f, 0.0f}});
//    cub.add({{0.5f, 0.5f, -0.5f,},
//             {1.0f, 1.0f}});
//    cub.add({{0.5f, -0.5f, -0.5f,},
//             {0.0f, 1.0f}});
//    cub.add({{0.5f, -0.5f, -0.5f,},
//             {0.0f, 1.0f}});
//    cub.add({{0.5f, -0.5f, 0.5f,},
//             {0.0f, 0.0f}});
//    cub.add({{0.5f, 0.5f, 0.5f,},
//             {1.0f, 0.0f}});
//    cub.add({{-0.5f, -0.5f, -0.5f,},
//             {0.0f,  1.0f}});
//    cub.add({{0.5f, -0.5f, -0.5f,},
//             {1.0f, 1.0f}});
//    cub.add({{0.5f, -0.5f, 0.5f,},
//             {1.0f, 0.0f}});
//    cub.add({{0.5f, -0.5f, 0.5f,},
//             {1.0f, 0.0f}});
//    cub.add({{-0.5f, -0.5f, 0.5f,},
//             {0.0f,  0.0f}});
//    cub.add({{-0.5f, -0.5f, -0.5f,},
//             {0.0f,  1.0f}});
//    cub.add({{-0.5f, 0.5f, -0.5f,},
//             {0.0f,  1.0f}});
//    cub.add({{0.5f, 0.5f, -0.5f,},
//             {1.0f, 1.0f}});
//    cub.add({{0.5f, 0.5f, 0.5f,},
//             {1.0f, 0.0f}});
//    cub.add({{0.5f, 0.5f, 0.5f,},
//             {1.0f, 0.0f}});
//    cub.add({{-0.5f, 0.5f, 0.5f,},
//             {0.0f,  0.0f}});
//    cub.add({{-0.5f, 0.5f, -0.5f,},
//             {0.0f,  1.0f}});
//
//    palka::VertexBuffer buff{};
//    buff.create(cub.getSize());
//    buff.update(&cub[0], cub.getSize(), s.getId());
//
//    // world space positions of our cubes
//    glm::vec3 cubePositions[] = {
//            glm::vec3(0.0f, 0.0f, 0.0f),
//            glm::vec3(2.0f, 5.0f, -15.0f),
//            glm::vec3(-1.5f, -2.2f, -2.5f),
//            glm::vec3(-3.8f, -2.0f, -12.3f),
//            glm::vec3(2.4f, -0.4f, -3.5f),
//            glm::vec3(-1.7f, 3.0f, -7.5f),
//            glm::vec3(1.3f, -2.0f, -2.5f),
//            glm::vec3(1.5f, 2.0f, -2.5f),
//            glm::vec3(1.5f, 0.2f, -1.5f),
//            glm::vec3(-1.3f, 1.0f, -1.5f)
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
////    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*) 0);
////    glEnableVertexAttribArray(0);
////    // texture coord attribute
////    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*) (3 * sizeof(float)));
////    glEnableVertexAttribArray(1);
//
//
////    // load and create a texture
////    // -------------------------
////    unsigned int texture1, texture2;
////    // texture 1
////    // ---------
////    glGenTextures(1, &texture1);
////    glBindTexture(GL_TEXTURE_2D, texture1);
////    // set the texture wrapping parameters
////    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
////    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
////    // set texture filtering parameters
////    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
////    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
////    // load image, create texture and generate mipmaps
//////    int width, height, nrChannels;
//////    stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
//////   // unsigned char *data = stbi_load(FileSystem::getPath("resources/textures/container.jpg").c_str(), &width, &height, &nrChannels, 0);
//////    if (data)
//////    {
//////        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
//////        glGenerateMipmap(GL_TEXTURE_2D);
//////    }
//////    else
//////    {
//////        std::cout << "Failed to load texture" << std::endl;
//////    }
//////    stbi_image_free(data);
////    // texture 2
////    // ---------
////    glGenTextures(1, &texture2);
////    glBindTexture(GL_TEXTURE_2D, texture2);
////    // set the texture wrapping parameters
////    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
////    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
////    // set texture filtering parameters
////    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
////    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
////    // load image, create texture and generate mipmaps
////    data = stbi_load(FileSystem::getPath("resources/textures/awesomeface.png").c_str(), &width, &height, &nrChannels, 0);
////    if (data)
////    {
////        // note that the awesomeface.png has transparency and thus an alpha channel, so make sure to tell OpenGL the data type is of GL_RGBA
////        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
////        glGenerateMipmap(GL_TEXTURE_2D);
////    }
////    else
////    {
////        std::cout << "Failed to load texture" << std::endl;
////    }
////    stbi_image_free(data);
//
//    // tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
//    // -------------------------------------------------------------------------------------------
//    glUseProgram(s.getId());
//    s.setValue("texture1", 0);
//    s.setValue("texture2", 1);
//
//    palka::Texture t;
//    t.LoadFromFile("Data\\tex\\debug.png");
//
//    palka::Texture t2;
//    t2.LoadFromFile("Data\\tex\\Hero.png");
//    // render loop
//    // -----------
//    while(!glfwWindowShouldClose(window))
//    {
//        // per-frame time logic
//        // --------------------
//        float currentFrame = glfwGetTime();
//        deltaTime = currentFrame - lastFrame;
//        lastFrame = currentFrame;
//
//        // input
//        // -----
//        processInput(window);
//
//        // render
//        // ------
//        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
//        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//        // bind textures on corresponding texture units
//        glActiveTexture(GL_TEXTURE0);
//        t.bind();
//        glActiveTexture(GL_TEXTURE1);
//        t2.bind();
//
//        // activate shader
//        glUseProgram(s.getId());
//
//        // pass projection matrix to shader (note that in this case it could change every frame)
//        glm::mat4 projection = glm::perspective(glm::radians(fov), (float) SCR_WIDTH / (float) SCR_HEIGHT, 0.1f, 100.0f);
//        // camera/view transformation
//        glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
//        s.updateUBO(glm::value_ptr(projection), sizeof(float[16]), sizeof(float[16]));
//        s.updateUBO(glm::value_ptr(view), sizeof(float[16]) * 2, sizeof(float[16]));
//        // render boxes
//        // glBindVertexArray(VAO);
//        buff.bind();
//        for(unsigned int i = 0; i < 10; i++)
//        {
//            // calculate the model matrix for each object and pass it to shader before drawing
//            glm::mat4 model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
//            model = glm::translate(model, cubePositions[i]);
//            float angle = 20.0f * i;
//            model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
//            s.updateUBO(glm::value_ptr(model), 0, sizeof(float[16]));
//
//            glDrawArrays(GL_TRIANGLES, 0, 36);
//        }
//
//        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
//        // -------------------------------------------------------------------------------
//        glfwSwapBuffers(window);
//        glfwPollEvents();
//    }
//
//    // optional: de-allocate all resources once they've outlived their purpose:
//    // ------------------------------------------------------------------------
////    glDeleteVertexArrays(1, &VAO);
////    glDeleteBuffers(1, &VBO);
//
//    // glfw: terminate, clearing all previously allocated GLFW resources.
//    // ------------------------------------------------------------------
//    glfwTerminate();
//    return 0;
//}
//
//// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
//// ---------------------------------------------------------------------------------------------------------
//void processInput(GLFWwindow* window)
//{
//    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
//        glfwSetWindowShouldClose(window, true);
//
//    float cameraSpeed = 2.5 * deltaTime;
//    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
//        cameraPos += cameraSpeed * cameraFront;
//    if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
//        cameraPos -= cameraSpeed * cameraFront;
//    if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
//        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
//    if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
//        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
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
//
//// glfw: whenever the mouse moves, this callback is called
//// -------------------------------------------------------
//void mouse_callback(GLFWwindow* window, double xpos, double ypos)
//{
//    if(firstMouse)
//    {
//        lastX = xpos;
//        lastY = ypos;
//        firstMouse = false;
//    }
//
//    float xoffset = xpos - lastX;
//    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top
//    lastX = xpos;
//    lastY = ypos;
//
//    float sensitivity = 0.1f; // change this value to your liking
//    xoffset *= sensitivity;
//    yoffset *= sensitivity;
//
//    yaw += xoffset;
//    pitch += yoffset;
//
//    // make sure that when pitch is out of bounds, screen doesn't get flipped
//    if(pitch > 89.0f)
//        pitch = 89.0f;
//    if(pitch < -89.0f)
//        pitch = -89.0f;
//
//    glm::vec3 front;
//    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
//    front.y = sin(glm::radians(pitch));
//    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
//    cameraFront = glm::normalize(front);
//}
//
//// glfw: whenever the mouse scroll wheel scrolls, this callback is called
//// ----------------------------------------------------------------------
//void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
//{
//    fov -= (float) yoffset;
//    if(fov < 1.0f)
//        fov = 1.0f;
//    if(fov > 45.0f)
//        fov = 45.0f;
//}
//
