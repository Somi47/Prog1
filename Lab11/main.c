#include <stdio.h>
#include <stdlib.h>

typedef struct fa {
    int ertek;
    struct fa *bal, *jobb;
} BiFa;

BiFa *beszur(BiFa *gyoker, int ertek) {
    if (gyoker == NULL) {
        BiFa *uj = (BiFa*) malloc(sizeof(BiFa));
        uj->ertek = ertek;
        uj->bal = uj->jobb = NULL;
        return uj;
    }
    if (ertek < gyoker->ertek) {        /* balra szur */
        gyoker->bal = beszur(gyoker->bal, ertek);
    }
    else if (ertek > gyoker->ertek) {   /* jobbra szur */
        gyoker->jobb = beszur(gyoker->jobb, ertek);
    }
    else {
        /* mar benne van */
    }
    return gyoker;
}

void f3kiir( BiFa *gyoker )
{
    if( gyoker == NULL )
        return;

    f3kiir( gyoker->bal );
    printf( "%d, ", gyoker->ertek );
    f3kiir( gyoker->jobb );
}

void f3destruct( BiFa *gyoker )
{
    if( gyoker == NULL )
        return;

    f3destruct( gyoker->bal );
    f3destruct( gyoker->jobb );
    free( gyoker );
}

int f4count( BiFa *gyoker )
{
    if( gyoker == NULL )
        return 0;

    return f4count( gyoker->bal ) + f4count( gyoker->jobb ) + 1;
}

int f4value( BiFa *gyoker )
{
    if( gyoker == NULL )
        return 0;

    return f4value( gyoker->bal ) + f4value( gyoker->jobb ) + gyoker->ertek;
}

BiFa *f5find( BiFa *gyoker, int iValue )
{
    if( gyoker == NULL )
        return NULL;

    if( gyoker->ertek == iValue )
        return gyoker;

    if( gyoker->ertek > iValue )
        return f5find( gyoker->bal, iValue );

    return f5find( gyoker->jobb, iValue );
}

void findUnitTest( BiFa *gyoker, int iValue )
{
    printf( "Find %3d: ", iValue );
    BiFa *foundnode = f5find( gyoker, iValue );
    if( foundnode == NULL )
        printf( "Not found\n" );
    else
        printf( "Found - pointer: %p, value: %3d\n", foundnode, foundnode->ertek );
}

void f6negal( BiFa *gyoker )
{
    if( gyoker == NULL )
        return;

    f6negal( gyoker->bal );
    gyoker->ertek = -gyoker->ertek;
    f6negal( gyoker->jobb );
}

BiFa *f6negfind( BiFa *gyoker, int iValue )
{
    if( gyoker == NULL )
        return NULL;

    if( gyoker->ertek == iValue )
        return gyoker;

    if( gyoker->ertek < iValue )
        return f6negfind( gyoker->bal, iValue );

    return f6negfind( gyoker->jobb, iValue );
}

void negfindUnitTest( BiFa *gyoker, int iValue )
{
    printf( "Find %3d: ", iValue );
    BiFa *foundnode = f6negfind( gyoker, iValue );
    if( foundnode == NULL )
        printf( "Not found\n" );
    else
        printf( "Found - pointer: %p, value: %3d\n", foundnode, foundnode->ertek );
}

void f7mirror( BiFa *gyoker )
{
    if( gyoker == NULL )
        return;

    f7mirror( gyoker->bal );
    f7mirror( gyoker->jobb );

    BiFa *tmp    = gyoker->bal;
    gyoker->bal  = gyoker->jobb;
    gyoker->jobb = tmp;
}

int main(void) {
    int minta[] = {15, 96, 34, 12, 14, 56, 21, 11, 10, 9, 78, 43, 0};
    BiFa *gyoker = NULL;
    int i;
    for (i = 0; minta[i] > 0; i++)
        gyoker = beszur(gyoker, minta[i]);

    /* Ide tedd be a kipróbálandó függvények hívásait! */
    f3kiir( gyoker );
    printf( "\n" );
    printf( "Count: %d\n", f4count( gyoker ) );
    printf( "Value: %d\n", f4value( gyoker ) );

    findUnitTest( gyoker, 78 );
    findUnitTest( gyoker,  9 );
    findUnitTest( gyoker, 14 );
    findUnitTest( gyoker, 50 ); // shouldnt be found

    printf( "\nNeg:" );
    f6negal( gyoker );
    f3kiir( gyoker );
    printf( "\n" );
    negfindUnitTest( gyoker, -78 );
    negfindUnitTest( gyoker, - 9 );
    negfindUnitTest( gyoker, -14 );
    negfindUnitTest( gyoker, -50 ); // shouldnt be found

    printf( "\nInv:" );
    f7mirror( gyoker );
    f3kiir( gyoker );
    printf( "\n" );
    findUnitTest( gyoker, -78 );
    findUnitTest( gyoker, - 9 );
    findUnitTest( gyoker, -14 );
    findUnitTest( gyoker, -50 ); // shouldnt be found


    f3destruct( gyoker );
    return 0;
}
