import math

import matplotlib.pyplot as plt
import numpy as np

from utils import to_short

Vdd = 3.3e3  # Power voltage, mV

base_r = (680, 470e3)
testing_r = (
    (
        (1, 100e3),
        (1, 700),
        (40e3, 100e3),
    ),
    (
        (1e3, 100e6),
        (1, 1e6),
        (40e6, 100e6),
    ),
)
fig, axs = plt.subplots(2, len(testing_r[0]), figsize=(15, 9), layout="constrained")

for i, R0 in enumerate(base_r):
    for j, resistors in enumerate(testing_r[i]):
        if j == 0:
            R = np.logspace(math.log10(resistors[0]), math.log10(resistors[1]), 300)
            volts = Vdd * R0 / (R0 + R)  # Voltage drop, mV
            axs[i, j].semilogx(R, volts, label=r"$V(R) = \frac{V_{dd}*R}{R0+R}$")
        else:
            R = np.linspace(resistors[0], resistors[1], 1000)
            volts = Vdd * R0 / (R0 + R)  # Voltage drop, mV
            axs[i, j].plot(R, volts, label=r"$V(R) = \frac{V_{dd}*R}{R0+R}$")
        axs[i, j].set_title(rf"Voltage drop at $R_0 = {to_short(R0)} \Omega$")

        if i == 0 and j == 0:
            axs[i, j].legend(fontsize=14)

        axs[i, j].set(xlim=(R.min(), R.max()), xlabel=r"$R, \Omega$")
        axs[i, j].set(ylim=(volts.min(), volts.max() * 1.05), ylabel=r"$V(R), mV$")
        axs[i, j].grid(True)

plt.savefig("res.svg")
plt.show()
