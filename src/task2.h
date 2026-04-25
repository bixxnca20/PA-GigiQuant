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
//nodurile pt coada care contin detalii suplimentare (ziua, diferenta si orasul)
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

//declararea functiilor utilizate pe stive
//adaugarea unui element in stiva
void push(nodeS **top, float val);
//eliminarea unui element din stiva
float pop(nodeS **top);
//stergerea stivei
void deleteStack(nodeS **top);

//declararea functiilor utilizate pe coada
//creearea unei cozi
Queue *createQ();
//adaugarea unui element in coada
void enq(Queue *q, float val, int day, const char *city);
//eliminarea unui element din coada
void deq(Queue *q);
//stergerea unei cozi
void deleteQueue(Queue *q);

//functii pentru task-ul 2
//pentru creearea celor 3 stive + retinerea orasului
void creaareStiva(nodeS **share, char city[], FILE *input);
//creearea cozii finale
void creeareCoada(nodeS **share1, nodeS **share2, nodeS **share3, Queue *q, char *city1, char *city2, char *city3);
//afisarea elementelor + eliminarea nodurilor
void afisareCoada(Queue *q, FILE *output);