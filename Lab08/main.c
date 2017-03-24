#include <stdio.h>

int Fib( int n )
{
    if( n < 2 )
        return n;

    return Fib( n - 1 ) + Fib( n - 2 );
}

void f1()
{
    printf("%d\n", Fib( 40 ));
}

void f2ax( int *x, int n )
{
    for( int i=0; i<n; ++i )
        printf( "%d, ", x[i] );
}

void f2ay( int *y, int n )
{
    for( int i=n-1; i>=0; --i )
        printf( "%d, ", y[i] );
}

void f2bx( int *x, int *vege )
{
    printf( "%d, ", *x );

    if( x != vege )
        f2bx( x + 1, vege );
}

void f2by( int *y, int *vege )
{
    if( y != vege )
        f2by( y + 1, vege );

    printf( "%d, ", *y );
}

void f2()
{
    int x[] = { 2, 4, 3, 5 };
    int y[] = { 4, 6, 8, 7 };
    int n = 4;
    f2ax( x, n );
    printf( "\n" );
    f2ay( y, n );
    printf( "\n" );
    f2bx( x, x + n - 1 );
    printf( "\n" );
    f2by( y, y + n - 1 );
}

int hatvany( int alap, int kitevo )
{
    if( kitevo == 0 )
        return 1;

    if( kitevo == 1 )
        return alap;


    if( kitevo % 2 == 0 )
        return hatvany( alap * alap, kitevo / 2 );
    else
        return alap * hatvany( alap, kitevo - 1  );
}

void f3()
{
    printf( "%d", hatvany( 3, 4 ) );
}

void valto( int n, int szr )
{
    if( n == 0 )
        return;

    valto( n / szr, szr );

    printf( "%d", n % szr );
}

void f4()
{
    valto( 10, 3 );
}

void hanyasavalkiir( int n, int hanyasaval )
{
    if( n == 0 )
        return;

    int mod = hatvany( 10, hanyasaval );
    hanyasavalkiir( n / mod, hanyasaval );

    printf( "%d ", n % mod );
}

void f5()
{
    hanyasavalkiir( 3621872, 3 );
}

int main()
{
    //f1();
    //f2();
    //f3();
    //f4();
    f5();

    return 0;
}
