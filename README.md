# Loschmidt Echo
The idea of a Loschmidt Echo is to solve a PDE, here the heat equation, with the boundary condition that the initial
and final states are the same. This creates an interesting scenario where the diffusive spreading out of the heat equation
must be combatted by the need to return to its initial state.

The trick to getting this to work is to exploit the neccesary time reversal symmetry: we propagate the solution forward a given
number of time steps and then simply reverse the propagation. Taking, for example, an initially gaussian wavefunction centred at
x = 0, the duration we propagate the solution forward for, t_d, gives us a characteristic 'excursion distance' from this initial point,
x_d = \sqrt{t_d}. This work can then be applied to simulating any free Brownian motion where one wishes the Brownian mover to 
fluctuate to a distant value x_d before returning to its initial value again.
