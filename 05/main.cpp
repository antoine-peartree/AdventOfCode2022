#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <filesystem>
#include <stack>
#include <sstream>

#define NB_STACKS (9U)

static void reverseStack(std::stack<char>& stack)
{
    std::stack<char> tmpStack;
    while (!stack.empty()) {
        tmpStack.push(stack.top());
        stack.pop();
    }
    stack = tmpStack;
}

static void displayAllTopStacks(std::vector<std::stack<char>> &stacks)
{
    for (int stackNb = 0; stackNb < stacks.size(); stackNb++)
        std::cout << stacks[stackNb].top();
    std::cout << std::endl;
}

static int run(std::ifstream& infile)
{
    std::vector<std::stack<char>> stacks(NB_STACKS), stacksPart2(NB_STACKS);
    std::string line;

    /* Fill stacks with input letters */
    while (std::getline(infile, line))
    {
        if (line.empty())
            break;

        for (int i = 0; i < stacks.size(); i++)
            if (std::isupper(line[1 + i * 4]))
                stacks[i].push(line[1 + i * 4]);
    }

    /* Reverse stacks to fit input style */
    for (int i = 0; i < stacks.size(); i++)
        reverseStack(stacks[i]);

    /* Copy input stacks to be used for Part2 */
    for (int i = 0; i < stacks.size(); i++)
        stacksPart2[i] = stacks[i];

    while (std::getline(infile, line))
    {
        /* Parse move */
        std::stringstream ss(line);
        std::string move, from, to;
        int nb, colFrom, colTo;
        ss >> move >> nb >> from >> colFrom >> to >> colTo;

        /* Execute Part1 move */
        for (int i = 0; i < nb; i++) {
            stacks[colTo - 1].push(stacks[colFrom - 1].top());
            stacks[colFrom - 1].pop();
        }

        /* Execute Part2 move */
        std::stack<char> tmpStack;
        for (int i = 0; i < nb; i++) {
            tmpStack.push(stacksPart2[colFrom - 1].top());
            stacksPart2[colFrom - 1].pop();
        }
        for (int i = 0; i < nb; i++) {
            stacksPart2[colTo - 1].push(tmpStack.top());
            tmpStack.pop();
        }        
    }

    /* Display top of each stacks in a single line */
    std::cout << "Part1 stacks : ";
    displayAllTopStacks(stacks);
    std::cout << "Part2 stacks : ";
    displayAllTopStacks(stacksPart2);

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