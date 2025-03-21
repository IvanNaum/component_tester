import math

import matplotlib.pyplot as plt
import numpy as np

from utils import to_short

fig, axs = plt.subplots(2, 1, figsize=(9, 7), layout="constrained")

# Circuit parameters
R = 680  # Resistance, Ohms
Vdd = 3.3  # Power voltage, V
t_charge = 0.01  # Charging pulse duration, sec
C = 0.01  # Capacitance, F (example value)
max_impulses = 499  # Maximum number of impulses
threshold2 = 0.075  # Intermediate threshold
threshold1 = 0.3  # Finite threshold
check_impulses = 127  # Check after impulses

# Initialization
V = 0.0  # Initial voltage
t = 0.0  # Initial time
stop = False  # Stop flag

# Data storage
time_points = [t]
voltage_points = [V]

# Simulate charging impulses
for impulse in range(1, max_impulses + 1):
    # Charge phase
    tau = R * C
    t_charge_end = t + t_charge
    charge_time = np.linspace(t, t_charge_end, 100)
    charge_voltage = V + (Vdd - V) * (1 - np.exp(-(charge_time - t) / tau))
    time_points.extend(charge_time)
    voltage_points.extend(charge_voltage)
    V = charge_voltage[-1]

    t_measure_end = t_charge_end + t_charge
    measure_time = np.linspace(t_charge_end, t_measure_end, 10)
    measure_voltage = np.full_like(measure_time, V)
    time_points.extend(measure_time)
    voltage_points.extend(measure_voltage)
    t = t_measure_end

    if impulse == check_impulses:
        if V < threshold2:
            axs[0].text(
                0,
                threshold1 * 0.95,
                f"Stopped after {impulse} impulses: {V * 1000:.1f}mV < {threshold2 * 1000}mV",
                ha="left",
                va="top",
                fontsize=10,
            )
            stop = True
            break
    if V >= threshold1:
        axs[0].text(
            0,
            threshold1 * 0.95,
            f"Reached {to_short(threshold1 * 1000, 'V')} threshold after {impulse} impulses",
            ha="left",
            va="top",
            fontsize=10,
        )
        stop = True
        break

if not stop:
    print(f"Completed {max_impulses} impulses. Voltage: {V * 1000:.1f} mV")

# Plotting the graph
axs[0].plot(time_points, voltage_points, label="Capacitor voltage")
axs[0].axhline(threshold1, color="r", linestyle="--", label=f"{threshold1 * 1000} mV threshold")
axs[0].axhline(threshold2, color="g", linestyle="--", label=f"{threshold2 * 1000} mV threshold")
axs[0].set_xlabel("Time, sec")
axs[0].set_ylabel("Voltage, V")
axs[0].set_title(rf'Capacitance Measurement Process $C = {to_short(C, "F")}$')
axs[0].legend()
axs[0].grid(True)


def calculate_impulses(
    C, R=680, VCC=3.3, t_charge=0.01, threshold1=0.3, threshold2=0.075, max_impulses=499, check_impulse=127
):
    """
    Corrected impulse calculation with proper termination logic
    """
    V = 0.0
    tau = R * C
    stop_early = False

    for impulse in range(1, max_impulses + 1):
        V = VCC - (VCC - V) * np.exp(-t_charge / tau)

        # Check early termination condition at 127th impulse
        if impulse == check_impulse and V < threshold2:
            stop_early = True
            break

        # Check success condition
        if V >= threshold1:
            return impulse

    return max_impulses if stop_early else max_impulses


# Extended capacitance range (0.1uF to 0.1F)
capacitors = (1e-5, 1e-1)
capacitances = np.logspace(math.log10(capacitors[0]), math.log10(capacitors[1]), 300)
impulse_counts = []

# Calculate impulses for each capacitance
for C in capacitances:
    count = calculate_impulses(C)
    impulse_counts.append(count)

axs[1].semilogx(capacitances, impulse_counts, "b-", linewidth=1.5)

# Add reference lines
critical_C = 0.01 / (680 * -np.log(1 - 0.3 / 3.3))  # ~154μF
axs[1].axvline(critical_C, color="r", linestyle="--", label=rf"Critical $C = {critical_C * 1e6:.1f}uF$")

axs[1].axhline(499, color="grey", linestyle=":", label="Max impulses (499)")
axs[1].axhline(127, color="green", linestyle=":", label="Check impulse (127)")

# Formatting
axs[1].set_title("Charging Impulses vs Capacitance")
axs[1].set_xlabel("Capacitance (F)")
axs[1].set_ylabel("Number of Impulses")
axs[1].grid(True, which="both", ls="--", alpha=0.5)
axs[1].legend()

# Annotations
axs[1].text(2e-5, 60, "Small Capacitors\nToo Fast Charging", ha="left", va="center", fontsize=9)
axs[1].text(1e-2, 300, "Large Capacitors\nReaching Impulse Limit", ha="right", va="center", fontsize=9)

axs[1].set_xlim(capacitors[0], capacitors[1])
axs[1].set_ylim(0, max_impulses * 1.1)

plt.tight_layout()
plt.savefig("cap.svg")
plt.show()
