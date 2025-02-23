#ifndef A37D078E_1952_4B69_A4DC_7A9C0DDC3715
#define A37D078E_1952_4B69_A4DC_7A9C0DDC3715

#include <vector>
class CrankNicholson {
public:
    CrankNicholson(const int &latticeWidth, const int &duration, const double &sigma);
    void Step();

private:
    const int latticeWidth_;
    const int duration_;
    const double sigma_;
    const double step_;
    std::vector<double> initialState_;
    std::vector<double> updateMatrix_ = {step_, 1 - 2 * step_, step_};
    void InitialiseState_();
    void DumpState_(const std::vector<double> &newState);
    std::vector<double> Update_(const std::vector<double> &state) const;
};

#endif /* A37D078E_1952_4B69_A4DC_7A9C0DDC3715 */
