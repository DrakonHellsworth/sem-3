// String Match Naive vs Rabin-Karp
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define D 256
#define Q 101
char* getln()
{
    int c,sz=0,cap=16;
    char *s=malloc(cap);
    while((c=getchar())!='\n' && c!=EOF)
    {
        if(sz+1>=cap)
        {
            cap*=2;
            s=realloc(s,cap);
        }
        s[sz++]=c;
    }
    s[sz]=0;
    return s;
}
void prt(const char *t,int st,int m)
{
    printf("Match at %d to %d : ",st,st+m-1);
    for(int i=0;i<m;i++) printf("%c",t[st+i]);
    printf("\n");
}
void naive(const char *t,const char *p)
{
    int n=strlen(t),m=strlen(p);
    for(int s=0;s<=n-m;s++)
    {
        int j=0;
        while(j<m && t[s+j]==p[j]) j++;
        if(j==m) prt(t,s,m);
    }
}
void rk(const char *t,const char *p)
{
    int n=strlen(t),m=strlen(p);
    if(m>n) return;
    int h=1;
    for(int i=0;i<m-1;i++) h=(h*D)%Q;
    int ph=0,th=0;
    for(int i=0;i<m;i++)
    {
        ph=(ph*D+p[i])%Q;
        th=(th*D+t[i])%Q;
    }
    for(int s=0;s<=n-m;s++)
    {
        if(ph==th)
        {
            int ok=1;
            for(int i=0;i<m;i++)
                if(t[s+i]!=p[i]){ok=0;break;}
            if(ok) prt(t,s,m);
        }
        if(s<n-m)
        {
            th=(D*(th-t[s]*h)+t[s+m])%Q;
            if(th<0) th+=Q;
        }
    }
}
int main()
{
    printf("Text:");
    char *t=getln();
    printf("Pattern:");
    char *p=getln();
    clock_t a,b;
    double tn,tr;
    printf("\nNaive:\n");
    a=clock();
    naive(t,p);
    b=clock();
    tn=(double)(b-a)/1000.0;
    printf("Naive Time: %.5f ms\n",tn);
    printf("\nRabin-Karp:\n");
    a=clock();
    rk(t,p);
    b=clock();
    tr=(double)(b-a)/1000.0;
    printf("Rabin-Karp Time: %.5f ms\n",tr);
    free(t);
    free(p);
    return 0;
}
