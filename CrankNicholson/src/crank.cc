#include "crank.hpp"
#include <cmath>
#include <filesystem>
#include <fstream>
#include <iostream>

CrankNicholson::CrankNicholson(const int &latticeWidth, const int &duration, const double &sigma)
    : latticeWidth_(latticeWidth),
      duration_(duration), initialState_(latticeWidth), sigma_(sigma), step_(0.5) {
    InitialiseState_();

    // Delete old data file
    std::string filename = "data.csv";
    try {
        if (std::filesystem::remove(filename))
            std::cout << "file " << filename << " deleted.\n";
    } catch (const std::filesystem::filesystem_error &err) {
        std::cout << "filesystem error: " << err.what() << '\n';
    }
}

void CrankNicholson::InitialiseState_() {
    // Gaussian initial state
    for (int x = 1; x < latticeWidth_ - 1; x++) {
        initialState_[x] = exp(-pow(x - latticeWidth_ / 2, 2) / (2 * pow(sigma_, 2)));
    }
    // Boundary conditions
    initialState_[0] = 0;
    initialState_[latticeWidth_ - 1] = 0;
}

std::vector<double> CrankNicholson::Update_(const std::vector<double> &state) const {
    // Produces the time evolved state
    std::vector<double> newState(latticeWidth_);

    newState[1] = state[1] * updateMatrix_[2] + state[0] * updateMatrix_[1];
    newState[latticeWidth_ - 2] = state[latticeWidth_ - 2] * updateMatrix_[0] + state[latticeWidth_ - 1] * updateMatrix_[1];

    for (int i = 2; i < latticeWidth_ - 2; i++) {
        newState[i] = state[i] * updateMatrix_[1] + state[i - 1] * updateMatrix_[0] + state[i + 1] * updateMatrix_[2];
    }

    return newState;
}

void CrankNicholson::DumpState_(const std::vector<double> &newState) {
    std::ofstream myfile;
    myfile.open("data.csv", std::ios::out | std::ios::app);

    for (int i = 0; i < newState.size(); i++) {
        myfile << newState.at(i) << ",";
    }
    myfile << "\n";

    myfile.close();
}

void CrankNicholson::Step() {
    // Iterate through duration_ number of time steps
    std::vector<double> newState = initialState_;
    DumpState_(newState);

    for (int i = 0; i < duration_; i++) {
        newState = Update_(newState);

        // Save for python plotting
        DumpState_(newState);
    }
}
