#include "crank.hpp"
#include <iostream>
#include <vector>
int main(int argc, char **argv) {
    if (argc != 4) {
        std::cout << "Please pass lattice spacing, duration and sigma of initial gaussian \n";
        return 0;
    }

    if (std::stod(argv[3]) < 3) {
        std::cout << "Sigma too low. Enter a sigma greater than 3. \n";
        return 0;
    }

    int latticeWidth = std::stoi(argv[1]);
    int duration = std::stoi(argv[2]);
    double sigma = std::stod(argv[3]);
    CrankNicholson Cn(latticeWidth, duration, sigma);

    Cn.Step();
    return 0;
}