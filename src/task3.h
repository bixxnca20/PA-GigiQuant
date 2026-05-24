#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

struct nodeA
{
    char name[6];
    double valoare;
    int index;
    struct nodeA *next;
};
typedef struct nodeA nodeA;
struct root
{
    nodeA *nod;
    struct root *left, *right;
};
typedef struct root ROOT;

int nrLines(FILE *input);
//procesarea datelor
void creeareListaCompanii(FILE *input,nodeA *headc);
void vectorStock(double price[],FILE *input,int *nr,int nrlines);

nodeA *creeareNod(const nodeA*node,double val);
void frunze(ROOT *root,char matfrunze[][5],int *index);
void frunzeTree(ROOT *root, double price[], int nr, nodeA **company,int *n);

void perechiCompanii(FILE *output, ROOT *left, ROOT *right);


void nrCompanii(ROOT *root,char frunze[][6],int *index,int nrcomp[],int *indexc);
void perechiCompanii(FILE *output, ROOT *left, ROOT *right);


void colectareFrunze(ROOT *root,nodeA **cosfrunze,int *indexcolectare);
void afisareFrunze(FILE *output,nodeA **cosfrunze, int index);

void freeTree(ROOT *root);
void freeList(nodeA *head);
