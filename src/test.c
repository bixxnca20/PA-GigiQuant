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
    node* p=(node*)malloc(sizeof(node));
    for(p=head;p!=NULL;p=p->next)
        *volatilitate+= (p->randament-randMediu)*(p->randament-randMediu);
    *volatilitate=sqrt((*volatilitate) /nr_op);
    free(p);
}
void adaugareRandament(int nr_op, node *head,double *randMediu,FILE *input)
{
    double suma_rand=0;
    double val_ant=head->valoare;

    node* p=(node*)malloc(sizeof(node));

    //se calculeaza randamentul pentru fiecare nod
    for(p=head->next;p!=NULL;p=p->next)
    {
        p->randament=(p->valoare + val_ant) / val_ant;
        suma_rand+=p->randament;
        val_ant=p->valoare;
    }
    *randMediu=suma_rand/nr_op;
    free(p);
}
void creeareLista(int n,node *head,FILE *input)
{
    int val;
    //creearea capului de lista
    fscanf(input,"%d",&val);
    head->valoare=val;
    head->randament=0;
    head->next=NULL;

    //crearea listei +popularea acesteia (partiala)
    node* latest=(node*)malloc(sizeof(node));
    fscanf(input,"%d",&val);
    head->next=latest;
    latest->next=NULL;
    latest->valoare=val;

    for(int i=3;i<=n;i++)
    {
        fscanf(input,"%d",&val);
        node* p=(node*)malloc(sizeof(node));
        p->next=NULL; 
        p->valoare=val;
        latest->next=p;
        latest=p;
    }
}

int main(int argc, char *argv[])
{
    //deschiderea fisierelor
    FILE *input,*output;
    input=fopen(argv[1],"rb");
    output=fopen(argv[2],"wb");

    //initializarea variabilelor
    int nr_op;
    double s_r,randMediu,volatilitate=0;
    fscanf(input,"%d",&nr_op);
    node* head=(node*)malloc(sizeof(node));

    creeareLista(nr_op,head,input);


    //testarea primei functii - debugging
    node* test=(node*)malloc(sizeof(node));
    for(test=head;test!=NULL;test=test->next)
        printf("%lf %lf\n",test->randament,test->valoare);
    printf("\ndoamne ajuta");

    //continuare

    adaugareRandament(nr_op,head,&randMediu,input);
    calculareVolatilitate(nr_op,head,randMediu,&volatilitate,input);
    s_r=randMediu/volatilitate;

    //afisarea rezultatelor
    fprintf(output,"%lf %lf %lf",randMediu,volatilitate,s_r);

    //eliberarea momeriei alocata pentru lista
    node* previous=(node*)malloc(sizeof(node));
    node* p=(node*)malloc(sizeof(node));

    previous=head;
    for(p=head->next;p->next!=NULL;p=p->next)
        {
            free(previous);
            previous=p;
        }
    free(previous);
    free(p);

    //inchiderea fisierelor
    fclose(input);
    fclose(output);
    return 0;
}