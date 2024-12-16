#!/usr/bin/env python3

import numpy as np
import matplotlib.pyplot as plt

# chargement des donnees 
data = np.loadtxt("output_file.txt",delimiter='\t', skiprows=1)

time = data[:,0]
deadman = data[:,11]
deadman[deadman==0] = np.nan
q1 = data[:,1]
q2 = data[:,2]
x = data[:,3]
y = data[:,4]
qd1 = data[:,5]*deadman
qd2 = data[:,6]*deadman
xd = data[:,7]*deadman
yd = data[:,8]*deadman
tau1_cmd = data[:,9]
tau2_cmd = data[:,10]

# affichage des donnees
fig, axs = plt.subplots(3, 2)

# q1
axs[0, 0].plot(time, q1, label='q1')
axs[0, 0].plot(time, qd1, label='qd1')
axs[0, 0].legend()
axs[0, 0].grid()
axs[0, 0].set_xlabel("Temps [ms]")
axs[0, 0].set_ylabel("Position articulaire [rad]")

# q2
axs[0, 1].plot(time, q2, label='q2')
axs[0, 1].plot(time, qd2, label='qd2')
axs[0, 1].legend()
axs[0, 1].grid()
axs[0, 1].set_xlabel("Temps [ms]")
axs[0, 1].set_ylabel("Position articulaire [rad]")

# x
axs[1, 0].plot(time, x, label='x')
axs[1, 0].plot(time, xd, label='xd')
axs[1, 0].legend()
axs[1, 0].grid()
axs[1, 0].set_xlabel("Temps [ms]")
axs[1, 0].set_ylabel("Position opérationnelle [m]")

# y
axs[1, 1].plot(time, y, label='y')
axs[1, 1].plot(time, yd, label='yd')
axs[1, 1].legend()
axs[1, 1].grid()
axs[1, 1].set_xlabel("Temps [ms]")
axs[1, 1].set_ylabel("Position opérationnelle [m]")

# tau1
axs[2, 0].plot(time, tau1_cmd, label='tau1_cmd')
axs[2, 0].legend()
axs[2, 0].grid()
axs[2, 0].set_xlabel("Temps [ms]")
axs[2, 0].set_ylabel("Couple de commande [N.m]")

# tau2
axs[2, 1].plot(time, tau2_cmd, label='tau2_cmd')
axs[2, 1].legend()
axs[2, 1].grid()
axs[2, 1].set_xlabel("Temps [ms]")
axs[2, 1].set_ylabel("Couple de commande [N.m]")

fig.tight_layout()
plt.legend()
plt.show()
