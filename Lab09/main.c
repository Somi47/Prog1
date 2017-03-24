#include <stdio.h>
#include <stdlib.h>

void f1()
{
    int n;
    scanf( "%d", &n );
    double *arr = (double *)malloc( n * sizeof(double) );

    for( int i = 0; i < n; ++i )
        scanf( "%lf", arr + i );

    for( int i = n - 1; i >= 0; --i )
        printf( "%f\n", arr[i] );

    free( arr );
}

void f2()
{
    int n = 0;
    double *arr = NULL;

    double szam;
    while( scanf( "%lf", &szam ) != EOF )
    {
        ++n;
        arr = (double *)realloc( arr, n * sizeof(double) );
        arr[n-1] = szam;
    }

    for( int i = n - 1; i >= 0; --i )
        printf( "%f\n", arr[i] );

    free( arr );
}

void f3()
{
    int n = 0;
    char *arr = NULL;

    char betu;
    while( scanf( "%c", &betu ) != EOF )
    {
        if( betu == '\0' )
            break;

        ++n;
        arr = (char *)realloc( arr, n * sizeof(char) );
        arr[n-1] = betu;
    }

    arr = (char *)realloc( arr, (n +  1) * sizeof(char) );
    arr[n] = '\0';

    printf( arr );
    free( arr );
}

char *dynamic_scan_str()
{
    int n = 0;
    char *arr = NULL;

    char betu;
    while( scanf( "%c", &betu ) != EOF )
    {
        if( betu == '\0' )
            break;

        ++n;
        arr = (char *)realloc( arr, n * sizeof(char) );
        arr[n-1] = betu;
    }

    arr = (char *)realloc( arr, (n +  1) * sizeof(char) );
    arr[n] = '\0';

    return arr;
}

void f4()
{
    char *str = dynamic_scan_str();
    printf( str );
}

int main()
{
    //f1();
    //f2();
    //f3();
    f4();

    return 0;
}
