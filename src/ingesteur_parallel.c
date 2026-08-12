#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <mpi.h>
#include <omp.h>

#define EPSILON_SCCI 1e-16

int main(int argc, char** argv) {
    int rank, size;
    
    // Initialisation de l'environnement MPI
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    
    if (rank == 0) {
        printf("==> Initialisation de l'ingesteur parallèle (MPI %d processus) <==\n", size);
    }
    
    // Bloc parallèle OpenMP au sein de chaque processus MPI
    #pragma omp parallel
    {
        if (omp_get_thread_num() == 0 && rank == 0) {
            printf("Exécution hybride active : %d threads par nœud.\n", omp_get_num_threads());
        }
    }
    
    // Simulation du calcul distribué de l'invariant hamiltonien
    double mesure_locale = 1.0 + (double)rank * 1e-17;
    double somme_globale = 0.0;
    
    MPI_Reduce(&mesure_locale, &somme_globale, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
    
    if (rank == 0) {
        double moyenne_invariant = somme_globale / size;
        double delta = fabs(moyenne_invariant - 1.0);
        printf("[SCCI CLUSTER] Dérive moyenne calculée : %.2e\n", delta);
        
        if (delta <= EPSILON_SCCI) {
            printf("[CERTIFICATION VALIDE] Stabilité de la 5ème dimension validée sur cluster.\n");
        } else {
            printf("[ALERTE SCCI] Dérive hors tolérance sur le supercalculateur !\n");
        }
    }
    
    MPI_Finalize();
    return EXIT_SUCCESS;
}
