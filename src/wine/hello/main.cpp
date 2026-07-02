#include <windows.h>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine, int nCmdShow)
{
    MessageBox(NULL, "Hello from libwine!", "Wine Example", MB_OK);
    return 0;
}
