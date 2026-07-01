#include <filesystem>
#include <future>
#include <iostream>
#include <string>
#include <thread>
#include <vector>

// filesystem
using namespace std::filesystem;
using namespace std;

vector<string> listDir(path const& dir)
{
    vector<string> files;
    for (const auto& entry :
         directory_iterator(dir, directory_options::skip_permission_denied))
    {
        if (is_regular_file(entry.status()))
        {
            files.push_back(entry.path().filename().string());
        }
    }
    return files;
}

vector<string> listDirs(vector<path> const& paths)
{
    vector<future<vector<string>>> futures;
    for (auto const& pth : paths)
    {
        cout << pth << endl;
        futures.emplace_back(async(listDir, ref(pth)));
    }
    vector<string> allFiles;
    for (auto& fut : futures)
    {
        auto files = fut.get();
        move(files.begin(), files.end(), back_inserter(allFiles));
    }
    return allFiles;
}

int main()
{
    vector<path> paths;
    const auto root{current_path().root_path()};
    for (const auto& entry :
         directory_iterator(root, directory_options::skip_permission_denied))
    {
        if (is_directory(entry.status()))
        {
            paths.push_back(entry.path());
        }
    }

    for (auto name : listDirs(paths))
    {
        cout << name << endl;
    }
}
