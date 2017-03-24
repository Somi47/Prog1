#include <stdio.h>
#include <math.h>

#define SIZE 400.0
#define PI 3.141592

int main()
{
    int h, m, s;
    scanf( "%d %d %d", &h, &m, &s );
    h = h % 12;
    m = m % 60;
    s = s % 60;

    printf( "<svg width=\"%.0f\" height=\"%.0f\" xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\">\n", SIZE, SIZE );

    printf( "\t<circle cx=\"%.0f\" cy=\"%.0f\" r=\"%.0f\" stroke=\"black\" fill=\"orange\" />\n", SIZE / 2, SIZE / 2, SIZE / 2 );
    int i;
    for( i = 0; i < 60; ++i )
    {
        double deg = i * PI / 30;
        double x1 = SIZE / 2 + cos( deg ) * SIZE / 2 * ( i % 15 == 0 ? 0.8 : ( i % 5 == 0 ? 0.85 : 0.95 ) );
        double y1 = SIZE / 2 + sin( deg ) * SIZE / 2 * ( i % 15 == 0 ? 0.8 : ( i % 5 == 0 ? 0.85 : 0.95 ) );
        double x2 = SIZE / 2 + cos( deg ) * SIZE / 2;
        double y2 = SIZE / 2 + sin( deg ) * SIZE / 2;
        printf( "\t<line x1=\"%.0f\" y1=\"%.0f\" x2=\"%.0f\" y2=\"%.0f\" stroke=\"black\" />\n", x1, y1, x2, y2 );
    }

    double hdeg = ( h + m / 60.0 + s / 3600.0 ) * PI / 6 - PI / 2;
    double hx1 = SIZE / 2 + cos( hdeg ) * SIZE / 2 * 0.5;
    double hy1 = SIZE / 2 + sin( hdeg ) * SIZE / 2 * 0.5;
    printf( "\t<line x1=\"%.0f\" y1=\"%.0f\" x2=\"%.0f\" y2=\"%.0f\" stroke=\"black\" stroke-width=\"5\" />\n", hx1, hy1, SIZE / 2, SIZE / 2 );

    double mdeg = ( m + s / 60.0 ) * PI / 30 - PI / 2;
    double mx1 = SIZE / 2 + cos( mdeg ) * SIZE / 2 * 0.7;
    double my1 = SIZE / 2 + sin( mdeg ) * SIZE / 2 * 0.7;
    printf( "\t<line x1=\"%.0f\" y1=\"%.0f\" x2=\"%.0f\" y2=\"%.0f\" stroke=\"black\" stroke-width=\"3\" />\n", mx1, my1, SIZE / 2, SIZE / 2 );

    double sdeg = s * PI / 30 - PI / 2;
    double sx1 = SIZE / 2 + cos( sdeg ) * SIZE / 2 * 0.9;
    double sy1 = SIZE / 2 + sin( sdeg ) * SIZE / 2 * 0.9;
    printf( "\t<line x1=\"%.0f\" y1=\"%.0f\" x2=\"%.0f\" y2=\"%.0f\" stroke=\"red\" />\n", sx1, sy1, SIZE / 2, SIZE / 2 );

    printf( "</svg>");
    return 0;
}
