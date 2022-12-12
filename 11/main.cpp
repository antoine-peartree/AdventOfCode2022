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
#include <iterator>
#include <algorithm>
#include <cmath>

struct Op {
    std::string op1, op2, opType;
};

struct Monkey {
    std::vector<uint64_t> items;
    Op op;
    uint64_t div;
    int nextMonkeyIfTrue, nextMonkeyIfFalse;
    uint64_t nbInspections;
};

static void doRound(std::vector<Monkey>& monkeys)
{
    /* For each monkey */
    for (auto monkey = monkeys.begin(); monkey != monkeys.end(); ++monkey) {

        /* For each item */
        for (auto item = monkey->items.begin(); item != monkey->items.end(); ++item) {

            /* Calculate new worry level */
            uint64_t op1 = !monkey->op.op1.compare("old") ? *item : std::stoi(monkey->op.op1);
            uint64_t op2 = !monkey->op.op2.compare("old") ? *item : std::stoi(monkey->op.op2);
            uint64_t newWorryLevel = !monkey->op.opType.compare("*") ? op1 * op2 : op1 + op2;

            /* Usual worry level division */
            newWorryLevel = floor(newWorryLevel / 3.0);

            /* Division test */
            int newMonkey = newWorryLevel % monkey->div ? monkey->nextMonkeyIfFalse : monkey->nextMonkeyIfTrue;

            /* Throw to new monkey */
            monkeys[newMonkey].items.push_back(newWorryLevel);

            /* Increase inspection count */
            monkey->nbInspections++;
        }

        /* Clear items as they have all been throwed to other monkeys */
        monkey->items.clear();
    }
}

static void parseInfile(std::ifstream& infile, std::vector<Monkey>& monkeys)
{
    std::string line;
    while (std::getline(infile, line)) {
        if (line.find("Monkey ") == std::string::npos)
            continue;

        Monkey monkey;

        /* Read items */
        std::getline(infile, line);
        line = line.substr(line.find(":") + 2);
        std::replace(line.begin(), line.end(), ',', ' ');
        std::stringstream ssItems(line);
        std::vector<uint64_t> items(std::istream_iterator<uint64_t>(ssItems), {});
        monkey.items = items;

        /* Read operation */
        std::getline(infile, line);
        std::stringstream ssOp(line.substr(line.find("=") + 2));
        ssOp >> monkey.op.op1 >> monkey.op.opType >> monkey.op.op2;

        /* Read div and nextMonkeys*/
        auto readLastIntFromNextStr = [](std::string line) {return std::stoi(line.substr(line.find("y ") + 2));};
        std::getline(infile, line);
        monkey.div = readLastIntFromNextStr(line);
        std::getline(infile, line);
        monkey.nextMonkeyIfTrue = readLastIntFromNextStr(line);
        std::getline(infile, line);
        monkey.nextMonkeyIfFalse = readLastIntFromNextStr(line);

        /* Save new monkey infos */
        monkey.nbInspections = 0;
        monkeys.push_back(monkey);
    }
}

static int run(std::ifstream& infile)
{
    std::vector<Monkey> monkeys;

    /* Parse infile */
    parseInfile(infile, monkeys);

    /* Do a certain amount of rounds */
    for (int nbRound = 0; nbRound < 20; nbRound++)
        doRound(monkeys);

    /* Retrieve monkey business */
    std::set<uint64_t> nbInspections;
    for (auto monkey = monkeys.begin(); monkey != monkeys.end(); ++monkey)
        nbInspections.insert(monkey->nbInspections);
    std::cout << "PART1 - Monkey business : " << (*nbInspections.rbegin()) * (*(++nbInspections.rbegin())) << std::endl;

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