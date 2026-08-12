# Makefile - Cadre Déterministe EHK / RS-MNK (SCCI)

CC = gcc
MPICC = mpicc
CFLAGS = -O3 -Wall -Wextra -std=c11 -pedantic
LDFLAGS = -lm

SRC_DIR = src
CLUSTER_DIR = cluster

all: run_benchmark_ehk run_cluster_ehk

# Compilation du binaire de benchmark standard
run_benchmark_ehk: $(SRC_DIR)/ingesteur.c
	$(CC) $(CFLAGS) $< -o $@ $(LDFLAGS)

# Compilation du binaire distribué MPI + OpenMP
run_cluster_ehk: $(SRC_DIR)/ingesteur_parallel.c
	$(MPICC) $(CFLAGS) -fopenmp $< -o $@ $(LDFLAGS)

# Nettoyage des binaires et objets compilés
clean:
	rm -f run_benchmark_ehk run_cluster_ehk *.o $(SRC_DIR)/*.o
