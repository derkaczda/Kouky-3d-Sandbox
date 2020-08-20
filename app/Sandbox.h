#include <Kouky3d.h>

class Sandbox
{
public:
    Sandbox();
    ~Sandbox();

    void Init();
    void Shutdown();

    void Update();
    void OnEvent(Kouky3d::Event& e);

private:

    void SetWindowViewport(Kouky3d::Window* window); 
    bool OnWindowClose(Kouky3d::WindowCloseEvent& e);
    bool OnWindowResize(Kouky3d::WindowResizeEvent& e);
    bool OnWindowMove(Kouky3d::WindowMoveEvent& e);


private:
    Kouky3d::Window* m_window;
    Kouky3d::Window* m_secondWindow;

    bool m_running = false;
};