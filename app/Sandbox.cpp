#include "Sandbox.h"
#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <glm/mat3x3.hpp>

#include <iostream>
#include <string>

Sandbox::Sandbox()
{
    m_window = new Kouky3d::Window("Sanbox", 800, 600);
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

    // TODO: move shader source to own file
    const std::string vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";

    const std::string fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\0";

    Kouky3d::Shader shader(vertexShaderSource, fragmentShaderSource);

    // ----------------
    // end triangle setup
    // ----------------

    shader.Bind();
    vertexArray.Bind();
    Kouky3d::Renderer::ClearColor({0.3f, 0.3f, 0.3f, 1.0f});
    while(true)
    {
        Kouky3d::Renderer::Clear();
        glDrawArrays(GL_TRIANGLES, 0, 3);
        m_window->OnUpdate();
    }
}