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
void deleteQueue(Queue *q);
void enq(Queue *q, float val);
float deq(Queue *q);
void creaareStiva(nodeS **share, char city[], FILE *input);