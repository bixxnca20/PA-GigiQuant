#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

struct stiva
{
    float val;
    struct stiva *next;
};
typedef struct stiva nodeS;
struct shareInfo
{
    int day;
    float val;
    char city[30];
    struct shareInfo *next;
};
typedef struct shareInfo shareInfo;
struct queue
{
    shareInfo *front, *rear;
};
typedef struct queue Queue;

void push(nodeS **top, float val);
float pop(nodeS **top);
void deleteStack(nodeS **top);

Queue *createQ();
void enq(Queue *q, float val, int day, const char *city);
void deq(Queue *q);
void deleteQueue(Queue *q);

void creaareStiva(nodeS **share, char city[], FILE *input);
void creeareCoada(nodeS **share1, nodeS **share2, nodeS **share3, Queue *q, char *city1, char *city2, char *city3);
void afisareCoada(Queue *q, FILE *output);