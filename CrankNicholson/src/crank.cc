#include "crank.hpp"
#include <iostream>

CrankNicholson::CrankNicholson(const int &latticeWidth, const int &duration)
    : latticeWidth_(latticeWidth),
      duration_(duration), initialState_(latticeWidth), cCoeffs_(latticeWidth) {
    InitialiseState_();
    InitialiseCCoeffs_();
}

void CrankNicholson::InitialiseState_() {
    // Delta function
    // More complicated states can be written here
    initialState_[latticeWidth_ / 2] = 1;
}

void CrankNicholson::InitialiseCCoeffs_() {
    cCoeffs_[0] = aMatrix_[2] / aMatrix_[1];
    for (int i = 1; i < latticeWidth_ - 1; i++) {
        cCoeffs_[i] = aMatrix_[2] / (aMatrix_[1] - aMatrix_[0] * cCoeffs_[i - 1]);
    }
}

std::vector<double> CrankNicholson::MultiplyB_(const std::vector<double> &state) const {
    std::vector<double> multiplicand(latticeWidth_);

    multiplicand[0] = state[1] * bMatrix_[2] + state[0] * bMatrix_[1];
    multiplicand[latticeWidth_ - 1] = state[latticeWidth_ - 2] * bMatrix_[0] + state[latticeWidth_ - 1] * bMatrix_[1];

    for (int i = 1; i < latticeWidth_ - 1; i++) {
        multiplicand[i] = state[i] * bMatrix_[1] + state[i - 1] * bMatrix_[0] + state[i + 1] * bMatrix_[2];
    }

    return multiplicand;
}

std::vector<double> CrankNicholson::ThomasAlgorithm_(const std::vector<double> &dCoeffs) {
    std::vector<double> newDCoeffs(latticeWidth_);
    std::vector<double> timeSteppedState(latticeWidth_);

    // update d coefficients
    newDCoeffs[0] = dCoeffs[0] / aMatrix_[1];
    for (int i = 1; i < latticeWidth_; i++) {
        newDCoeffs[i] = (dCoeffs[i] - aMatrix_[0] * newDCoeffs[i - 1]) / (aMatrix_[1] - aMatrix_[0] * cCoeffs_[i - 1]);
    }

    // back propagate to find time evolved state
    timeSteppedState[latticeWidth_ - 1] = newDCoeffs[latticeWidth_ - 1];
    for (int i = latticeWidth_ - 2; i >= 0; i--) {
        timeSteppedState[i] = newDCoeffs[i] - cCoeffs_[i] * timeSteppedState[i + 1];
    }

    return timeSteppedState;
}

void CrankNicholson::Step() {
    std::vector<double> newState = initialState_;

    for (int i = 0; i < duration_; i++) {
        newState = ThomasAlgorithm_(MultiplyB_(newState));
    }
}
