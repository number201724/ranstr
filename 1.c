#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <sys/time.h>


#define MAXELEMENT 10000000
#define MAXSTRLEN 17

static char charstable[] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};

unsigned char md[16] = {0};


int inc(int c)
{
    md[c]++;
    if(md[c] > 0xf)
    {
        md[c]=0;
        inc(c+1);
    }
}

int getidx(int n)
{
    if(n==0)
    {
        inc(0);
    }

    return md[n];
}

void randstr(char *s, int len)
{
    for(int i =0; i < len; i++)
    {
        s[i] = charstable[getidx(i)];
    }

    s[len-1] = 0;
}

char unique_elem[MAXELEMENT][MAXSTRLEN];
int main()
{
    struct timeval begin, end;
    char *s;
    
    gettimeofday(&begin, NULL);
    for(int i =0; i< MAXELEMENT;i++)
    {
        s = unique_elem[i];

        randstr(s, MAXSTRLEN);
    }
    
    gettimeofday(&end, NULL);

    
    for(int i =0; i< 100;i++)
    {
        printf("%d      %s\n", i+1, unique_elem[i]);
    }


    printf("last:%d       %s\n",MAXELEMENT,unique_elem[MAXELEMENT-1]);

    printf("total used time:%lu usec\n", end.tv_usec - begin.tv_usec);

}
