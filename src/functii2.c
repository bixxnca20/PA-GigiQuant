#include "task2.h"

// stive - push, pop, stergere stiva

void push(nodeS **top, float val)
{
    nodeS *nodNou = (nodeS *)malloc(sizeof(nodeS));
    nodNou->val = val;
    nodNou->next = *top;
    *top = nodNou;
}
float pop(nodeS **top)
{
    nodeS *temp = *top;
    float vaux = temp->val;
    *top = (*top)->next;
    free(temp);
    return vaux;
}
void deleteStack(nodeS **top)
{
    nodeS *temp = *top;
    while (*top != NULL)
    {
        temp = *top;
        *top = (*top)->next;
        free(temp);
    }
}
Queue *createQ()
{
    Queue *q = (Queue *)malloc(sizeof(Queue));
    q->front = q->rear = NULL;
    return q;
}
void enq(Queue *q, float val)
{
    shareInfo *nou = (shareInfo *)malloc(sizeof(shareInfo));
    nou->val = val;
    nou->next = NULL;

    if (q->rear == NULL) // queue e empty
    {
        q->front = nou;
        q->rear = nou;
    }
    else
    {
        (q->rear)->next = nou;
        q->rear = nou;
    }
}

// coada - adaugare si stergere element
float deq(Queue *q)
{
    if (q->front == NULL)
    {
        return (float)(-1); // coada este goala
    }

    shareInfo *aux = q->front;
    float val = aux->val;
    q->front = (q->front)->next;

    if (q->front == NULL)
    {
        q->rear = NULL;
    }

    free(aux);
    return val;
}
void deleteQueue(Queue *q)
{
    shareInfo *aux = NULL;
    while (q->front != NULL)
    {
        aux = q->front;
        q->front = q->front->next;
        free(aux);
    }
    free(q);
}

// functii pentru rezolvarea task-ului propriu-zis
void creaareStiva(nodeS **share, char city[], FILE *input)
{
    char lit;
    float val;
    int i = 0;
    strcpy(city, "");
    do
    {
        lit = getc(input);
        if (lit != '\n' && lit != '\r')
            city[i++] = lit;
    } while (lit != '\n');
    city[i] = '\0';
    // s-a aflat denumirea orasului
    while (fscanf(input, "%f", &val) == 1)
    {
        push(share, val);
    }
    // se adauga in stiva share val
}