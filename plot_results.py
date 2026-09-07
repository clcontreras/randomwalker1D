import matplotlib.pyplot as plt

# Leer datos de promedio
steps_avg, avg_pos = [], []
with open("average_positions_asym.dat", "r") as f:
for line in f:
    parts = line.split()
    if len(parts) == 2:
        steps_avg.append(int(parts[0]))
        avg_pos.append(float(parts[1]))

# Leer datos de varianza
steps_var, var_pos = [], []
with open("variance_positions_asym.dat", "r") as f:
for line in f:
    parts = line.split()
    if len(parts) == 2:
        steps_var.append(int(parts[0]))
        var_pos.append(float(parts[1]))

# Graficar desplazamiento promedio
plt.figure(figsize=(8, 5))
plt.plot(steps_avg, avg_pos, label="<R> (p=0.1)", color="blue")
plt.xlabel("Steps (S)")
plt.ylabel("Average Position")
plt.title("Random Walker 1D: Average Position (Asymmetric p=0.1)")
plt.legend()
plt.grid(True)
plt.savefig("average_position.png")
plt.close()

# Graficar varianza
plt.figure(figsize=(8, 5))
plt.plot(steps_var, var_pos, label="Variance (p=0.1)", color="red")
plt.xlabel("Steps (S)")
plt.ylabel("Variance")
plt.title("Random Walker 1D: Variance (Asymmetric p=0.1)")
plt.legend()
plt.grid(True)
plt.savefig("variance_position.png")
plt.close()

print("Graphs generated and saved successfully!")
