#include "task4.h"

int nrMuchii(graph *g, int nod)
{
    int nr = 0;
    for (int i = 0; i < g->v; i++)
    {
        nr += g->mat[nod][i];
    }

    return nr;
}

void cmmdc(int *numarator, int *numitor)
{
    int a = *numarator;
    if (a < 0)
        a = -a;
    int b = *numitor;
    if (b < 0)
        b = -b;

    while (b)
    {
        int r = a % b;
        a = b;
        b = r;
    }

    if (a != 0)
    {
        *numarator /= a;
        *numitor /= a;
    }
}

int creeareIntervaluri(int nrstari, float size, float start,const  float prices[], float *interval)
{
    int nr = 0;

    for (int i = 0; i < nrstari; i++)
    {
        // se afla marginea stanga a intervalului

        float capInterval = floor(prices[i] / size) * size;

        int ok = 0;
        for (int j = 0; j < nr; j++)
        {
            if (fabs(interval[j] - capInterval) < 0.0001)
            {
                ok = 1;
                break;
            }
        }

        if (ok == 0)
        {
            interval[nr] = capInterval;
            nr++;
        }
    }

    // se ordoneaza crescator intervalele
    for (int i = 0; i < nr - 1; i++)
    {
        for (int j = i + 1; j < nr; j++)
        {
            if (interval[i] > interval[j])
            {
                float aux = interval[i];
                interval[i] = interval[j];
                interval[j] = aux;
            }
        }
    }

    return nr;
}

graph *creareaGraf(int nrstari, float size, float start, const float prices[], const float interval[], int nrInterval)
{
    graph *g = (graph *)malloc(sizeof(graph));
    g->v = nrInterval;

    g->mat = (int **)calloc(g->v, sizeof(int *));
    for (int i = 0; i < g->v; i++)
        g->mat[i] = (int *)calloc(g->v, sizeof(int));

    for (int i = 0; i < nrstari - 1; i++)
    {

        float cap1 = floor(prices[i] / size) * size;
        float cap2 = floor(prices[i + 1] / size) * size;

        int ind1 = -1, ind2 = -1;
        for (int j = 0; j < nrInterval; j++)
        {
            if (fabs(interval[j] - cap1)<0.0001)
                ind1 = j;
            if (fabs(interval[j] - cap2)<0.0001)
                ind2 = j;
        }

        if (ind1 != -1 && ind2 != -1)
            g->mat[ind1][ind2]++;
        
    }

    return g;
}

void Stare(FILE *output, graph *g, float size, int days, float start, float target,const float interval[], int **stare)
{
    // se cauta pozitia lui start

    int indstart = -1;
    int indtarget = -1;

    float capstart=floor(start/size)*size;
    float captarget=floor(target/size)*size;

    for (int i = 0; i < g->v; i++)
    {
        if (fabs(interval[i] -capstart)<0.0001)
            indstart = i;
        if (fabs(interval[i] - captarget)<0.0001)
            indtarget = i;
    }

    // initiarea probabilitatilor
    for (int i = 0; i < g->v; i++)
    {
        stare[0][i] = 0; /// 0 pt numarator
        stare[1][i] = 1; // 1 pt numitor
    }

    if (indstart != -1)
    {
        stare[0][indstart] = 1;
        stare[1][indstart] = 1;
    }

    // vectori auxiliari pentru ziua urmatoare
    int *nextNumarator = (int *)calloc(g->v, sizeof(int));
    int *nextNumitor = (int*)calloc(g->v, sizeof(int));

    // afisare ziua 0
    if (stare[0][indtarget] == 0)
        fprintf(output, "0\n");
    else if (stare[0][indtarget] == stare[1][indtarget])
        fprintf(output, "1\n");

    for (int currentday = 0; currentday < days - 1; currentday++)
    {
        for (int i = 0; i < g->v; i++)
        {
            nextNumarator[i] = 0;
            nextNumitor[i] = 1;
        }

        for (int i = 0; i < g->v; i++)
        {
            if (stare[0][i] > 0)
            {
                int total_muchii = nrMuchii(g, i);
                if (total_muchii == 0)
                    continue;

                for (int j = 0; j < g->v; j++)
                {
                    if (g->mat[i][j] > 0)
                    {
                        // calculul probabilitatii
                        int pNumarator = stare[0][i] * g->mat[i][j];
                        int pNumitor = stare[1][i] * total_muchii;

                        // se adauga probabilitatea calculata la nod
                        if (nextNumarator[j] == 0)
                        {
                            nextNumarator[j] = pNumarator;
                            nextNumitor[j] = pNumitor;
                        }
                        else
                        {
                            int numitor_comun = nextNumitor[j] * pNumitor;
                            int numarator_nou = nextNumarator[j] * pNumitor + pNumarator * nextNumitor[j];
                            nextNumarator[j] = numarator_nou;
                            nextNumitor[j] = numitor_comun;
                        }
                        cmmdc(&nextNumarator[j], &nextNumitor[j]);
                    }
                }
            }
        }

        // se copiaza probabilitatile pt a trece la ziua urmatoare
        for (int i = 0; i < g->v; i++)
        {
            stare[0][i] = nextNumarator[i];
            stare[1][i] = nextNumitor[i];
        }

        // afisarea probabilitatii lui target

        if (indtarget == -1 || stare[0][indtarget] == 0)
            fprintf(output, "0\n");

        else if (stare[0][indtarget] == stare[1][indtarget])
            fprintf(output, "1\n");

        else
            fprintf(output, "%d/%d\n", stare[0][indtarget], stare[1][indtarget]);
    }

    free(nextNumarator);
    free(nextNumitor);
}