#include "Sandbox.h"
#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <glm/mat3x3.hpp>

#include <iostream>

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

    // TODO: move shader to own class
    const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";

    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);

    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    int  success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

    if(!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    const char* fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\0";

    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();

    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glUseProgram(shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);  

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0); 
    


    glUseProgram(shaderProgram);

    // ----------------
    // end triangle setup
    // ----------------


    vertexArray.Bind();
    Kouky3d::setClearColor(0.3f, 0.3f, 0.3f, 1.0f);
    while(true)
    {
        Kouky3d::clear();
        glDrawArrays(GL_TRIANGLES, 0, 3);
        m_window->OnUpdate();
    }
}