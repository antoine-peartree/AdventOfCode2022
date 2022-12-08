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

static void checkLine(bool isHorizontal, std::string line, std::set<std::pair<int,int>>& visibleTrees, const int constPos)
{
    int tallestTreeSz = -1;
    int varPos = 0;

    auto storeVisibleTree = [](int sz, int& tallest, std::set<std::pair<int,int>>& visibleTrees, std::pair<int,int> pos) {
        if (sz > tallest) {
            tallest = sz;
            visibleTrees.insert(pos);
        }
    };

    for (auto tree = line.begin(); tree != line.end(); ++tree) {
        storeVisibleTree(*tree - '0', tallestTreeSz, visibleTrees,
            isHorizontal ? std::make_pair(varPos++, constPos) : std::make_pair(constPos, varPos--));
    }

    varPos = isHorizontal ? varPos - 1 : varPos + 1;
    tallestTreeSz = -1;
    for (auto tree = line.rbegin(); tree != line.rend(); ++tree) {
        storeVisibleTree(*tree - '0', tallestTreeSz, visibleTrees,
            isHorizontal ? std::make_pair(varPos--, constPos) : std::make_pair(constPos, varPos++));
    }
}

static int run(std::ifstream& infile)
{
    /* Parse infile */
    std::vector<std::string> trees;
    std::string line;
    while (std::getline(infile, line)) trees.push_back(line);

    std::set<std::pair<int,int>> visibleTrees;

    /* Check horizontal lines */
    bool isHorizontal = true;
    int posY = 0;
    for (auto horizontalLine = trees.begin(); horizontalLine != trees.end(); ++horizontalLine)
        checkLine(isHorizontal, *horizontalLine, visibleTrees, posY--);

    /* Check vertical lines */
    isHorizontal = false;
    for (int posX = 0; posX < trees.begin()->length() - 1; posX++) {
        std::string verticalLine;
        for (auto horizontalLine = trees.begin(); horizontalLine != trees.end(); ++horizontalLine)
            verticalLine.push_back(horizontalLine->at(posX));
        checkLine(isHorizontal, verticalLine, visibleTrees, posX);
    }

    std::cout << "PART1 - Total visible trees : " << visibleTrees.size() << std::endl;

    struct coords{int x;int y;};

    /* Lambda for getting visible trees in one direction */
    auto getViz = [trees](coords curTree, coords offset) {
        int viz = 0;
        for (int i = 1; i < (offset.x ? trees.size() : trees.begin()->length()); i++) {
            coords newTree = {curTree.x + offset.x * i, curTree.y + offset.y * i};
            if (newTree.x < 0 || newTree.y < 0 || newTree.x >= trees.size() || newTree.y >= trees.begin()->length())
                break;

            viz++;
            if (trees[newTree.x][newTree.y] >= trees[curTree.x][curTree.y])
                break;
        }
        return viz;
    };

    coords curTree;
    std::set<int> visibilities;
    for (curTree.x = 0; curTree.x < trees.size(); curTree.x++)
        for (curTree.y = 0; curTree.y < trees.begin()->length(); curTree.y++)
            visibilities.insert(getViz(curTree, {0, -1}) *
                getViz(curTree, {0, 1}) *
                getViz(curTree, {-1, 0}) *
                getViz(curTree, {1, 0}));

    std::cout << "PART2 - Max visibility : " << *visibilities.rbegin() << std::endl;

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