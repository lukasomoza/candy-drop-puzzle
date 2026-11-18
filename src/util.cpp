#include "util.h"
#include <filesystem>
#include <iostream>

/// Walks up from the current working directory until it finds the project's
/// "data" folder (the one containing img/candy). This lets the game run from
/// the repo root, from build/, or from visual_studio/windows/Program/.
std::string getDataDirPath()
{
    namespace fs = std::filesystem;

    static std::string cached;
    if (!cached.empty())
        return cached;

    fs::path dir = fs::current_path();
    std::string prefix = "./";
    for (int depth = 0; depth < 6; ++depth)
    {
        if (fs::exists(dir / "data" / "img" / "candy"))
        {
            cached = prefix + "data/";
            return cached;
        }
        if (!dir.has_parent_path() || dir.parent_path() == dir)
            break;
        dir = dir.parent_path();
        prefix = (depth == 0) ? "../" : prefix + "../";
    }

    std::cerr << "Cannot find the data folder from '" << fs::current_path().string()
              << "'. Please run the game with run.sh or run.bat." << std::endl;
    return "data/";
}
