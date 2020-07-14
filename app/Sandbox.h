#include <Kouky3d.h>

class Sandbox
{
public:
    Sandbox();
    ~Sandbox();

    void Init();
    void Update();

private:
    Kouky3d::Window* m_window;
    Kouky3d::Window* m_secondWindow;
};