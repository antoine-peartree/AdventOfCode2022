#include <fstream>
#include <iostream>
#include <string>
#include <set>
#include <filesystem>
#include <stack>
#include <sstream>
#include <istream>
#include <map>
#include <vector>
#include <memory>

static int run(std::ifstream& infile)
{
    std::string pwd;
    std::map<std::string, size_t> files;

    /* Parse infile */
    std::string line;
    while (std::getline(infile, line))
    {
        /* Manage current absolute path */
        if (line.substr(0, 4) == "$ cd") {
            if (line.substr(5, 2) == "..") {
                pwd = pwd.substr(0, pwd.find_last_of("/"));
            } else if (line.substr(5, 1) == "/") {
                pwd = "/";
            } else {
                if (pwd != "/")
                    pwd += "/";
                pwd += line.substr(5);
            }
        /* Add new files and related size */
        } else if (line[0] != '$' && line.substr(0, 3) != "dir") {
            std::stringstream ss(line);
            size_t sz = 0;
            std::string name;
            ss >> sz >> name;
            if (pwd != "/")
                name = "/" + name;
            files.insert(std::make_pair(pwd + name, sz));
        }
    }

    /* Calculate directories size */
    std::map<std::string, size_t> dirs;
    for (auto file = files.begin(); file != files.end(); ++file) {
        std::string parentDirs = file->first.substr(0, file->first.find_last_of("/"));
        while (parentDirs != "") {
            size_t curSz = 0;
            if (dirs.find(parentDirs) != dirs.end())
                curSz = dirs.find(parentDirs)->second;
            dirs[parentDirs] = curSz + file->second;
            parentDirs = parentDirs.substr(0, parentDirs.find_last_of("/"));
        }
    }

    /* Iterate along registered directories and root files */
    size_t outermostDir = 0;
    std::set<size_t> dirSzOrdered;
    size_t sum = 0;
    for (auto it = dirs.begin(); it != dirs.end(); ++it) {

        /* Part1 - Sum all directories < 100000 */
        if ((it->first.find(".") == std::string::npos) && it->second <= 100000)
            sum += it->second;
        
        /* Part2 - Order dir sizes to choose file size to remove */
        dirSzOrdered.insert(it->second);

        /* Part2 - OutemostDir calculation for free space needed */
        if (!it->first.find_last_of("/"))
            outermostDir += it->second;
    }

    std::cout << "PART1 - Sum of dirs <100000 : " << sum << std::endl;

    const size_t minSpaceToFree = 30000000 - (70000000 - outermostDir);
    std::cout << "PART2 - Size of the dir to remove : " << *dirSzOrdered.upper_bound(minSpaceToFree) << std::endl;

    return 0;
}

int main(int argc, char** argv)
{
    int ret = -1;

    std::cout << std::endl << "== Starting " << argv[0] + 2 << " ==" << std::endl;

    /* Open infile */
    std::ifstream infile("in.txt");
    if (!infile.is_open()) {
        std::cerr << "Cannot open input file" << std::endl;
        goto out_main;
    }

    /* Run exercise */
    ret = run(infile);

out_main:
    infile.close();
    return ret;
}