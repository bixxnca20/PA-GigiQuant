#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "task1.h"

int main(int argc, const char *argv[])
{
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
    calculareVolatilitate(nr_op,head,randMediu,&volatilitate,input);
    s_r=randMediu*1.0/volatilitate;

    //afisarea rezultatelor
    fprintf(output,"%.3lf\n",((int)(randMediu*1000))*1.0/1000);
    fprintf(output,"%.3lf\n",((int)(volatilitate*1000))*1.0/1000);
    fprintf(output,"%.3lf\n",((int)(s_r*1000))*1.0/1000);

    //eliberarea memoriei
    eliberareMemorie(&head);
    ///task 2




    //inchiderea fisierelor
    fclose(input);
    fclose(output);



    return 0;
}