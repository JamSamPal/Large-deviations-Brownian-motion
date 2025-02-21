#ifndef A37D078E_1952_4B69_A4DC_7A9C0DDC3715
#define A37D078E_1952_4B69_A4DC_7A9C0DDC3715

#include <vector>
class CrankNicholson {
public:
    CrankNicholson(const int &latticeWidth, const int &duration);
    void Step();

private:
    const int latticeWidth_;
    const int duration_;
    std::vector<double> initialState_;
    std::vector<double> aMatrix_ = {-1, 3, 1};
    std::vector<double> bMatrix_ = {1, -1, 1};
    std::vector<double> cCoeffs_;
    void InitialiseState_();
    void InitialiseCCoeffs_();
    std::vector<double> MultiplyB_(const std::vector<double> &state) const;
    std::vector<double> ThomasAlgorithm_(const std::vector<double> &dCoeffs);
};

#endif /* A37D078E_1952_4B69_A4DC_7A9C0DDC3715 */
