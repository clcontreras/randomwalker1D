import numpy as np
import matplotlib.pyplot as plt

# =====================================================================
# PARÁMETROS DE LA SIMULACIÓN FÍSICA (Caminante Asimétrico 1D)
# =====================================================================
N = 1000       # Número de pasos temporales en la simulación
M = 10000      # Número de caminantes (ensayos para estadística empírica)
p = 0.6        # Probabilidad de paso hacia la derecha (+1)
q = 1.0 - p    # Probabilidad de paso hacia la izquierda (-1)
a = 1.0        # Longitud constante de cada paso discreto

print(f"Iniciando simulación para M={M} caminantes con N={N} pasos...")
print(f"Probabilidades establecidas: p={p} (derecha), q={q} (izquierda)")

# =====================================================================
# GENERACIÓN DE TRAYECTORIAS (Simulación Monte Carlo)
# =====================================================================
# Elegimos de forma aleatoria pasos de +a o -a para cada caminante y paso
pasos = np.random.choice([a, -a], size=(M, N), p=[p, q])

# Calculamos la trayectoria acumulando los desplazamientos de los pasos
# Agregamos una columna de ceros en t=0 para representar la posición inicial x=0
trayectorias = np.hstack([np.zeros((M, 1)), np.cumsum(pasos, axis=1)])

# =====================================================================
# CÁLCULO DE PROPIEDADES ESTADÍSTICAS
# =====================================================================
# Estadísticas empíricas obtenidas del promedio de los caminantes simulados
promedio_simulado = np.mean(trayectorias, axis=0)
varianza_simulada = np.var(trayectorias, axis=0)

# Eje temporal de pasos de t = 0 hasta N
pasos_eje = np.arange(N + 1)

# Estadísticas teóricas (Curvas analíticas derivadas de la probabilidad binomial)
promedio_teorico = pasos_eje * (p - q) * a
varianza_teorica = 4 * pasos_eje * p * q * (a**2)

# =====================================================================
# GENERACIÓN Y DISEÑO DE GRÁFICAS COMPARATIVAS
# =====================================================================
plt.figure(figsize=(14, 6))

# Gráfica 1: Desplazamiento Promedio (Deriva o Arrastre)
plt.subplot(1, 2, 1)
plt.plot(pasos_eje, promedio_simulado, label='Simulación Empírica (Promedio)', color='#005b96', alpha=0.85, linewidth=1.5)
plt.plot(pasos_eje, promedio_teorico, '--', label='Línea Teórica de Deriva', color='#cc5500', linewidth=2)
plt.title('Desplazamiento Promedio $\\langle x \\rangle$ vs. Tiempo')
plt.xlabel('Paso ($N$)')
plt.ylabel('Posición Promedio $\\langle x \\rangle$')
plt.grid(True, linestyle=':', alpha=0.6)
plt.legend()

# Gráfica 2: Varianza (Dispersión Espacial)
plt.subplot(1, 2, 2)
plt.plot(pasos_eje, varianza_simulada, label='Simulación Empírica (Varianza)', color='#009688', alpha=0.85, linewidth=1.5)
plt.plot(pasos_eje, varianza_teorica, '--', label='Línea Teórica de Varianza', color='#d32f2f', linewidth=2)
plt.title('Varianza de Posición $\\sigma_x^2$ vs. Tiempo')
plt.xlabel('Paso ($N$)')
plt.ylabel('Varianza $\\sigma_x^2$')
plt.grid(True, linestyle=':', alpha=0.6)
plt.legend()

plt.tight_layout()

# Guardar la gráfica resultante en formato PNG de alta resolución
nombre_imagen = 'graficas_caminante_asimétrico.png'
plt.savefig(nombre_imagen, dpi=300, bbox_inches='tight')
print(f"Simulación finalizada. Gráficas guardadas con éxito como '{nombre_imagen}'.")