#include "Sandbox.h"
#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <glm/mat3x3.hpp>

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
    Kouky3d::setClearColor(0.3f, 0.3f, 0.3f, 1.0f);
    while(true)
    {
        glClearColor(0.5f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        //Kouky3d::clear();
        glm::mat3 test;
        m_window->OnUpdate();
    }
}