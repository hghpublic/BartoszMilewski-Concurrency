#include <condition_variable>
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
        _cond.notify_one();
    }
    string pop_back()
    {
        unique_lock<mutex> lck(_mtx);
        /*
        while (_allFiles.empty())
            _cond.wait(lck);
        */
        _cond.wait(lck, [this] { return !_allFiles.empty(); });
        string name = std::move(_allFiles.back());
        _allFiles.pop_back();
        return name;
    }

private:
    mutable mutex _mtx;
    mutable condition_variable _cond;
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
    for (;;)
    {
        string name = fileSink.pop_back();
        cout << name << endl;
    }
    for (auto& fut : futures)
    {
        fut.wait();
    }
}

int main()
{
    vector<path> paths;
    for (directory_iterator it("c:\\"); it != directory_iterator(); ++it)
    {
        if (is_directory(it->status()))
        {
            paths.push_back(it->path());
        }
    }

    FileMonitor fileSink;
    listDirs(paths, fileSink);
}
