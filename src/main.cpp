#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <cmath>
#include <tbb/parallel_for.h>
#include <tbb/blocked_range2d.h>

using Matrix = std::vector<double>;

inline double& at(Matrix& m, int rows, int cols, int i, int j) {
    return m[static_cast<size_t>(i) * cols + j];
}

inline const double& at(const Matrix& m, int rows, int cols, int i, int j) {
    return m[static_cast<size_t>(i) * cols + j];
}

// Zufällige Matrix erzeugen
Matrix random_matrix(int rows, int cols, double min = -1.0, double max = 1.0) {
    Matrix m(static_cast<size_t>(rows) * cols);
    std::mt19937_64 rng(std::random_device{}());
    std::uniform_real_distribution<double> dist(min, max);

    for (auto& x : m) {
        x = dist(rng);
    }
    return m;
}

// Sequentielle Matrixmultiplikation: C = A (m x k) * B (k x n)
void matmul_sequential(const Matrix& A, const Matrix& B, Matrix& C,
                       int m, int k, int n) {
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            double sum = 0.0;
            for (int p = 0; p < k; ++p) {
                sum += at(A, m, k, i, p) * at(B, k, n, p, j);
            }
            at(C, m, n, i, j) = sum;
        }
    }
}

// Parallele Matrixmultiplikation mit TBB
void matmul_parallel(const Matrix& A, const Matrix& B, Matrix& C,
                     int m, int k, int n) {
    const int grain_rows = 32;
    const int grain_cols = 32;

    tbb::parallel_for(
            tbb::blocked_range2d<int>(0, m, grain_rows,
                                      0, n, grain_cols),
            [&](const tbb::blocked_range2d<int>& r) {
                for (int i = r.rows().begin(); i != r.rows().end(); ++i) {
                    for (int j = r.cols().begin(); j != r.cols().end(); ++j) {
                        double sum = 0.0;
                        for (int p = 0; p < k; ++p) {
                            sum += at(A, m, k, i, p) * at(B, k, n, p, j);
                        }
                        at(C, m, n, i, j) = sum;
                    }
                }
            }
    );
}

// Hilfsfunktion zum Messen der Laufzeit
template <typename F>
double time_in_seconds(F&& func) {
    auto start = std::chrono::high_resolution_clock::now();
    func();
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diff = end - start;
    return diff.count();
}

// Maximaler absolute Unterschied zwischen zwei Matrizen
double max_abs_diff(const Matrix& A, const Matrix& B) {
    if (A.size() != B.size()) {
        throw std::runtime_error("Matrix sizes do not match for comparison");
    }
    double max_diff = 0.0;
    for (size_t i = 0; i < A.size(); ++i) {
        max_diff = std::max(max_diff, std::fabs(A[i] - B[i]));
    }
    return max_diff;
}

int main() {
    // Beispielgrößen (einfach im Code ändern)
    const int rowsA = 800;
    const int colsA = 800;
    const int rowsB = colsA; // muss passen
    const int colsB = 800;

    std::cout << "Matrixgroessen: A = " << rowsA << " x " << colsA
              << ", B = " << rowsB << " x " << colsB << "\n";

    Matrix A = random_matrix(rowsA, colsA);
    Matrix B = random_matrix(rowsB, colsB);

    Matrix C_seq(static_cast<size_t>(rowsA) * colsB);
    Matrix C_par(static_cast<size_t>(rowsA) * colsB);

    // Sequentiell
    double t_seq = time_in_seconds([&] {
        matmul_sequential(A, B, C_seq, rowsA, colsA, colsB);
    });

    // Parallel
    double t_par = time_in_seconds([&] {
        matmul_parallel(A, B, C_par, rowsA, colsA, colsB);
    });

    double diff = max_abs_diff(C_seq, C_par);
    double speedup = t_seq / t_par;

    std::cout << "Sequentiell:  " << t_seq << " s\n";
    std::cout << "Parallel:     " << t_par << " s\n";
    std::cout << "Max. Fehler |C_seq - C_par| = " << diff << "\n";
    std::cout << "Speedup:      " << speedup << "x\n";

    return 0;
}
