#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <fstream>  // Para guardar archivos
#include <vector>   // Para usar vectores

int main() {
    // ============================================
    // PARÁMETROS DE LA SIMULACIÓN
    // ============================================
    double p = 0.7;  // Probabilidad de ir a la derecha (70%)
    double q = 1 - p; // Probabilidad de ir a la izquierda (30%)
    int N_pasos = 1000;    // Número de pasos por caminante
    int N_caminantes = 500; // Número de caminantes
    
    std::cout << "========================================" << std::endl;
    std::cout << "CAMINANTE ALEATORIO CON PROBABILIDAD DIFERENTE" << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << "Probabilidad derecha (p): " << p << std::endl;
    std::cout << "Probabilidad izquierda (q): " << q << std::endl;
    std::cout << "Número de pasos: " << N_pasos << std::endl;
    std::cout << "Número de caminantes: " << N_caminantes << std::endl;
    
    // ============================================
    // INICIALIZAR GENERADOR DE NÚMEROS ALEATORIOS
    // ============================================
    srand(time(0));
    
    // ============================================
    // SIMULAR TODOS LOS CAMINANTES
    // ============================================
    std::vector<int> posiciones_finales(N_caminantes);
    std::vector<std::vector<int>> todas_trayectorias(N_caminantes, std::vector<int>(N_pasos));
    
    // Para calcular promedio y varianza en cada paso
    std::vector<double> promedio_tiempo(N_pasos, 0.0);
    std::vector<double> varianza_tiempo(N_pasos, 0.0);
    
    for (int caminante = 0; caminante < N_caminantes; caminante++) {
        int posicion = 0;
        
        for (int paso = 0; paso < N_pasos; paso++) {
            // Generar número aleatorio entre 0 y 1
            double random = (double)rand() / RAND_MAX;
            
            // Decidir dirección según probabilidad p
            if (random < p) {
                posicion++;  // Ir a la derecha
            } else {
                posicion--;  // Ir a la izquierda
            }
            
            // Guardar la posición en este paso
            todas_trayectorias[caminante][paso] = posicion;
            
            // Acumular para promedios
            promedio_tiempo[paso] += posicion;
            varianza_tiempo[paso] += (double)posicion * posicion;
        }
        
        posiciones_finales[caminante] = posicion;
    }
    
    // ============================================
    // CALCULAR PROMEDIO Y VARIANZA FINAL
    // ============================================
    double suma_posiciones = 0.0;
    double suma_cuadrados = 0.0;
    
    for (int i = 0; i < N_caminantes; i++) {
        suma_posiciones += posiciones_finales[i];
        suma_cuadrados += (double)posiciones_finales[i] * posiciones_finales[i];
    }
    
    double promedio_final = suma_posiciones / N_caminantes;
    double varianza_final = (suma_cuadrados / N_caminantes) - (promedio_final * promedio_final);
    
    std::cout << "----------------------------------------" << std::endl;
    std::cout << "RESULTADOS FINALES:" << std::endl;
    std::cout << "Desplazamiento promedio: " << promedio_final << std::endl;
    std::cout << "Varianza: " << varianza_final << std::endl;
    std::cout << "========================================" << std::endl;
     // ============================================
    // CALCULAR PROMEDIO Y VARIANZA EN CADA PASO
    // ============================================
    for (int paso = 0; paso < N_pasos; paso++) {
        promedio_tiempo[paso] /= N_caminantes;
        varianza_tiempo[paso] = (varianza_tiempo[paso] / N_caminantes) - 
                                (promedio_tiempo[paso] * promedio_tiempo[paso]);
    }
    
    // ============================================
    // GUARDAR DATOS EN ARCHIVOS PARA GRÁFICAS
    // ============================================
    // Guardar posiciones finales (para histograma)
    std::ofstream archivo_finales("posiciones_finales.txt");
    for (int i = 0; i < N_caminantes; i++) {
        archivo_finales << posiciones_finales[i] << std::endl;
    }
    archivo_finales.close();
    
    // Guardar evolución temporal (para gráficas de promedio y varianza)
    std::ofstream archivo_evolucion("evolucion_temporal.txt");
    for (int paso = 0; paso < N_pasos; paso++) {
        archivo_evolucion << paso << " " 
                         << promedio_tiempo[paso] << " " 
                         << varianza_tiempo[paso] << std::endl;
    }archivo_evolucion.close();
    
    std::cout << "Datos guardados en:" << std::endl;
    std::cout << "  - posiciones_finales.txt" << std::endl;
    std::cout << "  - evolucion_temporal.txt" << std::endl;
    std::cout << "========================================" << std::endl;
    
    return 0;
}
