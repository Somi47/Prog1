#include <stdio.h>
#include <stdlib.h>

char* GetLine( FILE *pFile )
{
    char *strLine = (char *)malloc( sizeof(char) * 50 );
    if( strLine == NULL )
    {
        printf("Nem sikerult betolteni a players.txt-t!\n");
    }

    int i = 0;
    char c = (char)fgetc( pFile );
    for( i = 0; i<49 && c != '\n' && c != '\0' && c != EOF; ++i )
    {
        strLine[i] = c;
        c = (char)fgetc( pFile );
    }
    strLine[i+1] = '\0';

    return strLine;
}

int main()
{
    FILE *pFileNames = fopen( "players.txt", "r" );
    if( pFileNames == NULL )
    {
        printf("Nem sikerult betolteni a players.txt-t!\n");
    }


    printf(GetLine( pFileNames ) );
    return 0;
}
