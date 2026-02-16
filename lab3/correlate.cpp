#include <cmath>
#include <omp.h>

void correlate(int ny, int nx, const float* data, float* result)
{
    // Allocate arrays
    double* mean = new double[ny];
    double* norm = new double[ny];

    // ----------------------------
    // Step 1: Compute mean of each row
    // ----------------------------
    for (int i = 0; i < ny; i++) {
        const float* row = data + i * nx;

        double sum = 0.0;
        for (int x = 0; x < nx; x++) {
            sum += row[x];
        }

        mean[i] = sum / nx;
    }

    // ----------------------------
    // Step 2: Compute norm of each row
    // ----------------------------
    for (int i = 0; i < ny; i++) {
        const float* row = data + i * nx;

        double sum = 0.0;
        for (int x = 0; x < nx; x++) {
            double val = row[x] - mean[i];
            sum += val * val;
        }

        norm[i] = std::sqrt(sum);
    }

    // ----------------------------
    // Step 3: Compute correlations (Parallel)
    // ----------------------------
    #pragma omp parallel for schedule(static)
    for (int i = 0; i < ny; i++) {

        const float* row_i = data + i * nx;

        for (int j = 0; j <= i; j++) {

            const float* row_j = data + j * nx;

            double numerator = 0.0;

            for (int x = 0; x < nx; x++) {
                double a = row_i[x] - mean[i];
                double b = row_j[x] - mean[j];
                numerator += a * b;
            }

            double corr = numerator / (norm[i] * norm[j]);

            result[i + j * ny] = (float)corr;
        }
    }

    delete[] mean;
    delete[] norm;
}
