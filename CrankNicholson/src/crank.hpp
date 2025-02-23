#ifndef A37D078E_1952_4B69_A4DC_7A9C0DDC3715
#define A37D078E_1952_4B69_A4DC_7A9C0DDC3715

#include <vector>
// Crank Nicholson algorithm with the diffusion equation:
// state[t+1, i] = state[t,i](1 +dt*potential[i]) + (D/2)*(dt/(dx^2))* (state[t,i-1] - 2 state[t,i] + state[t,i+1])

// We set step = (D/2)*(dt/(dx^2)) = 0.1, with D the diffusion coefficient.
// The potential is a delta pulse = alpha if i = latticeWidth/2.
// We set dt*alpha = 0.1 and dx = 1.
// Putting it all together implies alpha/D = 0.5.
class CrankNicholson {
public:
    CrankNicholson(const int &latticeWidth, const int &duration, const double &alpha);
    void Step();

private:
    const int latticeWidth_;
    const int duration_;
    const double step_;
    const double alpha_;
    std::vector<double> initialState_;
    std::vector<double> updateMatrix_ = {step_, 1 - 2 * step_, step_}; // Rhs of Crank Nicholson algorithm
    void InitialiseState_();
    void DumpState_(const std::vector<double> &newState);
    std::vector<double> Update_(const std::vector<double> &state) const;
};

#endif /* A37D078E_1952_4B69_A4DC_7A9C0DDC3715 */
