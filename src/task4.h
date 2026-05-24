#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

struct graph
{
    int v;
    int **mat; 
};
typedef struct graph graph;

int nrMuchii(graph *g, int nod);
void cmmdc(int *numarator, int *numitor);

int creeareIntervaluri(int nrstari, float size, float start, const float prices[], float *interval);
graph *creareaGraf(int nrstari, float size, float start, const float prices[], const float interval[], int nrInterval);
void Stare(FILE *output, graph *g, float size, int days, float start, float target,const float interval[], int **stare);