#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "ngas.h"

#define WEIGHT_INIT_MIN 90.0
#define WEIGHT_INIT_MAX 100.0

void test_init_network() {
    printf("Testing init_network()... ");

    struct ngas_network network;
    init_network(&network);

    for (int i = 0; i < NUM_UNITS; ++i) {
	for (int j = 0; j < DIM_DATA; ++j) {
	    assert(network.weights[i][j] >= WEIGHT_INIT_MIN);
	    assert(network.weights[i][j] <= WEIGHT_INIT_MAX);
	}

	for (int j = 0; j < NUM_UNITS; ++j) {
	    assert(network.connections[i][j].connected == 0);
	    assert(network.connections[i][j].age == 0);
	}
    }

    printf("OK\n");
}

void test_random_double() {
    printf("Testing random_double()... ");

    srand(time(NULL));

    double x;
    for (int i = 0; i < 10; ++i) {
	x = random_double();
	assert(x >= WEIGHT_INIT_MIN);
	assert(x <= WEIGHT_INIT_MAX);
    }

    printf("OK\n");
}

void test_dist() {
    printf("Testing dist()... ");

    double v[] = { 1, 2 };
    double u[] = { 0, -1 };
    assert(dist(v, u, 2) > 3.162);
    assert(dist(v, u, 2) < 3.163);

    double x[] = { 35, -2, 5, 8.71, -92.3 };
    double y[] = { 0, -1, -2, -3, 4 };
    assert(dist(x, y, 5) > 103.372);
    assert(dist(y, x, 5) < 103.373);

    printf("OK\n");
}

void test_adapt_to() {
    printf("Testing adapt_to()...\n");

    struct ngas_network network;
    init_network(&network);

    for (int i = 0; i < T_MAX; ++i) {
	double v[DIM_DATA];

	for (int j = 0; j < DIM_DATA; ++j)
	    v[j] = random_double();

	adapt_to(&network, v);
    }

    for (int i = 0; i < NUM_UNITS; ++i) {
	for (int j = 0; j < NUM_UNITS; ++j)
	    printf("%d", network.connections[i][j].connected);
	printf("\n");
    }

    printf("OK\n");
}

int main(int argc, char *argv[]) {
    test_init_network();
    test_random_double();
    test_dist();
    test_adapt_to();
}
