import numpy as np
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation
import sys

max = int(sys.argv[1])

s,x,y = np.loadtxt(f'particles/0.dat', usecols=(0,1,2), unpack=True)
for i in range(1,max):
    s1,x1,y1 = np.loadtxt(f'particles/{i}.dat', usecols=(0,1,2), unpack=True)
    s = np.column_stack((s,s1))
    x = np.column_stack((x,x1))
    y = np.column_stack((y,y1))

lim = 100
fig, ax = plt.subplots(figsize=(8,8))
ax.set(xlim=(-lim, lim), ylim=(-lim, lim))
scat = ax.scatter(x[0], y[0], color='black')
circ = plt.Circle((0,0),radius=5,fc='yellow')
plt.gca().add_patch(circ)


def animate(i):
    x_i = x[i]
    y_i = y[i]
    scat.set_offsets(np.c_[x_i, y_i])
    scat.set_sizes(s[i])
    #print(x_i,y_i)

anim = FuncAnimation(fig, animate, interval=1, frames=len(y)-1)

plt.show()
