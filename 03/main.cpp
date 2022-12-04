#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <filesystem>

static int getCharValue(char c)
{
    return std::islower(c) ? c - 'a' + 1 : c - 'A' + 27;
}

static char getCommonItem(std::string half1, std::string half2)
{
    for (auto it = half1.begin(); it != half1.end(); ++it)
        if (half2.find(*it) != std::string::npos)
            return *it;
    return '@';
}

static int run(std::ifstream& infile)
{
    int sumPrioPart1 = 0, sumPrioPart2 = 0;
    int lineCnt = 0;

    /* Parse infile */
    std::string line;
    std::vector<std::string> group;
    while (std::getline(infile, line))
    {
        /* Part 1 */
        size_t halfSz = line.length() / 2;
        char commonItem = getCommonItem(line.substr(0, halfSz), line.substr(halfSz, halfSz));
        sumPrioPart1 += getCharValue(commonItem);

        /* Part 2 */
        group.push_back(line);
        if (!(++lineCnt % 3)) {
            std::vector<char> commonCharsForTwoDeers;

            /* Store common chars between the 2 first deers */
            for (auto c = group[0].begin(); c != group[0].end(); ++c)
                if (group[1].find(*c) != std::string::npos)
                    commonCharsForTwoDeers.push_back(*c);
            
            /* Compare the stored chars to the third deer of the group and add priority to sum */
            for (auto c = commonCharsForTwoDeers.begin(); c != commonCharsForTwoDeers.end(); ++c)
                if (group[2].find(*c) != std::string::npos) {
                    sumPrioPart2 += getCharValue(*c);
                    break;
                }
            group.clear();
        }
    }

    std::cout << sumPrioPart1 << std::endl;
    std::cout << sumPrioPart2 << std::endl;

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