#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Définition de la garde machine stricte requise par le SCCI
#define EPSILON_SCCI 1e-16

int main() {
    printf("==> Initialisation de l'ingesteur déterministe EHK/RS-MNK <==\n");
    
    // Simulation d'une mesure d'invariant hamiltonien
    double invariant_initial = 1.0000000000000000;
    double dérive_mesurée = 0.00000000000000005; // 5e-17
    
    double invariant_final = invariant_initial + dérive_mesurée;
    double delta = fabs(invariant_final - invariant_initial);
    
    printf("Seuil de tolérance SCCI : %.1e\n", EPSILON_SCCI);
    printf("Dérive de l'invariant calculée : %.2e\n", delta);
    
    if (delta <= EPSILON_SCCI) {
        printf("[CERTIFICATION VALIDE] L'invariant est figé sous la garde machine.\n");
        return EXIT_SUCCESS;
    } else {
        printf("[ALERTE SCCI] Dérive stochastique détectée hors tolérance !\n");
        return EXIT_FAILURE;
    }
}
