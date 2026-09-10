#include <iostream>
#include <vector>
#include <fstream>
#include <random>
#include <iomanip>

int main() {
    std::cout << "Enter the number of steps S: ";
    int S;
    std::cin >> S;
    std::cout << "Enter the number of random walk sequences N: ";
    int N;
    std::cin >> N;

    std::vector<std::vector<int>> random_walks(N, std::vector<int>(S + 1, 0));

    std::random_device rd;
    for (int i = 0; i < N; ++i) {
        std::mt19937 gen(rd() + i);
        // Genera decimales entre 0.0 y 1.0
        std::uniform_real_distribution<double> dis(0.0, 1.0);
        
        for (int j = 1; j <= S; ++j) {
            // Probabilidad asimétrica: 70% derecha (+1), 30% izquierda (-1)
            int step = (dis(gen) < 0.7) ? 1 : -1;
            random_walks[i][j] = random_walks[i][j - 1] + step;
        }
    }

    std::ofstream random_walks_file("random_walks.dat");
    random_walks_file << std::fixed << std::setprecision(6);
    for (int j = 0; j <= S; ++j) {
        random_walks_file << j;
        for (int i = 0; i < N; ++i) {
            random_walks_file << " " << random_walks[i][j];
        }
        random_walks_file << "\n";
    }

    std::vector<double> average_positions(S + 1, 0.0);
    std::vector<double> variance_positions(S + 1, 0.0);
    for (int j = 0; j <= S; ++j) {
        double sum = 0.0;
        double sum_squares = 0.0;
        for (int i = 0; i < N; ++i) {
            sum += random_walks[i][j];
            sum_squares += random_walks[i][j] * random_walks[i][j];
        }
        average_positions[j] = sum / N;
        variance_positions[j] = sum_squares / N - average_positions[j] * average_positions[j];
    }

    std::ofstream average_positions_file("average_positions.dat");
    average_positions_file << std::fixed << std::setprecision(6);
    for (int j = 0; j <= S; ++j) {
        average_positions_file << j << " " << average_positions[j] << "\n";
    }

    std::ofstream variance_positions_file("variance_positions.dat");
    variance_positions_file << std::fixed << std::setprecision(6);
    for (int j = 0; j <= S; ++j) {
        variance_positions_file << j << " " << variance_positions[j] << "\n";
    }

    std::cout << "Random walks, average positions, and variances have been written to files." << std::endl;

    random_walks_file.close();
    average_positions_file.close();
    variance_positions_file.close();

    return 0;
}
