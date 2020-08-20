#include "Sandbox.h"
#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <glm/mat3x3.hpp>
#include <glm/gtx/transform.hpp>

#include <iostream>
#include <string>
#include <sstream>

#define BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)

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
    m_window->SetCallback(BIND_EVENT_FN(Sandbox::OnEvent));
    m_window->Show();

    // TODO: move that somewhere into the engine
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

    m_secondWindow->Init(false);
    m_secondWindow->SetCallback(BIND_EVENT_FN(Sandbox::OnEvent));
    m_secondWindow->Show();

    m_running = true;
}

void Sandbox::Shutdown()
{
    m_window->Shutdown();
    m_secondWindow->Shutdown();

    delete m_window;
    delete m_secondWindow;
}

void Sandbox::OnEvent(Kouky3d::Event& e)
{
    Kouky3d::EventDispatcher dispatcher(e);
    dispatcher.Dispatch<Kouky3d::WindowCloseEvent>(BIND_EVENT_FN(Sandbox::OnWindowClose));
    dispatcher.Dispatch<Kouky3d::WindowResizeEvent>(BIND_EVENT_FN(Sandbox::OnWindowResize));
    dispatcher.Dispatch<Kouky3d::WindowMoveEvent>(BIND_EVENT_FN(Sandbox::OnWindowMove));
}

bool Sandbox::OnWindowClose(Kouky3d::WindowCloseEvent& e)
{
    m_running = false;
    return true;
}

void Sandbox::SetWindowViewport(Kouky3d::Window* window)
{
    window->GiveContext();
    Kouky3d::Renderer::Viewport(0, 0, window->GetSize().x, window->GetSize().y);
}

bool Sandbox::OnWindowResize(Kouky3d::WindowResizeEvent& e)
{
    if (e.GetWindowHandle() == m_window->GetHandle())
        SetWindowViewport(m_window);
    else if (e.GetWindowHandle() == m_secondWindow->GetHandle())
        SetWindowViewport(m_secondWindow);

    return false;
}

bool Sandbox::OnWindowMove(Kouky3d::WindowMoveEvent& e)
{
    std::ostringstream oss_window_one;
    oss_window_one << "x: " << m_window->GetPosition().x << " y: " << m_window->GetPosition().y;
    m_window->SetTitle(oss_window_one.str());

    std::ostringstream oss_window_two;
    oss_window_two << "x: " << m_secondWindow->GetPosition().x << " y: " << m_secondWindow->GetPosition().y;
    m_secondWindow->SetTitle(oss_window_two.str());
    return false;
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
    "uniform mat4 u_Transform;"
    "void main()\n"
    "{\n"
    "   gl_Position = u_Transform * vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
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
    float angle = 0;
    while(m_running)
    {
        m_window->GiveContext();
        Kouky3d::Renderer::ClearColor({0.3f, 0.3f, 0.3f, 1.0f});
        Kouky3d::Renderer::Clear();
        vertexArray.Bind();
        orangeShader.Bind();

        angle += 0.1f;
        glm::mat4 transform = glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0, 0.0f, 1.0f));
        orangeShader.Uniform("u_Transform", transform);
        // TODO: move that somewhere into the engine
        glDrawArrays(GL_TRIANGLES, 0, 3);

        
        m_window->OnUpdate();

        m_secondWindow->GiveContext();
       
        Kouky3d::Renderer::ClearColor({0.3f, 0.3f, 0.3f, 1.0f});
        Kouky3d::Renderer::Clear();
        second_vertexArray.Bind();     
        pinkShader.Bind();
        pinkShader.Uniform("u_Transform", glm::mat4(1.0f));
        // TODO: move that somewhere into the engine
        glDrawArrays(GL_TRIANGLES, 0, 3);
        m_secondWindow->OnUpdate();
    }
}