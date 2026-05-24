#include "task3.h"
int nrLines(FILE *input)
{
    int nr = 0;
    char lit;
    while (fscanf(input, "%c", &lit) == 1)
    {
        if (lit == '\n')
        {
            nr++;
        }
    }
    return (nr - 1);
}
void creeareListaCompanii(FILE *input, nodeA *headc) // poate sa fie void
{
    int count = 0, i = 0;
    char lit;
    nodeA *p = headc;
    // popularea nodurilor cu numele companiior
    while (fscanf(input, "%c", &lit) == 1 && lit != '\n')
    {
        if (lit == '\r')
            continue;
        if (lit != ',')
        {
            p->name[i] = lit;
            i++;
        }
        else
        {
            p->name[i] = '\0';
            i = 0;
            count++;

            nodeA *node = (nodeA *)malloc(sizeof(nodeA));
            node->next = NULL;
            node->index = count;
            node->valoare = 0;

            p->next = node;
            p = node;
        }
    }
    p->name[i] = '\0';
}

nodeA *creeareNod(const nodeA *node, double val)
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
    int i, j;
    for (j = 0; j <= nrlines; j++)
    {
        for (i = j * 10; i < (j + 1) * 10 - 1; i++)
        {
            fscanf(input, "%lf,", &price[i]);
            (*nr)++;
        }
        fscanf(input, "%lf\n", &price[i]);
        (*nr)++;
    }
}

void frunzeTree(ROOT *root, double price[], int nr, nodeA **company, int *n)
{
    // nr = nr de zile
    //*n => pt indexarea vectorului de preturi
    // index => indexul din lista initiala
    // nodeA *aux = root->nod;

    if ((*company) == NULL)
        return;

    int days = 1, index = (*company)->index;
    ROOT *current = root;
    nodeA *p;

    // se creeaza nodul
    nodeA *nod = creeareNod(*company, price[*n + index]);

    while (days < nr)
    {
        // daca este nod intern
        if (days < nr - 1)
            if ((*company)->valoare < price[*n + index])
            {
                if (current->right == NULL)
                    current->right = (ROOT *)malloc(sizeof(ROOT));
                current = current->right;
            }
            else
            {
                if (current->left == NULL)
                    current->left = (ROOT *)malloc(sizeof(ROOT));
                current = current->left;
            }
        else
        { // s a ajuns la frunza
            if ((*company)->valoare < price[*n + index])
            {
                if (current->right == NULL)
                {
                    current->right = (ROOT *)malloc(sizeof(ROOT));
                    current->right->left = NULL;
                    current->right->right = NULL;
                    current->right->nod = NULL;
                }
                if (current->right->nod == NULL)
                    current->right->nod = nod;
                else
                {
                    for (p = current->right->nod; p->next != NULL; p = p->next)
                        ;
                    p->next = nod;
                }
            }
            else
            {
                // s a ajuns la frunza
                if (current->left == NULL)
                {
                    current->left = (ROOT *)malloc(sizeof(ROOT));
                    current->left->left = NULL;
                    current->left->right = NULL;
                    current->left->nod = NULL;
                }
                if (current->left->nod == NULL)
                    current->left->nod = nod;
                else
                {
                    for (p = current->left->nod; p->next != NULL; p = p->next)
                        ;
                    p->next = nod;
                }
            }
        }
        (*company)->valoare = price[*n + index];
        (*n) += 10;
        days++;
    }
    (*n) = 10;
    (*company) = (*company)->next;
    frunzeTree(root, price, nr, company, n);
}/*
void frunze(ROOT *root, char matfrunze[][5], int *index)
{
    if (root == NULL)
        return;
    frunze(root->left, matfrunze, index);
    int i = 0;
    if (root->left == NULL && root->right == NULL)
    {
        for (nodeA *p = root->nod; p != NULL; p = p->next)
        {
            strcpy(matfrunze[*index], p->name);
            i++;
        }
        // strncat(matfrunze[*index]," ",1);
        (*index)++;
    }
    frunze(root->right, matfrunze, index);
}*/

void perechiCompanii(FILE *output, ROOT *left, ROOT *right)
{ // left face preorder
  // right face postorder

    if (left == NULL || right == NULL)
        return;
    // ambele sunt frunze
    if (left->right == NULL && left->left == NULL && right->right == NULL && right->left == NULL)
    {
        for (nodeA *p = left->nod; p != NULL; p = p->next)
            for (nodeA *q = right->nod; q != NULL; q = q->next)
                if (p->index > q->index)
                    fprintf(output, "%s-%s\n", q->name, p->name);
                else
                    fprintf(output, "%s-%s\n", p->name, q->name);

        return;
    }
    // numai left este frunza
    else if (left->nod != NULL && left->left == NULL && left->right == NULL)
    {
        perechiCompanii(output, left, right->right);
        perechiCompanii(output, left, right->left);
        return;
    }
    // numai right este frunza
    else if (right->nod != NULL && right->left == NULL && right->right == NULL)
    {
        perechiCompanii(output, left->left, right);
        perechiCompanii(output, left->right, right);
        return;
    }
    perechiCompanii(output, left->left, right->right);
    perechiCompanii(output, left->right, right->left);
}

void colectareFrunze(ROOT *root, nodeA **cosfrunze, int *indexcolectare)
{
    if (root == NULL)
        return;

    // este frunza
    if (root->left == NULL && root->right == NULL)
    {
        cosfrunze[*indexcolectare] = root->nod;
        (*indexcolectare)++;
        return;
    }

    // parcurgere in-order
    colectareFrunze(root->left, cosfrunze, indexcolectare);
    colectareFrunze(root->right, cosfrunze, indexcolectare);
}
/*
void afisareFrunze(FILE *output, nodeA **cosfrunze, int index)
{
    /*for (int i = 0,j=index-1; i < j; i++,j--)
        {
            if (cosfrunze[i] == NULL)
                i++;
            if (cosfrunze[j] == NULL)
                j--;
            for (nodeA *p = cosfrunze[i]; p != NULL; p = p->next)
                for (nodeA *q = cosfrunze[j]; q != NULL; q = q->next)
                    fprintf(output, "%s-%s\n", p->name, q->name);
        }*/
    // se creaza o matrice pentru a nu afisa aceeasi pereche de mai multe ori
   /* int check[11][11];
    int nline = 1;
    for (int i = 0; i < 10; i++)
        for (int j = 0; j < 10; j++)
            check[i][j] = 0;

    for (int i = 0; i < index; i++)
    {
        int j = index - i-1;
        if (cosfrunze[i] == NULL || cosfrunze[j] == NULL)
            continue;
        if (i >= j)
            break;
        for (nodeA *p = cosfrunze[i]; p != NULL; p = p->next)
            for (nodeA *q = cosfrunze[j]; q != NULL; q = q->next)
            {
                int pind = p->index;
                int qind = q->index;
                if (pind != qind && check[pind][qind] == 0)
                {
                    {
                        check[pind][qind] = 1;
                        check[qind][pind] = 1;
                    }
                    if (nline == 1) // este prima pereche
                    {
                        fprintf(output, "%s-%s", p->name, q->name);
                        nline = 0;
                    }
                    else
                        fprintf(output, "\n%s-%s", p->name, q->name);
                }
            }
    }
}*/

void freeTree(ROOT *root)
{
    if (root == NULL)
        return;
    freeTree(root->right);
    freeTree(root->left);
    nodeA *temp = NULL;
    while (root->nod != NULL)
    {
        temp = root->nod;
        root->nod = root->nod->next;
        free(temp);
    }
    free(root);
}

void freeList(nodeA *head)
{
    nodeA *temp = NULL;
    while (head != NULL)
    {
        temp = head;
        head = head->next;
        free(temp);
    }
}
