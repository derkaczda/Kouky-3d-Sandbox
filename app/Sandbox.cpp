#include "Sandbox.h"

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
        Kouky3d::clear();
        m_window->OnUpdate();
    }
}