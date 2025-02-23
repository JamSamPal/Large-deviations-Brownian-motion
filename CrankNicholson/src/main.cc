#include "crank.hpp"
#include <iostream>
#include <vector>
int main(int argc, char **argv) {
    if (argc != 3) {
        std::cout << "Please pass lattice spacing, duration and strength of potential \n";
        return 0;
    }

    int latticeWidth = std::stoi(argv[1]);
    int duration = std::stoi(argv[2]);

    CrankNicholson Cn(latticeWidth, duration);

    Cn.Step();
    return 0;
}