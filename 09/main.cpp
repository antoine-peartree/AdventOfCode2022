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

using Coords = std::pair<int,int>;
std::map<char, Coords> moveOffset = {
    {'U', {0, 1}},
    {'D', {0, -1}},
    {'L', {-1, 0}},
    {'R', {1, 0}}
};

static bool isTailStickingToHead(Coords posHead, Coords posTail)
{
    auto isSticking = [](int ax1, int ax2) {return ax1 == ax2 || ax1 == ax2 + 1 || ax1 == ax2 - 1;};
    return isSticking(posHead.first, posTail.first) && isSticking(posHead.second, posTail.second);
}

static int run(std::ifstream& infile)
{
    Coords posHead = {0, 0}, posTail = {0, 0};
    std::set<Coords> posTailRecords;
    posTailRecords.insert(posTail);

    /* Parse infile */
    std::string line;
    while (std::getline(infile, line)) {

        /* Parse new move */
        char dir;
        int dist;
        std::stringstream ss(line);
        ss >> dir >> dist;

        for (int i = 0; i < dist; i++) {
            /* Apply new move to head */
            Coords lastPosHead = posHead;
            posHead.first += moveOffset[dir].first;
            posHead.second += moveOffset[dir].second;

            /* Apply new move to tail */
            if (!isTailStickingToHead(posHead, posTail))
                posTail = lastPosHead;

            /* Store tail position */
            posTailRecords.insert(posTail);
        }
    }

    std::cout << "PART1 - Nb tail positions : " << posTailRecords.size() << std::endl;

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