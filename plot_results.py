import numpy as np
import matplotlib.pyplot as plt

# Número de pasos
S = 1000

# Probabilidades utilizadas
probabilities = [0.3, 0.7, 0.9]

# ============================================================
# GRÁFICA 1: DESPLAZAMIENTO PROMEDIO
# ============================================================

plt.figure(figsize=(9, 6))

for p in probabilities:

    # Nombre de los archivos
    p_text = str(p).replace(".", "")
    
    average_data = np.loadtxt(
        f"average_positions_p{p_text}.dat"
    )

    steps = np.arange(S + 1)

    # Resultado teórico:
    # <R> = S(2p - 1)
    average_theoretical = steps * (2.0 * p - 1.0)

    # Simulación
    plt.plot(
        steps,
        average_data,
        label=f"Simulación, p = {p}"
    )

    # Teoría
    plt.plot(
        steps,
        average_theoretical,
        "--",
        label=f"Teoría, p = {p}"
    )

plt.xlabel("Número de pasos")
plt.ylabel("Posición promedio")
plt.title("Desplazamiento promedio del caminante aleatorio")
plt.legend()
plt.grid(True)
plt.tight_layout()

plt.savefig(
    "average_position_comparison.png",
    dpi=300
)

plt.show()


# ============================================================
# GRÁFICA 2: VARIANZA
# ============================================================

plt.figure(figsize=(9, 6))

for p in probabilities:

    # Nombre de los archivos
    p_text = str(p).replace(".", "")

    variance_data = np.loadtxt(
        f"variance_positions_p{p_text}.dat"
    )

    steps = np.arange(S + 1)

    # Resultado teórico:
    # sigma^2 = 4 S p(1-p)
    variance_theoretical = (
        4.0 * steps * p * (1.0 - p)
    )

    # Simulación
    plt.plot(
        steps,
        variance_data,
        label=f"Simulación, p = {p}"
    )

    # Teoría
    plt.plot(
        steps,
        variance_theoretical,
        "--",
        label=f"Teoría, p = {p}"
    )

plt.xlabel("Número de pasos")
plt.ylabel("Varianza")
plt.title("Varianza del caminante aleatorio")
plt.legend()
plt.grid(True)
plt.tight_layout()

plt.savefig(
    "variance_comparison.png",
    dpi=300
)

plt.show()


print("Gráficas comparativas generadas correctamente.")
print()
print("Archivos creados:")
print("  average_position_comparison.png")
print("  variance_comparison.png")