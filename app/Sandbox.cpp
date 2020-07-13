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
    while(true)
    {
        m_window->OnUpdate();
    }
}