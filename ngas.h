#define NUM_UNITS 200
#define DIM_DATA  2
#define T_MAX     40000

#define LAMBDA_I  30.0
#define LAMBDA_F  0.01
#define EPSILON_I 0.3
#define EPSILON_F 0.05
#define T_I       20
#define T_F       200

struct conn_t {
    int connected;
    int age;
};

struct ngas_network_t {
    double weights[NUM_UNITS][DIM_DATA];
    struct conn_t connections[NUM_UNITS][NUM_UNITS];
    int t;
};

void init_network(struct ngas_network_t *network);
double random_double();
double dist(const double *v, const double *u, int dim);
void adapt_to(struct ngas_network_t *network, double signal[DIM_DATA]);
double time_dependent_value(double i, double f, int t, int t_max);
