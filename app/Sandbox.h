#include <Kouky3d.h>

class Sandbox
{
public:
    Sandbox();
    ~Sandbox();

    void Init();
    void Update();
    void OnEvent(Kouky3d::Event& e);

    bool OnWindowClose(Kouky3d::WindowCloseEvent& e);

private:
    Kouky3d::Window* m_window;
    Kouky3d::Window* m_secondWindow;
};