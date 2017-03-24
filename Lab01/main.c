#include <stdio.h>
#include <stdlib.h>

#define PI 3.14

int main()
{
    printf( "  \/\n \/\n\/\n");
    printf( "A printf(\"hello\\n\") kiirja, hogy \"hello\",\nes kezd egy uj sort.\n" );
    printf( "\\\n \\\n  \\\n" );
    printf( "A \"%%d\" segitsegevel egy valtozo ertekettudjuk kiirni.\n" );


    printf("Tartaly festes\n\n");

    double dHeight, dDiameter;

    printf("Milyen magas? ");
    scanf( "%lf", &dHeight );

    printf( "Mennyi az atmeroje? ");
    scanf( "%lf", &dDiameter );

    printf( "%.1f doboz festek kell", ( ( dDiameter / 2 ) * ( dDiameter / 2 ) * PI * 2+ dDiameter * PI * dHeight ) / 2 );
    return 0;
}
