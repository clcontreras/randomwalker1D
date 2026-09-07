"Gerardo Adrián Jiménez García"

""" Lee average_positions.dat y variance_positions.dat y guarda dos gráficas 
en PNG: desplazamiento promedio vs. pasos, y varianza vs. pasos."""
import numpy as np
import matplotlib.pyplot as plt

# Cargar los datos: cada archivo tiene dos columnas -> paso, valor
pasos_avg, promedio = np.loadtxt("average_positions.dat", unpack=True)
pasos_var, varianza = np.loadtxt("variance_positions.dat", unpack=True)

# Gráfica del desplazamiento promedio
plt.figure()
plt.plot(pasos_avg, promedio)
plt.xlabel("Número de pasos")
plt.ylabel("Desplazamiento promedio ⟨R⟩")
plt.title("Desplazamiento promedio vs. pasos (probabilidad asimétrica)")
plt.grid(True)
plt.savefig("desplazamiento_promedio.png", dpi=150)

# Gráfica de la varianza
plt.figure()
plt.plot(pasos_var, varianza)
plt.xlabel("Número de pasos")
plt.ylabel("Varianza σ²_R")
plt.title("Varianza vs. pasos (probabilidad asimétrica)")
plt.grid(True)
plt.savefig("varianza.png", dpi=150)

print("Listas: desplazamiento_promedio.png y varianza.png")
