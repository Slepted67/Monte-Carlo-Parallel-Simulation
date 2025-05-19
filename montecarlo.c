#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <math.h>

int main(int argc, char** argv) {
    long long int num_darts = 1000000000; // Default: 1 billion darts
    int max_threads = 48;

    if (argc > 1) {
        num_darts = atoll(argv[1]); // Allow override from command line
    }

    printf("Number of darts: %lld\n\n", num_darts);
    double pi_actual = acos(-1.0);

    for (int num_threads = 1; num_threads <= max_threads; num_threads++) {
        long long int hits = 0;
        double start_time = omp_get_wtime();

        #pragma omp parallel num_threads(num_threads)
        {
            unsigned int seed = 1234 + omp_get_thread_num(); // Private seed
            long long int local_hits = 0;

            #pragma omp for
            for (long long int i = 0; i < num_darts; i++) {
                double x = (double)rand_r(&seed) / RAND_MAX * 2.0 - 1.0;
                double y = (double)rand_r(&seed) / RAND_MAX * 2.0 - 1.0;

                if (x * x + y * y <= 1.0) {
                    local_hits++;
                }
            }

            #pragma omp atomic
            hits += local_hits;
        }

        double elapsed_time = omp_get_wtime() - start_time;
        double pi_estimate = 4.0 * (double)hits / (double)num_darts;
        double error = fabs(pi_estimate - pi_actual);

        printf("Threads: %d\n", num_threads);
        printf("Estimated Pi = %.12f\n", pi_estimate);
        printf("Error        = %.12f\n", error);
        printf("Elapsed Time = %.4f seconds\n\n", elapsed_time);
    }

    return 0;
}
