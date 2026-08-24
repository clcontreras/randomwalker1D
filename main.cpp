// This program simulates a simple random walker in a 1D grid size N and equally spaced points.
// Walker starts at the center of the grid which is located at x=0, and takes steps to the left or right with equal probability.
// A two dimensional vector is initialized to store the random walk sequence of S steps in a row, where each row corresponds to a random walk sequence generated from a different random seed.
// All rows are generated from different random seeds.
// It is assumed that the time intervals are all equal and the walker takes one step at each time interval.
// The program starts by asking the user to input the number of steps S and the number of random walk sequences N.
// After generating the random walk sequences, the program outputs all random walks to a file named "random_walks.dat"
// The output files contains a column for time or step number, and N columns for the random walk sequences generated from different random seeds.
// After that, the program calculates the average position of the walker at each time step across all random walk sequences and outputs the average positions to a file named "average_positions.dat".
// It also obtains the variance of the walker's position at each time step across all random walk sequences and outputs the variance to a file named "variance_positions.dat",
// with the variance defined as the average of the squared displacement from the origin minus the squared average position at each time step, sigma^2_R=<R^2>-<R>^2, where R is the position of the walker at each time step.
// Program starts.
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

    // Initialize a 2D vector to store the random walk sequences
    std::vector<std::vector<int>> random_walks(N, std::vector<int>(S + 1, 0));

    // Generate random walk sequences
    std::random_device rd;
    for (int i = 0; i < N; ++i) {
        std::mt19937 gen(rd() + i); // Different seed for each sequence
        std::uniform_int_distribution<> dis(0, 1); // 0 for left, 1 for right
        for (int j = 1; j <= S; ++j) {
            int step = dis(gen) == 0 ? -1 : 1; // Step left or right
            random_walks[i][j] = random_walks[i][j - 1] + step; // Update position
        }
    }

    // Output random walks to file
    std::ofstream random_walks_file("random_walks.dat");
    random_walks_file << std::fixed << std::setprecision(6);
    for (int j = 0; j <= S; ++j) {
        random_walks_file << j; // Time step
        for (int i = 0; i < N; ++i) {
            random_walks_file << " " << random_walks[i][j]; // Random walk positions
        }
        random_walks_file << "\n";
    }

    // Calculate average positions and variances
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

    // Output average positions to file
    std::ofstream average_positions_file("average_positions.dat");
    average_positions_file << std::fixed << std::setprecision(6);
    for (int j = 0; j <= S; ++j) {
        average_positions_file << j << " " << average_positions[j] << "\n";
    }

    // Output variances to file
    std::ofstream variance_positions_file("variance_positions.dat");
    variance_positions_file << std::fixed << std::setprecision(6);
    for (int j = 0; j <= S; ++j) {
        variance_positions_file << j << " " << variance_positions[j] << "\n";
    }

    std::cout << "Random walks, average positions, and variances have been written to files." << std::endl;

    // Close files
    random_walks_file.close();
    average_positions_file.close();
    variance_positions_file.close();
}