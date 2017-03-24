#include <stdio.h>
#include <stdlib.h>

typedef struct ListaElem {
    int adat;
    struct ListaElem *kov;
} ListaElem;


/* létrehoz egy listát, benne egy csomó számmal */
ListaElem *lista_letrehoz(void) {
    int szamok[] = { 8, 14, 13, 17, 1, 19, 16, 5, 3, 11, 2,
                     15, 9, 10, 6, 22, 4, 7, 18, 20, -1 };
    ListaElem *l = NULL;

    int i;
    for (i = 0; szamok[i] != -1; ++i) {
        ListaElem *u;
        u = (ListaElem*) malloc(sizeof(ListaElem));
        u->kov = l;
        u->adat = szamok[i];
        l = u;
    }
    return l;
}

 void f2( ListaElem *pFirst )
 {
     for( ListaElem *pIterator = pFirst; pIterator != NULL; pIterator = pIterator->kov )
        printf( "%d ", pIterator->adat );

     printf( "\n" );
}

int f3_length( ListaElem *pFirst )
{
    int count = 0;
    for( ListaElem *pIterator = pFirst; pIterator != NULL; pIterator = pIterator->kov )
        ++count;

    return count;
}

void f4_free( ListaElem *pFirst )
{
    ListaElem *pIterator = pFirst;
    while( pIterator != NULL )
    {
        ListaElem *pTmp = pIterator;
        pIterator = pIterator->kov;
        free( pTmp );
    }
}

ListaElem *f5_InsertFirst( ListaElem *pFirst, int iData )
{
    ListaElem *pNew = (ListaElem*) malloc(sizeof(ListaElem));
    pNew->adat = iData;
    pNew->kov  = pFirst;

    return pNew;
}

void f6_InsertLast( ListaElem *pFirst, int iData )
{
    ListaElem *pIterator;
    for( pIterator = pFirst; pIterator->kov != NULL; pIterator = pIterator->kov )
        /*NOTHING*/;

    ListaElem *pNew = (ListaElem*) malloc(sizeof(ListaElem));
    pNew->adat = iData;
    pNew->kov  = NULL;

    pIterator->kov = pNew;
}

ListaElem *f7_Find( ListaElem *pFirst, int iData )
{
    for( ListaElem *pIterator = pFirst; pIterator != NULL; pIterator = pIterator->kov )
    {
        if( pIterator->adat == iData )
            return pIterator;
    }

    return NULL;
}

int main(void)
{
    ListaElem *lis;

    lis = lista_letrehoz();

    lis = f5_InsertFirst( lis, 33 );
    f6_InsertLast( lis, 42 );
    f2( lis );
    printf( "%d\n", f3_length( lis ) );

    printf( "%p\n", f7_Find( lis,   3 ) );
    printf( "%p\n", f7_Find( lis, 112 ) );

    f4_free( lis );

    return 0;
}
