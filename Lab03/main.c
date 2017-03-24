#include <stdio.h  >
#include <stdbool.h>

void f02()
{
    printf("1. %g\n", 1e40 / 1e-40);
    printf("2. %g\n", 1e40f / 1e-40f);
    printf("3. %g\n", 1e40);
    printf("4. %f\n", 1e40);
    printf("5. %s\n", 1e3+1 == 1e3 ? "igaz" : "hamis");
    printf("6. %s\n", 1e30+1 == 1e30 ? "igaz" : "hamis");
}

void f03()
{
    printf( "%f", (double)( 4+2-(3-(6+((double)4/5)))) / ( 3*( 2-7 )) );
}

void f05()
{
    unsigned long int szam = 1;
    int hossz = 0;
    bool bOverflow = false;
    while( !bOverflow )
    {
        if( szam != 0 )
        {
            ++hossz;
            szam <<= 1;
        }
        else
        {
            bOverflow = true;
        }
    }

    printf( "%d\n", hossz );
}

void f06()
{
    unsigned long int szam = 29;
    unsigned long int mask = 1<<31;

    for( int i = 0; i<32; ++i, mask >>=1 )
    {
        if( (szam & mask) != 0 )
            printf( "#" );
        else
            printf( " " );
    }

    printf( "\n" );
}

void f07()
{
    unsigned long szamok[9] = { 0U, 1940142534U, 2216969513U, 2216969513U, 1681671631U, 337925385U, 3819190537U, 1024U, 0U };
    for( int i = 0; i < 9; ++i)
        szamok[i] = szamok[i] ^ ~65535;

    for( int j = 0; j < 9; ++j)
    {
        unsigned long int szam = szamok[j];
        unsigned long int mask = 1<<31;

        for( int i = 0; i<32; ++i, mask >>=1 )
        {
            if( (szam & mask) != 0 )
                printf( "#" );
            else
                printf( " ");
        }

        printf( "\n" );
    }
}

int main()
{
    unsigned long szamok[32] = { 131072U, 327680U, 557056U, 1064960U, 2105344U,
                                 4198400U, 8390656U, 16778240U, 33554944U, 67109120U,
                                 134217856U, 268435520U, 536870944U, 2147483632U,
                                 1431655760U, 715827872U, 1431655760U,
                                 2147483632U, 536870944U, 268435520U, 134217856U,
                                 67109120U, 33554944U, 16778240U, 8390656U, 4198400U,
                                 2105344U, 1064960U, 557056U, 327680U, 131072U, 0U };

    for( int j = 0; j < 32; ++j)
    {
        unsigned long int szam = szamok[j];
        unsigned long int mask = 1<<31;

        for( int i = 0; i<32; ++i, mask >>=1 )
        {
            if( (szam & mask) != 0 )
                printf( "#" );
            else
                printf( " ");
        }

        printf( "\n" );
    }

    return 0;
}
