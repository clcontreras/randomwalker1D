
// Cambio realizado en master para practicar la resolucion de conflictos.
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
>>>>>>> master
// Program starts.

#include <iostream>
#include <vector>
#include <fstream>
#include <random>
#include <iomanip>

int main() {

    // ------------------------------------------------------------
    // Input parameters
    // ------------------------------------------------------------

    std::cout << "Enter the number of steps S: ";
    int S;
    std::cin >> S;

    if (S <= 0) {
        std::cerr << "Error: the number of steps must be greater than 0."
                  << std::endl;
        return 1;
    }

    std::cout << "Enter the number of random walk sequences N: ";
    int N;
    std::cin >> N;

    if (N <= 0) {
        std::cerr << "Error: the number of random walk sequences must be greater than 0."
                  << std::endl;
        return 1;
    }

    // Probability of taking a step to the right.
    std::cout << "Enter the probability of stepping to the right p (0 <= p <= 1): ";
    double p_right;
    std::cin >> p_right;

    // Check that the probability is valid.
    if (p_right < 0.0 || p_right > 1.0) {
        std::cerr << "Error: the probability must be between 0 and 1."
                  << std::endl;
        return 1;
    }

    // Probability of taking a step to the left.
    double p_left = 1.0 - p_right;

    std::cout << std::fixed << std::setprecision(6);
    std::cout << "\nProbability of stepping right: " << p_right << std::endl;
    std::cout << "Probability of stepping left:  " << p_left << std::endl;

    // ------------------------------------------------------------
    // Initialize a 2D vector to store the random walk sequences
    // ------------------------------------------------------------

    std::vector<std::vector<int>> random_walks(
        N,
        std::vector<int>(S + 1, 0)
    );

    // ------------------------------------------------------------
    // Generate random walk sequences
    // ------------------------------------------------------------

    std::random_device rd;

    for (int i = 0; i < N; ++i) {

        // Different seed for each random walk sequence.
        std::mt19937 gen(rd() + i);

        // Generates a real random number between 0 and 1.
        std::uniform_real_distribution<double> dis(0.0, 1.0);

        for (int j = 1; j <= S; ++j) {

            double random_number = dis(gen);

            int step;

            // Move to the right with probability p_right.
            // Otherwise move to the left.
            if (random_number < p_right) {
                step = 1;
            }
            else {
                step = -1;
            }

            // Update the position of the walker.
            random_walks[i][j] =
                random_walks[i][j - 1] + step;
        }
    }

    // ------------------------------------------------------------
    // Output random walks to file
    // ------------------------------------------------------------

    std::ofstream random_walks_file("random_walks.dat");

    if (!random_walks_file) {
        std::cerr << "Error: could not open random_walks.dat."
                  << std::endl;
        return 1;
    }

    random_walks_file << std::fixed << std::setprecision(6);

    for (int j = 0; j <= S; ++j) {

        // Time step.
        random_walks_file << j;

        for (int i = 0; i < N; ++i) {

            // Position of each random walk.
            random_walks_file
                << " "
                << random_walks[i][j];
        }

        random_walks_file << "\n";
    }

    // ------------------------------------------------------------
    // Calculate average positions and variances
    // ------------------------------------------------------------

    std::vector<double> average_positions(
        S + 1,
        0.0
    );

    std::vector<double> variance_positions(
        S + 1,
        0.0
    );

    for (int j = 0; j <= S; ++j) {

        double sum = 0.0;
        double sum_squares = 0.0;

        for (int i = 0; i < N; ++i) {

            double position = random_walks[i][j];

            // Sum of positions.
            sum += position;

            // Sum of squared positions.
            sum_squares += position * position;
        }

        // Average position:
        //
        // <R> = (1/N) sum R_i
        //
        average_positions[j] = sum / N;

        // Variance:
        //
        // sigma^2 = <R^2> - <R>^2
        //
        variance_positions[j] =
            (sum_squares / N)
            - (average_positions[j] * average_positions[j]);
    }

    // ------------------------------------------------------------
    // Output average positions to file
    // ------------------------------------------------------------

    std::ofstream average_positions_file(
        "average_positions.dat"
    );

    if (!average_positions_file) {
        std::cerr << "Error: could not open average_positions.dat."
                  << std::endl;
        return 1;
    }

    average_positions_file
        << std::fixed
        << std::setprecision(6);

    for (int j = 0; j <= S; ++j) {

        average_positions_file
            << j
            << " "
            << average_positions[j]
            << "\n";
    }

    // ------------------------------------------------------------
    // Output variances to file
    // ------------------------------------------------------------

    std::ofstream variance_positions_file(
        "variance_positions.dat"
    );

    if (!variance_positions_file) {
        std::cerr << "Error: could not open variance_positions.dat."
                  << std::endl;
        return 1;
    }

    variance_positions_file
        << std::fixed
        << std::setprecision(6);

    for (int j = 0; j <= S; ++j) {

        variance_positions_file
            << j
            << " "
            << variance_positions[j]
            << "\n";
    }

    // ------------------------------------------------------------
    // Close files
    // ------------------------------------------------------------

    random_walks_file.close();
    average_positions_file.close();
    variance_positions_file.close();

    // ------------------------------------------------------------
    // Final message
    // ------------------------------------------------------------

    std::cout << "\nRandom walks, average positions, and variances "
              << "have been written to files."
              << std::endl;

    return 0;
}

