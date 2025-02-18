#ifdef _WIN32
#include <Windows.h>
#endif
#ifdef NDEBUG
#define _DEBUG
#endif
#include <fmt/core.h>
#include <iostream>
#include <string>
#include <fstream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <He/Log.hpp>
#include <He/App/GLFW3Window.hpp>
#include <He/Graphics/GL/ElementBufferObject.hpp>
#include <He/Graphics/GL/Shader.hpp>
#include <He/Graphics/GL/Mesh.hpp>

#include <He/Utils/Array.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/noise.hpp>
#include <He/Graphics/GL/Camera.hpp>

void callback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, GLchar const* message, void const* user_param)
{
    auto source_str = [source]() -> std::string {
        switch (source)
        {
            case GL_DEBUG_SOURCE_API: return "API";
            case GL_DEBUG_SOURCE_WINDOW_SYSTEM: return "WINDOW SYSTEM";
            case GL_DEBUG_SOURCE_SHADER_COMPILER: return "SHADER COMPILER";
            case GL_DEBUG_SOURCE_THIRD_PARTY:  return "THIRD PARTY";
            case GL_DEBUG_SOURCE_APPLICATION: return "APPLICATION";
            case GL_DEBUG_SOURCE_OTHER: return "OTHER";
            default: return "UNKNOWN";
        }
    }();

    auto type_str = [type]() {
        switch (type)
        {
            case GL_DEBUG_TYPE_ERROR: return "ERROR";
            case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: return "DEPRECATED_BEHAVIOR";
            case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR: return "UNDEFINED_BEHAVIOR";
            case GL_DEBUG_TYPE_PORTABILITY: return "PORTABILITY";
            case GL_DEBUG_TYPE_PERFORMANCE: return "PERFORMANCE";
            case GL_DEBUG_TYPE_MARKER:  return "MARKER";
            case GL_DEBUG_TYPE_OTHER: return "OTHER";
            default: return "UNKNOWN";
        }
    }();

    auto severity_str = [severity]() {
        switch (severity) {
            case GL_DEBUG_SEVERITY_NOTIFICATION: return "NOTIFICATION";
            case GL_DEBUG_SEVERITY_LOW: return "LOW";
            case GL_DEBUG_SEVERITY_MEDIUM: return "MEDIUM";
            case GL_DEBUG_SEVERITY_HIGH: return "HIGH";
            default: return "UNKNOWN";
        }
    }();

    DEBUG_WARN("{}, {}, {}, {}: {}", source_str, type_str, severity_str, id, message);
}
std::string readFile(const char* filePath) {
    std::ifstream file(filePath);

    std::string content;

    if (!file.is_open()) {
        throw std::runtime_error(fmt::format("Could not open file: {}", filePath));
    }

    std::string line;
    while (std::getline(file, line)) {
        content += line + "\n";
    }

    return content;
}
glm::vec3 cameraPosition = glm::vec3(0.0f, 0.0f, -3.0f);
int cullFaceC = 0;
bool polygonMode = false;

class MyWindow : public He::App::GLFW3Window {
public:
    void OnKeyDown(He::App::Input::Keys key, He::App::Input::KeyModifiers mods) override {
        if (key == He::App::Input::Keys::Escape) glfwSetWindowShouldClose(this->_windowHandler, true);
        if (!mods.Repeat) {
            if (key == He::App::Input::Keys::C) {
                cullFaceC++;
                if (cullFaceC > 2) cullFaceC = 0;

                glCullFace(cullFaceC == 0 ? GL_FRONT : cullFaceC == 1 ? GL_BACK : GL_FRONT_AND_BACK);
            }
            if (key == He::App::Input::Keys::P) {
                polygonMode = !polygonMode;
                glPolygonMode(GL_FRONT_AND_BACK, polygonMode ? GL_LINE : GL_FILL);
            }
        }
        switch (key) {
            case He::App::Input::Keys::A:
                cameraPosition.x += 0.1f;
                break;
            case He::App::Input::Keys::D:
                cameraPosition.x -= 0.1f;
            break;
            case He::App::Input::Keys::W:
                cameraPosition.z += 0.1f;
            break;
            case He::App::Input::Keys::S:
                cameraPosition.z -= 0.1f;
            break;

            case He::App::Input::Keys::Space:
                cameraPosition.y -= 0.1f;
            break;
            case He::App::Input::Keys::LeftShift:
                cameraPosition.y += 0.1f;
            break;
            default:break;
        }
    }
    void OnKeyUp(He::App::Input::Keys key, He::App::Input::KeyModifiers mods) override {

    }
};

int main(int argc, char* argv[]) {
#ifdef _WIN32
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, dwMode);
#endif

    DEBUG_ERROR("Something went wrong");
    if(!glfwInit()){
        const char* desc ;
        glfwGetError(&desc);

        if(desc){
            LOG_ERROR("Couldn't initialize GLFW3: {}", desc);
        }
        else {
            LOG_ERROR("Couldn't initialize GLFW3: unknown error");
        }
        return -1;
    }

    LOG_INFO("GLFW3 initialized successful");

    try {

        bool chunk[16][16][16];
        for (int x = 0; x < 16; x++) {
            for (int y = 0; y < 16; y++) {
                for (int z = 0; z < 16; z++) {
                    chunk[x][y][z] = glm::simplex(glm::vec3(x, y, z) / 10.0f) > 0;
                }
            }
        }
        MyWindow window;

        window.MakeContextCurrent();

        glewExperimental = GL_TRUE;
        auto glewInitStatus = glewInit();
        if (glewInitStatus != GLEW_OK)
        {
            LOG_ERROR("Couldn't initialiaze GLEW: {}", (const char*)glewGetErrorString(glewInitStatus));
            return -1;
        }

        LOG_INFO("GLEW initialized successful");

        glEnable(GL_DEBUG_OUTPUT);
        glDebugMessageCallback(callback, nullptr);

        struct Vertex {
            glm::vec3 Position;
            glm::vec3 Color;
        };
/*
    // Задняя грань (Z = -0.5)


    // Верхняя грань (Y = 0.5)
    -0.5f,  0.5f,  0.5f,  // 8
     0.5f,  0.5f,  0.5f,  // 9
     0.5f,  0.5f, -0.5f,  // 10
    -0.5f,  0.5f, -0.5f,  // 11

    // Нижняя грань (Y = -0.5)
    -0.5f, -0.5f,  0.5f,  // 12
     0.5f, -0.5f,  0.5f,  // 13
     0.5f, -0.5f, -0.5f,  // 14
    -0.5f, -0.5f, -0.5f,  // 15

    // Левая грань (X = -0.5)
    -0.5f, -0.5f, -0.5f,  // 16
    -0.5f, -0.5f,  0.5f,  // 17
    -0.5f,  0.5f,  0.5f,  // 18
    -0.5f,  0.5f, -0.5f,  // 19

    // Правая грань (X = 0.5)
     0.5f, -0.5f, -0.5f,  // 20
     0.5f, -0.5f,  0.5f,  // 21
     0.5f,  0.5f,  0.5f,  // 22
     0.5f,  0.5f, -0.5f   // 23*/
        glEnable(GL_CULL_FACE);
        glEnable(GL_DEPTH_TEST);
        //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glm::vec3 topLeft = glm::vec3(-1, 1, 0);
        glm::vec3 bottomLeft = glm::vec3(-1, -1, 0);
        glm::vec3 topRight = glm::vec3(1, 1, 0);
        glm::vec3 bottomRight = glm::vec3(1, -1, 0);
        glm::vec3 topLeftFront = glm::vec3(-1, 1, 1);
        glm::vec3 bottomLeftFront = glm::vec3(-1, -1, 1);
        glm::vec3 topRightFront = glm::vec3(1, 1, 1);
        glm::vec3 bottomRightFront = glm::vec3(1, -1, 1);
        glm::vec3 topLeftBack = glm::vec3(-1, 1, -1);
        glm::vec3 topRightBack = glm::vec3(1, 1, -1);
        glm::vec3 bottomLeftBack = glm::vec3(-1, -1, -1);
        glm::vec3 bottomRightBack = glm::vec3(1, -1, -1);

        He::Utils::Array<glm::vec3> forward_vertices = {
            bottomLeftFront,
            bottomRightFront,
            topRightFront,
            topLeftFront,
        };
        He::Utils::Array<glm::vec3> backward_vertices = {
            topLeftBack,
            topRightBack,
            bottomRightBack,
            bottomLeftBack,
        };
        He::Utils::Array<glm::vec3> up_vertices = {
            topLeftFront,
            topRightFront,
            topRightBack,
            topLeftBack,
        };

        He::Utils::Array<glm::vec3> down_vertices = {
            bottomLeftBack,
            bottomRightBack,
            bottomRightFront,
            bottomLeftFront,
        };
        He::Utils::Array<glm::vec3> right_vertices = {
            bottomRightBack,
            topRightBack,
            topRightFront,
            bottomRightFront,
        };
        He::Utils::Array<glm::vec3> left_vertices = {
            bottomLeftFront,
            topLeftFront,
            topLeftBack,
            bottomLeftBack,
        };

        std::vector<glm::vec3> listvertices, listnormals;
        glm::vec3 offset(-8, -8, -8);
        for(int x = 0; x < 16; ++x){
            for(int y = 0; y < 16; ++y){
                for(int z = 0; z < 16; ++z){
                    if(!chunk[x][y][z]) continue;
                    if(y == 15 || !chunk[x][y+1][z]) {
                        for(auto vert : up_vertices){
                            listvertices.push_back(vert + glm::vec3(x, y, z) + offset);
                            listnormals.push_back(glm::vec3(0.0f, -1.0f, 0.0f));
                        }
                    }
                    if(y == 0 || !chunk[x][y-1][z]){
                        for(auto vert : down_vertices){
                            listvertices.push_back(vert + glm::vec3(x, y, z) + offset);
                            listnormals.push_back(glm::vec3(0.0f, 1.0f, 0.0f));
                        }
                    }

                    if(x == 15 || !chunk[x+1][y][z]) {
                        for(auto vert : right_vertices){
                            listvertices.push_back(vert + glm::vec3(x, y, z) + offset);
                            listnormals.push_back(glm::vec3(-1.0f, 0.0f, 0.0f));
                        }
                    }
                    if(x == 0 || !chunk[x-1][y][z]){
                        for(auto vert : left_vertices){
                            listvertices.push_back(vert + glm::vec3(x, y, z) + offset);
                            listnormals.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
                        }
                    }

                    if(z == 15 || !chunk[x][y][z+1]) {
                        for(auto vert : forward_vertices){
                            listvertices.push_back(vert + glm::vec3(x, y, z) + offset);
                            listnormals.push_back(glm::vec3(0.0f, 0.0f, -1.0f));
                        }
                    }
                    if(z == 0 || !chunk[x][y][z-1]){
                        for(auto vert : backward_vertices){
                            listvertices.push_back(vert + glm::vec3(x, y, z) + offset);
                            listnormals.push_back(glm::vec3(0.0f, 0.0f, 1.0f));
                        }
                    }
                }
            }
        }

        He::Utils::Array<glm::vec3> vertices(listvertices.size());
        He::Utils::Array<glm::vec3> normals(vertices.size());
        He::Utils::Array<glm::vec2> uvs(vertices.size());

        He::Utils::Array<GLuint> indices(vertices.size()/4*6);

        for(int i = 0; i < listvertices.size(); ++i) {
            vertices[i] = listvertices[i];
        }
        /*{ 
            0, 1, 3,
            1, 2, 3 
        };*/

        for (int i = 0; i < normals.size(); i++) {
            normals[i] = listnormals[i];//glm::vec3(0.1f, 0.9f, 0.1f);
            uvs[i] = glm::vec2(0.f, 0.f);
        }

        for (int i = 0; i < vertices.size() / 4; i++) {
            indices[i*6 + 0] = i*4 + 0;
            indices[i*6 + 1] = i*4 + 1;
            indices[i*6 + 2] = i*4 + 2;
            indices[i*6 + 3] = i*4 + 0;
            indices[i*6 + 4] = i*4 + 2;
            indices[i*6 + 5] = i*4 + 3;
        }

        /*for (int i = 0; i < 4; i++) {
            vertices[i] = forward_vertices[i];
            vertices[i + 4] = backward_vertices[i];
            vertices[i + 8] = up_vertices[i];
            vertices[i + 12] = down_vertices[i];
            vertices[i + 16] = right_vertices[i];
            vertices[i + 20] = left_vertices[i];
        }*/


        He::Graphics::GL::Mesh mesh(vertices, normals, uvs, indices);

        mesh.Setup();

        auto fragmentShaderSource = readFile("resources/assets/shaders/default.frag");
        auto vertexShaderSource = readFile("resources/assets/shaders/default.vert");

        He::Graphics::GL::Shader shader(fragmentShaderSource.c_str(), vertexShaderSource.c_str());

        glm::mat4 model(1.f);
        glm::mat4 view(1.f);
        glm::mat4 projection(1.f);
        //model = glm::rotate(model, -55.0f, glm::vec3(1.0f, 0.0f, 0.0f));
        //view = glm::translate(view, cameraPosition);
        //model = glm::translate(model, glm::vec3(-8, -8, -8));

            shader.SetUniform("icolor", glm::vec3(0.4f, 0.8f, 0.3f));
            shader.SetUniform("lightColor", glm::vec3(1.0f)); 

        while(!window.ShouldClose()){
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            projection = glm::perspective(glm::radians(45.0f), (GLfloat)window.Width() / (GLfloat)window.Height(), 0.1f, 100.0f);
            model = glm::rotate(model, glm::radians((float)glfwGetTime() / 100.0f), glm::vec3(0.0f, 1.0f, 0.0f));
            glm::mat4 normalMatrix = glm::transpose(glm::inverse(model * view));

            shader.SetUniform("projection", projection);
            shader.SetUniform("normalMatrix", normalMatrix);
            shader.SetUniform("lightPosition", cameraPosition);
            shader.SetUniform("view", glm::translate(view, cameraPosition));
            shader.SetUniform("model", model);
            shader.Use();  


            mesh.Draw();
            window.SwapBuffers(); 

            glfwPollEvents();
        }

        glfwTerminate();
    }
    catch(std::exception& e){
        LOG_ERROR("{}", e.what());
    }

#ifdef _DEBUG  
    system("pause || read -rsp $'Press enter to continue...\n'"); 
#endif

    return 0;
}