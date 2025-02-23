#include "crank.hpp"
#include <cmath>
#include <filesystem>
#include <fstream>
#include <iostream>

CrankNicholson::CrankNicholson(const int &latticeWidth, const int &duration, const double &alpha)
    : latticeWidth_(latticeWidth),
      duration_(duration), initialState_(latticeWidth), alpha_(alpha), step_(0.1) {
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
    // Simple delta function
    initialState_[latticeWidth_ / 2] = 1;
}

std::vector<double> CrankNicholson::Update_(const std::vector<double> &state) const {
    // Produces the time evolved state
    std::vector<double> newState(latticeWidth_);

    newState[1] = state[1] * updateMatrix_[2] + state[0] * updateMatrix_[1];
    newState[latticeWidth_ - 2] = state[latticeWidth_ - 2] * updateMatrix_[0] + state[latticeWidth_ - 1] * updateMatrix_[1];

    double total = 0;
    for (int i = 2; i < latticeWidth_ - 2; i++) {
        if (i == latticeWidth_ / 2) {
            // Delta function potential
            newState[i] = state[i] * (updateMatrix_[1] + 0.1) + state[i - 1] * updateMatrix_[0] + state[i + 1] * updateMatrix_[2];
        } else {
            newState[i] = state[i] * (updateMatrix_[1]) + state[i - 1] * updateMatrix_[0] + state[i + 1] * updateMatrix_[2];
        }
        total += newState[i];
    }

    // Normalise
    for (int i = 2; i < latticeWidth_ - 2; i++) {
        newState[i] /= total;
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
