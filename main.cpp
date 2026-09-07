#include <iostream>
#include <vector>
#include <fstream>
#include <random>
#include <iomanip>

int main() {
int S, N;
double p;
std::cout << "Enter the number of steps S: ";
std::cin >> S;
std::cout << "Enter the number of random walk sequences N: ";
std::cin >> N;
std::cout << "Enter the probability of moving right (p, e.g., 0.6): ";
std::cin >> p;

std::vector<std::vector<int>> random_walks(N, std::vector<int>(S + 1, 0));

std::random_device rd;
for (int i = 0; i < N; ++i) {
    std::mt19937 gen(rd() + i);
    std::bernoulli_distribution dist(p); // p for right (+1), 1-p for left (-1)
    for (int j = 1; j <= S; ++j) {
        int step = dist(gen) ? 1 : -1; 
        random_walks[i][j] = random_walks[i][j - 1] + step;
    }
}

// Output average positions and variances
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

std::ofstream avg_file("average_positions_asym.dat");
std::ofstream var_file("variance_positions_asym.dat");
avg_file << std::fixed << std::setprecision(6);
var_file << std::fixed << std::setprecision(6);

for (int j = 0; j <= S; ++j) {
    avg_file << j << " " << average_positions[j] << "\n";
    var_file << j << " " << variance_positions[j] << "\n";
}

avg_file.close();
var_file.close();

std::cout << "Asymmetric random walks data generated successfully." << std::endl;
return 0;
}
