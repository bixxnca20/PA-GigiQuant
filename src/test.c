#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "task1.h"
#include "functii.h"
#include "task2.h"

int main(int argc, const char *argv[])
{
    // deschiderea fisierelor
    FILE *input, *output;

    input = fopen(argv[1], "rb");
    output = fopen(argv[2], "wb");

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
        char city1[20], city2[20], city3[20];
        nodeS *share1 = NULL, *share2 = NULL, *share3 = NULL;

        creaareStiva(&share1, city1, input);
        creaareStiva(&share2, city2, input);
        creaareStiva(&share3, city3, input);

        deleteStack(&share1);
        deleteStack(&share2);
        deleteStack(&share3);

        fclose(input);
        fclose(output);
    }
    free(num);

    return 0;
}