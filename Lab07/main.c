#include <stdio.h>
#include <stdio.h>

void f_1func1(int i2) {
    i2 *= 2;
    printf("func1()... i2 = %d\n", i2);     /* 4 */
}

void f_1func2(int *p3) {
    *p3 *= 2;
    printf("func2()... *p3 = %d\n", *p3);
    p3 = NULL;                              /* 5, 6 */
    printf("func2()... p3 = %p\n", p3);
}

void f_1()
{
    int i1 = 2;
    int *p1 = NULL;
    int *p2 = NULL;
    printf("Hova mutat p1 es p2?\n");       /* 1 */

    p1 = &i1;
    printf("&i1 = %p, p1 = %p\n", &i1, p1);
    printf("i1 = %d, *p1 = %d\n", i1, *p1); /* 2 */

    i1 = 3;  printf("*p1 = %d\n", *p1);
    *p1 = 4; printf("i1 = %d\n", i1);

    p2 = p1;
    *p2 = 5;
    printf("i1 = %d, p2 = %p\n", i1, p2);   /* 3 */
    printf("-----\n");

    f_1func1(i1);
    printf("main()... i1 = %d - de miert?\n", i1);
    printf("-----\n");

    f_1func2(&i1);
    printf("main()... i1 = %d - miert?\n", i1);
    printf("-----\n");

    f_1func2(p2);
    printf("main()... i1 = %d - miert?\n", i1);
    printf("main()... p2 = %p - miert?\n", p2);
}

void f_3Kockahossz( double hossz, double *felulet, double *terfogat )
{
    *felulet  = hossz * hossz * 6;
    *terfogat = hossz * hossz * hossz;
}

void f_3()
{
    double hossz = 2.7;
    double felulet, terfogat;

    f_3Kockahossz( hossz, &felulet, &terfogat );
    printf( "%f\n%f", felulet, terfogat );
}

int *f_4Keres( int *arr, int length, int x )
{
    for( int i = 0; i < length; ++i )
    {
        if( *(arr + i) == x )
            return arr + i;
    }

    return NULL;
}

void f_4()
{
    int arr[5] = { 3, -2, 7, 0, 4 };

    int x = 7;

    printf( "pointer: %p\n", f_4Keres(arr, 5, x));
    printf( "index:   %d",   f_4Keres(arr, 5, x) - arr);
}

void f_6Trim( char *before, char *after, int size )
{
    int beg = 0;

    while( beg < size && before[beg] == ' ' )
        ++beg;

    int end = beg;
    while( end < size && before[end] != '\0' )
        ++end;

    while( end >= 0 && before[end] == ' ' )
        --end;

    int j=0;
    for( int i = beg; i <= end; ++i )
        after[j++] = before[i];

    after[j] = '\0';
}

void f_6()
{
    char before[100];// = " a  b   ";
    char after[100];

    scanf( before );
    printf( "%s\n", before );

    f_6Trim( before, after, 100 );

    printf( after );
}

int main(void)
{
    //f_1();
    //f_3();
    //f_4();
    f_6();

    return 0;
}
