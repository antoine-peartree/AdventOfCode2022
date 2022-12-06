#include <fstream>
#include <iostream>
#include <string>
#include <set>
#include <filesystem>
#include <stack>
#include <sstream>
#include <iterator>

static size_t findMarkerPos(std::string& msg, int startMarkerSize)
{
    /* Iterate to find start marker */
    size_t AfterMarkerPos = startMarkerSize;
    for (auto it = msg.begin() + startMarkerSize - 1; it != msg.end(); ++it) {

        /* Store last 4 characters in a set */
        std::set<char> last4Chars;
        for (int i = 0; i < startMarkerSize; i++)
            last4Chars.insert(*(it - i));

        /* Check unique elements with set size */
        if (last4Chars.size() == startMarkerSize)
            return AfterMarkerPos;

        AfterMarkerPos++;
    }
    return -1;
}

static int run(std::ifstream& infile)
{
    /* Get the single line of that puzzle input */
    std::string msg;
    std::getline(infile, msg);

    std::cout << "Start of packet position : " << findMarkerPos(msg, 4) << std::endl;
    std::cout << "Start of message position : " << findMarkerPos(msg, 14) << std::endl;

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