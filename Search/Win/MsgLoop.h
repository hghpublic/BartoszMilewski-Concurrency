#if !defined(MSGLOOP_H)
#define MSGLOOP_H
#include <list>
#include <windows.h>

namespace Win
{
class MsgPrepro
{
    typedef std::list<HWND>::iterator DlgIter;

public:
    MsgPrepro() : _winTop(0) {}
    int Pump();

private:
    HWND _winTop;
};
} // namespace Win

#endif
