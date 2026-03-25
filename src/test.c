#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct node{
    double valoare;
    double randament;
    struct node *next;
};
typedef struct node node;

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

int main(int argc, char *argv[])
{
    //de adaugat: exit() daca nu sunt suficiente argumente
    //deschiderea fisierelor
    FILE *input,*output;
    input=fopen(argv[1],"rb");
    output=fopen(argv[2],"wb");

    //initializarea variabilelor
    int nr_op;
    double s_r,randMediu,volatilitate;
    fscanf(input,"%d",&nr_op);
    node* head=(node*)malloc(sizeof(node));

    creeareLista(nr_op,head,input);
    //creare lista e bun
    adaugareRandament(nr_op,&head,&randMediu,input);

    //testare adaugare randament
    //for(node *pp=head;pp!=NULL;pp=pp->next)
      //  printf("val:%lf ran:%lf\n",pp->valoare,pp->randament);

    calculareVolatilitate(nr_op,head,randMediu,&volatilitate,input);
    s_r=randMediu*1.0/volatilitate;

    //afisarea rezultatelor
    fprintf(output,"%.3lf\n",((int)(randMediu*1000))*1.0/1000);
    fprintf(output,"%.3lf\n",((int)(volatilitate*1000))*1.0/1000);
    fprintf(output,"%.3lf\n",((int)(s_r*1000))*1.0/1000);


    //eliberarea momeriei alocata pentru lista
    /*node* previous=(node*)malloc(sizeof(node));
    node* p=(node*)malloc(sizeof(node));

    previous=head;
    for(p=head->next;p->next!=NULL;p=p->next)
        {
            free(previous);
            previous=p;
        }
    free(previous);
    free(p);
    */
    //inchiderea fisierelor
    fclose(input);
    fclose(output);
    return 0;
}