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
typedef struct root root;

int nrLines(FILE *input);
//procesarea datelor
nodeA *creeareListaCompanii(FILE *input);
void vectorStock(double price[],FILE *input,int *nr,int nrlines);

root *creeareRoot();
nodeA *creeareNod(nodeA*node,double val);

void emptyLevel(root *root);
void frunzeTree(root *root, double price[], int nr, nodeA **company,int *n);

void urmatoareaZi(root *root,double price[],int index);
void vectorFrunze(root *root,char frunze[][6],int *nr);
void afisarePerechi(FILE *output,nodeA *headc, char frunze[][6],int nr);
