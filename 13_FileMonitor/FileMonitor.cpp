#include <filesystem>
#include <future>
#include <iostream>
#include <mutex>
#include <string>
#include <thread>
#include <vector>

// filesystem
using namespace std::filesystem;
using namespace std;

class FileMonitor
{
public:
    void push_back(string file)
    {
        lock_guard<mutex> lck(_mtx);
        _allFiles.push_back(std::move(file));
    }
    void print()
    {
        lock_guard<mutex> lck(_mtx);
        for (auto& name : _allFiles)
        {
            cout << name << endl;
        }
    }

private:
    mutex _mtx;
    vector<string> _allFiles;
};

void listDir(string path, FileMonitor& fileSink)
{
    for (directory_iterator it(path); it != directory_iterator(); ++it)
    {
        if (is_regular_file(it->status()))
        {
            fileSink.push_back(it->path().filename().string());
        }
    }
}

void listDirs(vector<path> paths, FileMonitor& fileSink)
{
    vector<future<void>> futures;
    for (auto& pth : paths)
    {
        cout << pth << endl;
        futures.emplace_back(async(listDir, pth.string(), ref(fileSink)));
    }
    for (auto& fut : futures)
    {
        fut.wait();
    }
}

int main()
{
    vector<path> paths;
    const auto root{current_path().root_path()};
    for (directory_iterator it(root); it != directory_iterator(); ++it)
    {
        if (is_directory(it->status()))
        {
            paths.push_back(it->path());
        }
    }

    FileMonitor fileSink;
    listDirs(paths, fileSink);
    fileSink.print();
}
