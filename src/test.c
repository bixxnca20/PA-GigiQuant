#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "task3.h"
#include "task1.h"
#include "task2.h"
#include "functii.h"
#include "task4.h"

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
        nodeA *company = (nodeA *)malloc(sizeof(nodeA));
        creeareListaCompanii(input, company);

        // se populeaza vectorul care retine toate preturile
        double price[51];
        int nr = 0;
        vectorStock(price, input, &nr, nrlines);

        // se adauga in lista preturile din prima zi
        for (nodeA *p = company; p != NULL; p = p->next)
            p->valoare = price[p->index];

        // se creaza root-ul arborelui si ii se atribuie lista cu toate companiile
        ROOT *parent = (ROOT *)malloc(sizeof(ROOT));
        parent->nod = company;
        parent->right = NULL;
        parent->left = NULL;

        // se muta fiecare companie,pe rand, la frunza ei
        int n = 10;
        frunzeTree(parent, price, nrlines, &company, &n);
        
        //se realizeaza afisarea
        //int index=0;
        nodeA **cosfrunze=(nodeA**)malloc(10*sizeof(nodeA*));
        for(int i=0;i<10;i++)
            cosfrunze[i]=NULL;
        //colectareFrunze(parent,cosfrunze,&index);

        //afisareFrunze(output,cosfrunze,index);

        // se elibereaza memoria
        freeTree(parent);
        freeList(company);
        free(cosfrunze);

        // se inchid fisierele
        /*
        fclose(input);
        fclose(output);*/
    }
    if (selectare(num) == 4)
    {
        //task 4
        int nrstari, days;
        float size, start, target;

        //se citesc valorile
        fscanf(input, "%d", &nrstari);
        fscanf(input, "%f", &size);
        fscanf(input, "%d", &days);
        fscanf(input, "%f", &start);
        fscanf(input, "%f", &target);

        //se stocheaza preturile intr un vector
        float *prices = malloc(nrstari * sizeof(float));
        for (int i = 0; i < nrstari; i++)
        {
            float readv;
            fscanf(input, "%f", &readv);
            prices[i] = readv;
        }

        //se creeaza un vector pentru intervalele nodurilor
        float *interval = calloc(nrstari, sizeof(float));
        int nrInterval = creeareIntervaluri(nrstari, size, start, prices, interval);

        //creearea grafului si a matricei sale de adiacenta
        graph *g = creareaGraf(nrstari, size, start, prices, interval, nrInterval);

        // se creeaza matricea de probabilitati
        int **stare = malloc(2 * sizeof(int *));
        stare[0] = calloc(g->v, sizeof(int)); 
        stare[1] = calloc(g->v, sizeof(int)); 

        // simularea proriu-zisa
        Stare(output, g, size, days, start, target, interval, stare);

        //se elibereaza memoria
        free(prices);
        free(interval);
        for (int i = 0; i < g->v; i++)
            free(g->mat[i]);
        free(g->mat);
        free(g);
        free(stare[0]);
        free(stare[1]);
        free(stare);

        //se inchid fisierele
        fclose(input);
        fclose(output);
    }

    // eliberarea variabilei cu care am aflat nr fisierului de input
    free(num);
    return 0;
}