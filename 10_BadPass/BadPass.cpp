#include <future>
#include <memory>
#include <thread>

void threadFun(std::unique_ptr<int> p) {}

void main()
{
    std::unique_ptr<int> up(new int(10));
    std::async(threadFun, std::move(up));
}