import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.animation as animation
from pathlib import Path

bin = Path(__file__).parent.parent / "src/data.csv"

df = pd.read_csv(str(bin), header=None)

flipped_df = df.iloc[::-1].reset_index(drop=True)

# Produce a diffusion plot with time reversed portion added to it to simulate
# return of brownian mover
df= pd.concat([df, flipped_df], ignore_index=True)

fig, ax = plt.subplots()

# The x values will just be the indices of the rows
x = np.arange(df.shape[1])

# Create a line that will be updated during the animation
line, = ax.plot([], [], lw=2)

ax.set_xlim(0, df.shape[1]-1)
ax.set_ylim(-0.1*max(df.iloc[0,:]), 1.1*max(df.iloc[0, :]) )

def init():
    line.set_data([], [])
    return line,

def update(frame):
    y = df.iloc[frame, :]
    line.set_data(x,y) 
    return line,

ani = animation.FuncAnimation(fig, update, frames=len(df), init_func=init, blit=True, interval=20)
ani.save('animation.gif', writer='imagemagick', fps=30)