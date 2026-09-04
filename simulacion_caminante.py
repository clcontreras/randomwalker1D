# ========================================================
# Física Estadística: Caminata Aleatoria 1D
# Experimento: Probabilidades Diferentes
#Astrid Saldaña Herrera
# ========================================================

import numpy as np
import matplotlib.pyplot as plt

NUM_PASOS = 1000
NUM_CAMINANTES = 5000

# Definiendo las probabilidades distintas (p=0.6 a la derecha, q=0.4 a la izquierda)
p_derecha = 0.6
p_izquierda = 1.0 - p_derecha


def simular_caminatas(n_pasos, n_caminantes, p_der, p_izq):
    # Saltos con probabilidades desiguales p != q
    saltos = np.random.choice([1, -1], size=(n_caminantes, n_pasos), p=[p_der, p_izq])
    trayectorias = np.cumsum(saltos, axis=1)
    return trayectorias


if __name__ == "__main__":
    trayectorias = simular_caminatas(NUM_PASOS, NUM_CAMINANTES, p_derecha, p_izquierda)

    # Calculando el desplazamiento promedio <x(t)> y la varianza sigma^2(t)
    promedio = np.mean(trayectorias, axis=0)
    varianza = np.var(trayectorias, axis=0)
    tiempo = np.arange(1, NUM_PASOS + 1)

    # Generación y guardado de las gráficas
    plt.figure(figsize=(10, 4))

    plt.subplot(1, 2, 1)
    plt.plot(tiempo, promedio, label=f'Promedio (p={p_derecha})', color='blue')
    plt.xlabel('Tiempo (pasos)')
    plt.ylabel(r'$\langle x(t) \rangle$')
    plt.title('Desplazamiento Promedio')
    plt.grid(True)
    plt.legend()

    plt.subplot(1, 2, 2)
    plt.plot(tiempo, varianza, label=f'Varianza (p={p_derecha})', color='red')
    plt.xlabel('Tiempo (pasos)')
    plt.ylabel(r'$\sigma^2(t)$')
    plt.title('Varianza')
    plt.grid(True)
    plt.legend()

    plt.tight_layout()
    plt.savefig('grafica_desplazamiento_varianza.png')
    print("Simulación completada con probabilidades desiguales.")
    print("Gráfica guardada como 'grafica_desplazamiento_varianza.png'")
