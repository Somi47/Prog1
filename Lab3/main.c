#include <stdio.h>
#include <stdbool.h>

//c--
#define A for
#define B int
#define C printf
#define D (
#define E )
#define F {
#define G }


void f6 D  E
 F
    B x[] =  F 11, 4, 3, 9, 26, 4, 2, 17, 12, 15 G ;

    C D  "A tomb: "  E ;
    A D  B i = 0; i < 10; ++i  E
        C D  "%d ", x[i]  E ;

    C D  "\nA tomb: "  E ;
    A D  B i = 0; i < 10; ++i  E
        C D  "[%d]=%d ", i, x[i]  E ;

    B minindex = 0;
    A D  B i = 0; i < 10; ++i  E
        if D  x[minindex] > x[i]  E
            minindex = i;

    C D  "\nA legkisebb: %d\n", x[minindex]  E ;
    C D  "Jelolve:"  E ;
    A D  B i = 0; i < 10; ++i  E
     F
        C D  " %d", x[i]  E ;
        if D  i == minindex  E
            C D  "[MIN]"  E ;
     G
 G

void f7 D  E
 F
    B x[] =  F 11, 4, 3, 9, 26, 4, 2, 17, 12, 15 G ;
    A D  B i = 0; i < 10; ++i  E
        C D  "%2d ", x[i]  E ;

    C D  "\n"  E ;

    A D  B i = 0; i < 9; ++i  E
     F
        B helperFirst = x[0];

        A D  B i = 1; i < 10; ++i  E
            x[i - 1] = x[ i ];

        x[9] = helperFirst;

        A D  B i = 0; i < 10; ++i  E
            C D  "%2d ", x[i]  E ;

        C D  "\n"  E ;
     G
 G

B main D  E
 F
    //f6 D  E ;
    f7 D  E ;

    return 0;
 G
