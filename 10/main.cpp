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
#include <queue>
#include <array>

static std::array<int, 6> cyclesToWatch = {20, 60, 100, 140, 180, 220};

static std::string pixels;

static void doMiddleCycle(std::vector<int>& valuesX, int curCycle, int X, std::array<int,6>::iterator& nextCycleTarget)
{
    /* Draw pixel */
    static int posCRT = 0;
    pixels.push_back(posCRT >= X - 1 && posCRT <= X + 1 ? '#' : '.');
    posCRT = (posCRT + 1) % 40;

    /* Save X value if cycle is watched */
    if (curCycle != *nextCycleTarget)
        return;
    valuesX.push_back(X);
    nextCycleTarget++;
}

static int run(std::ifstream& infile)
{
    int X = 1;
    int curCycle = 0;
    std::vector<int> valuesX;
    auto itCyclesToWatch = cyclesToWatch.begin();

    /* Parse infile */
    std::string line;
    while (std::getline(infile, line)) {
        std::stringstream ss(line);

        /* Check X value at the middle of noop cycle or middle of the first addv cycle */
        doMiddleCycle(valuesX, ++curCycle, X, itCyclesToWatch);

        /* Parse cmd */
        std::string cmd;
        ss >> cmd;
        if (cmd == "noop")
            continue;

        /* Check X value at the middle of second addv cycle */
        doMiddleCycle(valuesX, ++curCycle, X, itCyclesToWatch);

        /* Add value at the end of the second addv cycle */
        int val;
        ss >> val;
        X += val;
    }

    /* Part1 sum calculation and print */
    int sum = 0;
    itCyclesToWatch = cyclesToWatch.begin();
    for (auto it = valuesX.begin(); it != valuesX.end(); ++it) 
        sum += (*it) * (*(itCyclesToWatch++));
    std::cout << "PART1 - Total sum : " << sum << std::endl;

    /* Part 2 - display string with 40 chars rows */
    std::cout << "PART2 - Pixel draw : " << std::endl;
    for (int c = 0; c < pixels.length(); c++)
        std::cout << (!(c % 40) ? "\n" : "") << pixels[c];
    std::cout << std::endl;

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