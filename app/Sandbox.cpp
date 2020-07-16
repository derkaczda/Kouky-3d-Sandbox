#include "Sandbox.h"
#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <glm/mat3x3.hpp>

#include <iostream>
#include <string>
#include <sstream>

Sandbox::Sandbox()
{
    m_window = new Kouky3d::Window("Sanbox", 800, 600);
    m_secondWindow = new Kouky3d::Window("Second window", 300, 300);
}

Sandbox::~Sandbox()
{
    delete m_window;
    delete m_secondWindow;
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
    /* TODO: it should be possible to share the vertex/fragment objects
     * and just create the glProgram (wrapper) for the two different contexts. 
     * So maybe it should be possible to construct a shader from different vertex/fragment sources
     * could also help reusage of code.
     * */
    m_window->GiveContext();
    Kouky3d::Shader orangeShader(vertexShaderSource, fragmentShaderSourceOrange);

    m_secondWindow->GiveContext();
    Kouky3d::Shader pinkShader(vertexShaderSource, fragmentShaderSourcePink);

    // ----------------
    // end triangle setup
    // ----------------

    glm::vec2 windowpos{100, 100};
    float windowstepsize = 1;
    m_secondWindow->SetPosition(windowpos);
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

        //
        // move window around screen
        //
        windowpos += windowstepsize;
        m_secondWindow->SetPosition(windowpos);
        m_secondWindow->SetSize(windowpos);

        if (windowpos.x > 300)
        {
            windowpos.x = windowpos.y = 300;
            windowstepsize = -windowstepsize;
        }
        else if(windowpos.x < 50)
        {
            windowpos.x = windowpos.y = 50;
            windowstepsize = -windowstepsize;
        }
        std::ostringstream oss;
        oss << "x: " << m_secondWindow->GetPosition().x << " y: " << m_secondWindow->GetPosition().y;
        m_secondWindow->SetTitle(oss.str());
        //std::cout << "Window pos x: " << m_secondWindow->GetPosition().x << " y: " << m_secondWindow->GetPosition().y << std::endl;
       
        Kouky3d::Renderer::ClearColor({0.3f, 0.3f, 0.3f, 1.0f});
        Kouky3d::Renderer::Clear();
        second_vertexArray.Bind();     
        pinkShader.Bind();
        // TODO: move that somewhere into the engine
        glDrawArrays(GL_TRIANGLES, 0, 3);
        m_secondWindow->OnUpdate();
    }
}