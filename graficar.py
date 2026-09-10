import numpy as np
import matplotlib.pyplot as plt

# Cargar los archivos .dat
t_avg, x_avg = np.loadtxt('average_positions.dat', unpack=True)
t_var, var = np.loadtxt('variance_positions.dat', unpack=True)

fig, (ax1, ax2) = plt.subplots(1, 2, figsize=(12, 5))

# Gráfica de Posición Promedio
ax1.plot(t_avg, x_avg, color='blue', linewidth=1.5)
ax1.set_title('Posición Promedio vs Tiempo')
ax1.set_xlabel('Pasos (t)')
ax1.set_ylabel('<x>')
ax1.grid(True)

# Gráfica de Varianza
ax2.plot(t_var, var, color='red', linewidth=1.5)
ax2.set_title('Varianza vs Tiempo')
ax2.set_xlabel('Pasos (t)')
ax2.set_ylabel('Varianza')
ax2.grid(True)

plt.tight_layout()
plt.savefig('posicion_y_varianza.png', dpi=300)
plt.show()