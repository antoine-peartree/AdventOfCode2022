#include <fstream>
#include <iostream>
#include <string>
#include <set>
#include <filesystem>

static char chooseResponse(char opponent, char guide)
{
    char rsp;

    if (guide == 'Y') {
        rsp = opponent;
    } else if (guide == 'X') {
        rsp = opponent == 'A' ? 'C' : opponent - 1;
    } else {
        rsp = opponent == 'C' ? 'A' : opponent + 1;
    }

    return rsp + 'X' - 'A';
}

static int getGamePoints(char opponent, char you)
{
    you -= 'X' - 'A';

    if (opponent == you)
        return 3;

    if (opponent == 'C') {
        return you == 'A' ? 6 : 0;
    } else if (opponent == 'B') {
        return you == 'C' ? 6 : 0;
    } else {
        return you == 'B' ? 6 : 0;
    }
}

static int run(std::ifstream& infile)
{
    int scoreSumPart1 = 0, scoreSumPart2 = 0;

    /* Score calculation for one round */
    auto addScore = [] (std::string line) {return line[2] - 'X' + 1 + getGamePoints(line[0], line[2]);};

    /* Parse infile */
    std::string line;
    while (std::getline(infile, line))
    {
        if (line[0] < 'A' || line[0] > 'C' || line[2] < 'X' || line[2] > 'Z')
            break;

        /* Part 1 */
        scoreSumPart1 += addScore(line);

        /* Part 2 */
        line[2] = chooseResponse(line[0], line[2]);
        scoreSumPart2 += addScore(line);

    }

    std::cout << "Score part1 = " << scoreSumPart1 << std::endl;
    std::cout << "Score part2 = " << scoreSumPart2 << std::endl;

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