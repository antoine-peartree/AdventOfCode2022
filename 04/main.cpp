#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <filesystem>
#include <sstream>

static int run(std::ifstream& infile)
{
    int cntIncludes = 0, cntOverlaps = 0;

    /* Parse infile */
    std::string line;
    while (std::getline(infile, line))
    {
        std::replace(line.begin(), line.end(), ',', ' ');
        std::replace(line.begin(), line.end(), '-', ' ');

        std::stringstream ss(line);
        std::pair<int, int> range1, range2;
        ss >> range1.first >> range1.second >> range2.first >> range2.second;

        /* Part 1 */
        if ((range1.first <= range2.first && range1.second >= range2.second) ||
                (range2.first <= range1.first && range2.second >= range1.second))
            cntIncludes++;

        /* Part 2 */
        if ((range1.first <= range2.first && range2.first <= range1.second) ||
                (range1.first <= range2.second && range2.second <= range1.second) ||
                (range2.first <= range1.first && range1.first <= range2.second) ||
                (range2.first <= range1.second && range1.second <= range2.second))
            cntOverlaps++;
    }

    std::cout << "PART1 - Nbr includes : " << cntIncludes << std::endl;
    std::cout << "PART2 - Nbr overlaps : " << cntOverlaps << std::endl;

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