#include "task1.h"

void calculareVolatilitate(int nr_op,node *head,double randMediu, double *volatilitate,FILE *input)
{
    *volatilitate=0;
    for(node *p=head->next;p!=NULL;p=p->next)
        *volatilitate+= (p->randament-randMediu)*(p->randament-randMediu);
    *volatilitate=sqrt((*volatilitate)*1.0 /(nr_op-1));
}
void adaugareRandament(int nr_op, node **head,double *randMediu,FILE *input)
{
    double suma_rand=0;
    double val_ant= (*head)->valoare;

    //se calculeaza randamentul pentru fiecare nod
    for(node *p= (*head)->next;p!=NULL;p=p->next)
    {
        p->randament=(p->valoare - val_ant)*1.0 / val_ant;
        suma_rand+=p->randament;
        val_ant=p->valoare;
    }
    *randMediu=suma_rand*1.0/(nr_op-1);
}
void creeareLista(int n,node *head,FILE *input)
{
    double val;
    //creearea capului de lista
    fscanf(input,"%lf",&val);
    head->valoare=val;
    head->randament=0;
    head->next=NULL;

    //crearea listei +popularea acesteia (partiala)
    node* latest=(node*)malloc(sizeof(node));
    fscanf(input,"%lf",&val);
    latest->next=NULL;
    latest->valoare=val;
    head->next=latest;

    for(int i=3;i<=n;i++)
    {
        fscanf(input,"%lf",&val);
        node* p=(node*)malloc(sizeof(node));
        p->next=NULL; 
        p->valoare=val;
        latest->next=p;
        latest=p;
    }
}
void eliberareMemorie(node **head)
{
    node* temp=NULL;
    while((*head)!=NULL)
    {
        temp= (*head)->next;
        free(*head);
        *head=temp;
    }
    free(temp);
}