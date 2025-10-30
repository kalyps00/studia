#include "plot.h"
char *readString()
{
    size_t size=10;
    size_t len=0;
    char *str=(char *)malloc(size*sizeof(char));
    if(!str)
    {
        printf("Błędna alokacja pamięci. Spróbuj ponownie");
        return NULL;
    }
    int ch;
    while((ch=getchar())!='\n' && ch != EOF)
    {
        if(len+1 >=size)
        {
            size *=2;
            char *new_str=(char *)realloc(str,size);
            if(!new_str)
            {
                printf("Błędna alokacja pamięci. Spróbuj ponownie");
                return NULL;
            }
            str=new_str;
        }
        str[len++]=ch;

    }
    str[len]='\0';
    return str;
}

void szyfruj()
{
    char *tekst;
    char *depth;
    while(1)
    {
    printf("Podaj tekst do zaszyfrowania: ");
    tekst=readString();
    if(strlen(tekst)==0)
    {
        printf("Nie podano tekstu. Sprobuj ponownie\n");
    }
    else
    break;
    }
    while(1)
    {
    printf("Podaj glebokosc szyfru: ");
    depth=readString();
    int deplen=strlen(depth);

    if(deplen==0)
    {
        printf("Nie podano glebokosci szyfru. Sprobuj ponownie\n");
        continue;
    }
    int flag=1;
    for(int i=0;i<deplen;i++)
    {
        if(!isdigit(depth[i]))
        {
            
            flag=0;
        }
    }
    if(flag==1)
    {
        break;
    }
    else
    {
        printf("Glebokosc szyfru moze zawierac tylko cyfry. Sprobuj ponownie\n");
    }
    }

    int dep=atoi(depth);
	if(dep==1)
	{
	printf("Zaszyfrowany tekst to: %s",tekst);
	return;
	}

    int length=strlen(tekst);
    char **arr=(char **)malloc(dep*sizeof(char *));
    if(!arr)
    {
        printf("Bledna alokacja pamieci!");
        return;
    }
    for(int i=0;i<dep;i++)
    {
        arr[i]=(char *)malloc((length+1)*sizeof(char));
        if(!arr[i])
        {
        printf("Bledna alokacja pamieci!");
        return;
        }
        arr[i][0]='\0';
    }
    int rzad=0;
    int kierunek =1;
    for(int i=0;i<length;i++)
    {
        strncat(arr[rzad],&tekst[i],1);
        if(rzad ==0)
        kierunek =1;
        else if(rzad == dep-1)
            kierunek = -1;
        rzad+=kierunek;
    }
    printf("Zaszyfrowany tekst to: ");
    for(int i=0;i<dep;i++)
    {
        printf("%s",arr[i]);
        free(arr[i]);
    }
    free(arr);
    printf("\n");
    
}
