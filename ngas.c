#include <float.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

#include "ngas.h"

void init_network(struct ngas_network_t *network) {
    srand(time(NULL));
    
    for (int i = 0; i < NUM_UNITS; ++i) {
	for (int j = 0; j < DIM_DATA; ++j)
	    network->weights[i][j] = random_double();

	for (int j = 0; j < NUM_UNITS; ++j) {
	    network->connections[i][j].connected = 0;
	    network->connections[i][j].age = 0;
	}
    }

    network->t = 0;
}

double random_double() {
    return 90.0 + (rand() / (RAND_MAX / (100.0-90.0)));
}

double dist(const double *v, const double *u, int dim) {
    double sum = 0;

    for (int i = 0; i < dim; ++i)
	sum += pow(*(u+i) - *(v+i), 2);

    return sqrt(sum);
}

void adapt_to(struct ngas_network_t *network, double signal[DIM_DATA]) {
    double distances[NUM_UNITS];
    int n = 0, ci, next_ci;

    double lambda = time_dependent_value(LAMBDA_I, LAMBDA_F, network->t, T_MAX);
    double epsilon = time_dependent_value(EPSILON_I, EPSILON_F, network->t, T_MAX);
    double T = time_dependent_value(T_I, T_F, network->t, T_MAX);

    for (int i = 0; i < NUM_UNITS; ++i)
	distances[i] = dist(network->weights[i], signal, DIM_DATA);

    while (n < NUM_UNITS) {
	ci = 0;
	for (int i = 1; i < NUM_UNITS; ++i)
	    if (distances[i] < distances[ci])
		ci = i;

	distances[ci] = DBL_MAX;

	next_ci = 0;
	for (int i = 1; i < NUM_UNITS; ++i)
	    if (distances[i] < distances[next_ci])
		next_ci = i;

	for (int i = 0; i < DIM_DATA; ++i)
	    network->weights[ci][i] = network->weights[ci][i]
		+ epsilon * exp(-n/lambda) * (signal[i] - network->weights[ci][i]);

	if (network->connections[ci][next_ci].connected == 0) {
	    network->connections[ci][next_ci].connected = 1;
	    network->connections[ci][next_ci].age = 0;
	}
	else if (network->connections[ci][next_ci].connected == 1)
	    network->connections[ci][next_ci].age = 0;

	for (int i = 0; i < NUM_UNITS; ++i) {
	    if (network->connections[ci][i].connected == 1) {
		++(network->connections[ci][i].age);
		if (network->connections[ci][i].age > T)
		    network->connections[ci][i].connected = 0;
	    }
	}

	++n;
    }
}

double time_dependent_value(double i, double f, int t, int t_max) {
    return i * pow(f/i, t/t_max);
}
