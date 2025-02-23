import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.animation as animation

from pathlib import Path
from scipy.optimize import curve_fit

bin = Path(__file__).parent.parent / "src/data.csv"

df = pd.read_csv(str(bin), header=None)
fig, ax = plt.subplots()

# The x values will just be the indices of the rows
x = np.arange(df.shape[1]-1)

# Create a line that will be updated during the animation
line, = ax.plot([], [], lw=2)

def theory_prediction(x):
    # (alpha/(2D))*np.exp((alpha/D)*|x-a|) with "a" the long term average
    # we know alpha/D = 0.5 in our units. a is the centre which we set at
    # half the lattice spacing.

    centre = len(x)//2
    return 0.25*np.exp(-0.5 * np.abs(x-centre))

ax.plot(x, theory_prediction(x))

def init():
    line.set_data([], [])
    return line,

def update(frame):
    y = df.iloc[frame, :-1]
    line.set_data(x,y) 
    return line,

# Animation shows settling down to theory prediction
ani = animation.FuncAnimation(fig, update, frames=len(df), init_func=init, blit=True, interval=20)
ani.save('animation.gif', writer='imagemagick', fps=30)

# Compare error
area_simulation = np.trapezoid(df.iloc[-1,:-1])
area_theory = np.trapezoid(theory_prediction(x))
area_error = (np.abs(area_theory-area_simulation)/area_simulation)*100

print(f"Error between theory and simulation = {area_error}%")