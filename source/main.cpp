#ifdef _WIN32
#include <Windows.h>
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

class MyWindow : public He::App::GLFW3Window {
public:
    void OnKeyDown(He::App::Input::Keys key, He::App::Input::KeyModifiers mods) override {
        if (key == He::App::Input::Keys::Escape) glfwSetWindowShouldClose(this->_windowHandler, true);
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
        glDisable(GL_CULL_FACE);
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        He::Utils::Array<glm::vec3> forward_vertices = {
            {-0.5f, -0.5f,  0.5f},  // 0
             {0.5f, -0.5f,  0.5f},  // 1
             {0.5f,  0.5f,  0.5f},  // 2
            {-0.5f,  0.5f,  0.5f},  // 3
        };
        He::Utils::Array<glm::vec3> backward_vertices = {
            {-0.5f, -0.5f, -0.5f},  // 4
             {0.5f, -0.5f, -0.5f},  // 5
             {0.5f,  0.5f, -0.5f},  // 6
            {-0.5f,  0.5f, -0.5f},  // 7
        };

        He::Utils::Array<glm::vec3> vertices(8);
        He::Utils::Array<glm::vec3> normals(vertices.size());
        He::Utils::Array<glm::vec2> uvs(vertices.size());

        He::Utils::Array<GLuint> indices(vertices.size()/4*6);
        /*{
            0, 1, 3,
            1, 2, 3
        };*/

        for (int i = 0; i < normals.size(); i++) {
            normals[i] = glm::vec3(0.1f, 0.9f, 0.1f);
            uvs[i] = glm::vec2(0.f, 0.f);
        }

        for (int i = 0; i < vertices.size() / 4; i++) {
            indices[i*4 + 0] = i*4 + 0;
            indices[i*4 + 1] = i*4 + 1;
            indices[i*4 + 2] = i*4 + 2;
            indices[i*4 + 3] = i*4 + 2;
            indices[i*4 + 4] = i*4 + 3;
            indices[i*4 + 5] = i*4 + 0;
        }

        for (int i = 0; i < 4; i++) {
            vertices[i] = forward_vertices[i];
            vertices[i + 4] = backward_vertices[i];
        }


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
        projection = glm::perspective(glm::radians(45.0f), (GLfloat)640 / (GLfloat)480, 0.1f, 100.0f);


            shader.SetUniform("model", model);
            shader.SetUniform("projection", projection);
            shader.SetUniform("icolor", glm::vec3(1.f));

        while(!window.ShouldClose()){
            glClear(GL_COLOR_BUFFER_BIT);

            shader.SetUniform("view", glm::translate(view, cameraPosition));
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
    system("pause");
#endif

    return 0;
}