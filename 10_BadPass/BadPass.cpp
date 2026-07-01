#include <future>
#include <memory>
#include <thread>

void threadFun(std::unique_ptr<int> p) {}

int main()
{
    std::unique_ptr<int> up(new int(10));
    [[maybe_unused]] auto _ = std::async(threadFun, std::move(up));
}