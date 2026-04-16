#include <stdio.h>
#include <stdlib.h>
#include <math.h>


struct node{
    double valoare;
    double randament;
    struct node *next;
};
typedef struct node node;

void calculareVolatilitate(int nr_op,node *head,double randMediu, double *volatilitate,FILE *input);
void adaugareRandament(int nr_op, node **head,double *randMediu,FILE *input);
void creeareLista(int n,node *head,FILE *input);
void eliberareMemorie(node **head);