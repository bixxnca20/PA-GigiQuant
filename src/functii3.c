#include "task3.h"
int nrLines(FILE *input)
{
    int nr = 0;
    char lit;
    while (lit = fgetc(input))
        if (lit == '\n')
            nr++;
    return nr;
}
nodeA *creeareListaCompanii(FILE *input) // poate sa fie void
{
    int count = 0, i = 0;
    char lit;
    nodeA *headc = NULL;
    nodeA *last = NULL;
    // popularea nodurilor cu numele companiior
    while (count < 10)
    {
        nodeA *company = (nodeA *)malloc(sizeof(nodeA));
        company->next = NULL;
        company->index = count;
        strcpy(company->name, "");

        do
        {
            lit = getc(input);
            company->name[i++] = lit;
        } while (lit != ',' && lit != '\n' && lit != '\r');

        company->name[i] = '\0';
        i = 0;

        // legarea listei
        if (count == 0)
            headc = company;
        else
        {
            last->next = company;
        }

        last = company;
        count++;
    }
    return headc;
}

root *creeareRoot()
{
    root *parent = (root *)malloc(sizeof(root));
    parent->left = NULL;
    parent->right = NULL;
    parent->nod = NULL;

    return parent;
}

nodeA *creeareNod(nodeA *node, double val)
{
    nodeA *stock = (nodeA *)malloc(sizeof(nodeA));
    stock->index = node->index;
    stock->valoare = val;
    strcpy(stock->name, node->name);
    stock->next = NULL;

    return stock;
}

void vectorStock(double price[], FILE *input, int *nr, int nrlines)
{
    for (int j = 0; j <= nrlines; j++)
    {
        for (int i = j * 10; i < (j + 1) * 10 - 1; i++)
        {
            fscanf(input, "%lf,", price + (*nr));
            (*nr)++;
        }
        fscanf(input, "%lf\n", price + (*nr));
        (*nr)++;
    }
}

void emptyLevel(root *root)
{
    while (root != NULL)
    {
        // daca este frunza
        if (root->left == NULL && root->right == NULL)
        {
            creeareRoot(root->left);
            creeareRoot(root->right);
        }

        emptyLevel(root->left);
        emptyLevel(root->right);
    }
}

void frunzeTree(root *root, double price[], int nr, nodeA **company, int *n)
{
    // nr = nr de zile
    //*n => pt indexarea vectorului de preturi
    // index => indexul din lista initiala
    nodeA *aux = root->nod;
    if ((*company) == NULL)
        return;

    int days = 1, index = (*company)->index;
    nodeA *p;

    // se creeaza nodul
    nodeA *nod = (nodeA *)malloc(sizeof(nodeA));
    nod = creeareNod(*company, price[*n + index]);

    while (days <= nr)
    {
        // nodul merge la dreapta
        if ((*company)->valoare < price[*n + index])
        {
            // daca s a ajuns la frunza si aceasta mai are noduri
            if (days == nr && root->right->nod != NULL)
                for (p = root->right->nod; p != NULL; p = p->next)
                    if (p->next == NULL)
                        p->next = nod;
                    // daca frunza nu are noduri
                    else
                        root->right->nod = nod;
            else if (days != nr)
            {
                root->right->nod = nod;
                free(root->nod);
                root = root->right;
            }
        }
        // nodul merge la stanga
        else
        {
            // daca s a ajuns la frunza si aceasta mai are noduri
            if (days == nr && root->left->nod != NULL)
                for (p = root->left->nod; p != NULL; p = p->next)
                    if (p->next == NULL)
                        p->next = nod;
                    // daca frunza nu are noduri
                    else
                        root->left->nod = nod;
            else if (days != nr)
            {
                root->left->nod = nod;
                free(root->nod);
                root = root->left;
            }
        }
        (*company)->valoare = price[*n + index];
        (*n) += 10;
        days++;
    }
    (*n) = 0;
    (*company) = (*company)->next;
    frunzeTree(root, price, nr, company, n);
}

// stocarea frunzelor intr un vector
void vectorFrunze(root *root, char frunze[][6], int *nr)
{

    if (root != NULL)
    {
        // este frunza
        if (root->left == NULL && root->right == NULL)
        {
            for (nodeA *p = root->nod; p != NULL; p = p->next)
            {
                strcpy(frunze[*nr], p->name);
                (*nr)++;
            }
        }
        vectorFrunze(root->left, frunze, nr);
        vectorFrunze(root->right, frunze, nr);
    }
}

void afisarePerechi(FILE *output, nodeA *headc, char frunze[][6], int nr)
{
    int i, j;
    char aux[6];
    for (i = 0, j = nr - 1; i < j; i++, j--)
    {
        for (nodeA *p = headc; p != NULL; p = p->next)
        {
            if (strcmp(frunze[i], p->name) == 0)
                break;

            // interschimbarea numelor astfel incat ca ele sa fie in ordine cronologica
            if (strcmp(frunze[j], p->name) == 0)
            {
                strcpy(aux, frunze[i]);
                strcpy(frunze[i], frunze[j]);
                strcpy(frunze[j], aux);
                break;
            }
        }
        fprintf(output, "%s-%s\n", frunze[i], frunze[j]);
    }
}
