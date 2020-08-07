#include "Sandbox.h"

int main (int argc, char *argv[]) 
{     
    Sandbox sandbox;
    sandbox.Init();
    sandbox.Update();
    sandbox.Shutdown();
    return 0;
}