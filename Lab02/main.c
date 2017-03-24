#include <stdio.h>
#include <math.h>

#define PI 3.14159

int main()
{
//double dXP, dYP, dXQ, dYQ;
//scanf( "%lf %lf %lf %lf", &dXP, &dYP, &dXQ, &dYQ );
//printf( "Hossz: %.2f", sqrt( pow( dXP - dXQ, 2 ) + pow( dYP - dYQ, 2 ) ) );

//    double a, b, c;
//    scanf( "%lf %lf %lf", &a, &b, &c );
//    if( a == 0 )
//        printf( "Nem masodfoku" );
//
//    double d = pow( b, 2 ) - ( 4 * a * c );
//    if( d < 0 )
//    {
//        printf( "Nincs megoldas" );
//    }
//    else if( d == 0 )
//    {
//        printf( "X: %.2lf", (- b)/(2*a) );
//    }
//    else
//    {
//        printf( "X1: %.2lf ", (- b + sqrt( d ) )/(2*a) );
//        printf( "X2: %.2lf" , (- b - sqrt( d ) )/(2*a) );
//    }

//    for( int i = 1; i <= 20; ++i )
//    {
//        printf( "%d\n", i );
//    }

    int n, m;
    scanf( "%d %d", &n, &m );

    printf( "+" );
    for(int i = 0; i<n; ++i )
    {
        printf( "-" );
    }
    printf( "+\n" );

    for( int j = 0; j<m; ++j )
    {
        printf( "|" );
        for(int i = 0; i<n; ++i )
        {
            printf( "." );
        }
        printf( "|\n" );
    }

    printf( "+" );
    for(int i = 0; i<n; ++i )
    {
        printf( "-" );
    }
    printf( "+\n" );

    printf( "\n\n" );

    for( int i = 0; i<16; ++i )
    {
        for( int j = 0; j<16; ++j )
        {
            if( (j/2) % 2 == (i/2) % 2 )
                printf( "X" );
            else
                printf( " " );
        }
        printf( "\n" );
    }

    printf( "\n\n" );

    for( int i = 0; i < 20; ++i )
    {
        int xpos = (int) ( sin( 2 * i * PI / 20 ) * 10 );
        for( int j = 0; j < 20; ++j )
        {
            if( j == xpos + 10 )
                printf( "X" );
            else
                printf( " " );
        }
        printf( "\n" );
    }

    return 0;
}
