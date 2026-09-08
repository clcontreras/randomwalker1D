import numpy as np
import matplotlib.pyplot as plt

# ============================================
# LEER DATOS DE LOS ARCHIVOS
# ============================================
# Leer posiciones finales
posiciones_finales = np.loadtxt('posiciones_finales.txt')

# Leer evolución temporal
datos_evolucion = np.loadtxt('evolucion_temporal.txt')
pasos = datos_evolucion[:, 0]
promedio = datos_evolucion[:, 1]
varianza = datos_evolucion[:, 2]
# ============================================
# GRÁFICA 1: HISTOGRAMA DE POSICIONES FINALES
# ============================================
plt.figure(figsize=(12, 5))

plt.subplot(1, 2, 1)
plt.hist(posiciones_finales, bins=30, edgecolor='black', alpha=0.7)
plt.xlabel('Posición final')
plt.ylabel('Frecuencia')
plt.title(f'Distribución de posiciones finales (p=0.7)')
plt.axvline(np.mean(posiciones_finales), color='red', linestyle='--', 
            label=f'Promedio = {np.mean(posiciones_finales):.1f}')
plt.legend()
plt.grid(True, alpha=0.3)
# ============================================
# GRÁFICA 2: EVOLUCIÓN DEL PROMEDIO Y VARIANZA
# ============================================
plt.subplot(1, 2, 2)
plt.plot(pasos, promedio, 'b-', label='Promedio')
plt.plot(pasos, varianza, 'g-', label='Varianza')
plt.xlabel('Número de pasos')
plt.ylabel('Valor')
plt.title(f'Evolución temporal (p=0.7)')
plt.legend()
plt.grid(True, alpha=0.3)

plt.tight_layout()
plt.savefig('resultados_caminante.png', dpi=150)
plt.show()
# ============================================
# GRÁFICA 3: SOLO DESPLAZAMIENTO PROMEDIO
# ============================================
plt.figure(figsize=(10, 4))
plt.subplot(1, 2, 1)
plt.plot(pasos, promedio, 'b-', linewidth=2)
plt.xlabel('Número de pasos')
plt.ylabel('Posición promedio')
plt.title('Desplazamiento promedio vs tiempo')
plt.grid(True, alpha=0.3)
# ============================================
# GRÁFICA 4: SOLO VARIANZA
# ============================================
plt.subplot(1, 2, 2)
plt.plot(pasos, varianza, 'g-', linewidth=2)
plt.xlabel('Número de pasos')
plt.ylabel('Varianza')
plt.title('Varianza vs tiempo')
plt.grid(True, alpha=0.3)

plt.tight_layout()
plt.savefig('promedio_varianza.png', dpi=150)
plt.show()
# ============================================
# MOSTRAR ESTADÍSTICAS
# ============================================
print("========================================")
print("ESTADÍSTICAS FINALES")
print("========================================")
print(f"Desplazamiento promedio final: {np.mean(posiciones_finales):.2f}")
print(f"Varianza final: {np.var(posiciones_finales):.2f}")
print(f"Desviación estándar: {np.std(posiciones_finales):.2f}")
print("========================================")
