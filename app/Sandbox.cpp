#include "Sandbox.h"
#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <glm/mat3x3.hpp>

#include <iostream>
#include <string>

Sandbox::Sandbox()
{
    m_window = new Kouky3d::Window("Sanbox", 800, 600);
    m_secondWindow = new Kouky3d::Window("Second window", 800, 600);
}

Sandbox::~Sandbox()
{
    delete m_window;
}

void Sandbox::Init()
{
    std::cout << "Kouky3d version is " << Kouky3d::Version() << std::endl;
    
    
    m_window->Init();
    m_window->Show();

    // TODO: move that somewhere into the engine
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

    m_secondWindow->Init(false);
    m_secondWindow->Show();
}

void Sandbox::Update()
{
    // ----------------
    // setup triangle
    // ----------------

    float vertices[] = {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f,  0.5f, 0.0f
    };

    Kouky3d::VertexBuffer vertexBuffer(vertices, sizeof(vertices));
    Kouky3d::VertexArray vertexArray;
    vertexArray.AddBuffer(vertexBuffer);

    // REMARK: vertex array objects are not shareable between
    // different contexts. Vertex buffers are shareable!
    m_secondWindow->GiveContext();
    Kouky3d::VertexArray second_vertexArray;
    second_vertexArray.AddBuffer(vertexBuffer);

    // TODO: move shader source to own file
    const std::string vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";

    const std::string fragmentShaderSourceOrange = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\0";

    const std::string fragmentShaderSourcePink = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "    FragColor = vec4(1.0f, 0.5f, 0.8f, 1.0f);\n"
    "}\0";

    // REMARK:
    // glPrograms are not shareable between different contexts
    m_window->GiveContext();
    Kouky3d::Shader orangeShader(vertexShaderSource, fragmentShaderSourceOrange);

    m_secondWindow->GiveContext();
    Kouky3d::Shader pinkShader(vertexShaderSource, fragmentShaderSourcePink);

    // ----------------
    // end triangle setup
    // ----------------

    while(true)
    {
        m_window->GiveContext();
        Kouky3d::Renderer::ClearColor({0.3f, 0.3f, 0.3f, 1.0f});
        Kouky3d::Renderer::Clear();
        vertexArray.Bind();
        orangeShader.Bind();
        // TODO: move that somewhere into the engine
        glDrawArrays(GL_TRIANGLES, 0, 3);
        m_window->OnUpdate();

        m_secondWindow->GiveContext();
        Kouky3d::Renderer::ClearColor({0.3f, 0.3f, 0.3f, 1.0f});
        Kouky3d::Renderer::Clear();
        second_vertexArray.Bind();     
        pinkShader.Bind();
        // TODO: move that somewhere into the engine
        glDrawArrays(GL_TRIANGLES, 0, 3);
        m_secondWindow->OnUpdate();
    }
}