#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "task1.h"
#include "functii.h"
#include "task2.h"
#include "task3.h"

int main(int argc, const char *argv[])
{
    // deschiderea fisierelor
    FILE *input, *output;

    input = fopen(argv[1], "rb");
    output = fopen(argv[2], "wb");

    // pentru a afla numarul fisierului de input
    char *num = (char *)malloc(sizeof(argv[1]) + 1);
    strcpy(num, argv[1]);

    if (selectare(num) == 1)
    {
        // task 1
        //  initializarea variabilelor
        int nr_op;
        double s_r, randMediu, volatilitate;
        fscanf(input, "%d", &nr_op);
        node *head = (node *)malloc(sizeof(node));

        creeareLista(nr_op, head, input);
        // creare lista e bun
        adaugareRandament(nr_op, &head, &randMediu, input);
        calculareVolatilitate(nr_op, head, randMediu, &volatilitate, input);
        s_r = randMediu * 1.0 / volatilitate;

        // afisarea rezultatelor
        fprintf(output, "%.3lf\n", ((int)(randMediu * 1000)) * 1.0 / 1000);
        fprintf(output, "%.3lf\n", ((int)(volatilitate * 1000)) * 1.0 / 1000);
        fprintf(output, "%.3lf\n", ((int)(s_r * 1000)) * 1.0 / 1000);

        // eliberarea memoriei
        eliberareMemorie(&head);
        /// task 2

        // inchiderea fisierelor
        /*fclose(input);
        fclose(output);*/
    }
    if (selectare(num) == 2)
    {
        // task 2
        // declararea variabilelor
        char city1[20], city2[20], city3[20];
        nodeS *share1 = NULL, *share2 = NULL, *share3 = NULL;

        creaareStiva(&share1, city1, input);
        creaareStiva(&share2, city2, input);
        creaareStiva(&share3, city3, input);

        Queue *q = createQ();
        creeareCoada(&share1, &share2, &share3, q, city1, city2, city3);
        afisareCoada(q, output);

        // eliberarea memoriei
        deleteStack(&share1);
        deleteStack(&share2);
        deleteStack(&share3);
        deleteQueue(q);

        // inchiderea fisierelor
        /*fclose(input);
        fclose(output);*/
    }
    if (selectare(num) == 3)
    {
        // task 3

        // functie pt a afla cate zile sunt
        int nrlines = nrLines(input);
        
        fclose(input);
        input = fopen(argv[1], "rb");

        // se creeaza o lista cu toate companiile
        nodeA *company = creeareListaCompanii(input);

         //se populeaza vectorul care retine toate preturile
        double *price=malloc(sizeof(double)*nrlines*10 + 1);
        int nr = 0, index = 0;
        vectorStock(price, input, &nr, nrlines);

        // se creaza root-ul arborelui si ii se atribuie lista cu toate companiile
        root *parent;
        parent = creeareRoot();
        parent->nod = company;

        //se adauga atatea niveluri goale cate zile sunt
        for(int i=0;i<nrlines;i++)
            emptyLevel(parent);
        
        //se muta fiecare companie,pe rand, la frunza ei
        int n=0,listindex=0;
        frunzeTree(parent,price,nr,&company,&n);

        //se stocheaza toate frunzele in ordine de la stanga la dreapta
        char frunze[11][6];
        int nrf = 0;
        vectorFrunze(parent, frunze, &nrf);
        
        //se afiseaza perechile cerute
        afisarePerechi(output, company, frunze, nrf);
        
        // trebuie eliberata memoria
        free(price);

        //se inchid fisierele
        fclose(input);
        fclose(output);
    }
    // eliberarea variabilei cu care am aflat nr fisierului de input
    free(num);
    return 0;
}