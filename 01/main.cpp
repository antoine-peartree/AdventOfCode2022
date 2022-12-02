#include <fstream>
#include <iostream>
#include <string>
#include <set>
#include <filesystem>

static int run(std::ifstream& infile)
{
    /* Parse infile */
    std::string line;
    std::set<int> calsPerDeer;
    int tmpCal = 0;
    while (std::getline(infile, line))
    {
        if (!std::isdigit(line[0])) {
            calsPerDeer.insert(tmpCal);
            tmpCal = 0;
            continue;
        }
        tmpCal += std::stoi(line);
    }
    calsPerDeer.insert(tmpCal);

    /* Retrieve max values asked within set */
    auto maxCalIt = calsPerDeer.rbegin();
    std::cout << "Max calories carried : " << *(maxCalIt) << std::endl;
    std::cout << "Max calories of the 3 top Elves : " << *(maxCalIt++) + *(maxCalIt++) + *maxCalIt << std::endl;

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