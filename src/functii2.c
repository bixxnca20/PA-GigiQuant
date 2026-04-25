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
    while (*top != NULL)
    {
        nodeS *temp = *top;
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
void enq(Queue *q, float val, int day, const char city[])
{
    shareInfo *nou = (shareInfo *)malloc(sizeof(shareInfo));
    nou->val = val;
    nou->day = day;
    strcpy(nou->city, city);
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
void deq(Queue *q)
{
    if (q->front == NULL)
    {
        return; // coada este goala
    }

    shareInfo *aux = q->front;
    q->front = (q->front)->next;

    if (q->front == NULL)
        q->rear = NULL;

    free(aux);
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
void creeareCoada(nodeS **share1, nodeS **share2, nodeS **share3, Queue *q, char *city1, char *city2, char *city3)
{
    int i = 1;
    while (*share1 != NULL && *share2 != NULL && *share3 != NULL)
    {
        if ((*share1)->val == (*share2)->val && (*share1)->val != (*share3)->val)
            enq(q, fabs((*share1)->val - (*share3)->val), i, city3); // diferenta,ziua,orasul diferit
        else if ((*share1)->val == (*share3)->val && (*share1)->val != (*share2)->val)
            enq(q, fabs((*share1)->val - (*share2)->val), i, city2); // diferenta,ziua,orasul diferit
        else if ((*share2)->val == (*share3)->val && (*share1)->val != (*share2)->val)
            enq(q, fabs((*share1)->val - (*share3)->val), i, city1); // diferenta,ziua,orasul diferit

        pop(share1);
        pop(share2);
        pop(share3);

        i++;
    }
}
void afisareCoada(Queue *q, FILE *output)
{
    while (q->front != NULL)
    {
        fprintf(output, "ziua %d - %.2f - %s\n", q->front->day, q->front->val, q->front->city);
        deq(q);
    }
}