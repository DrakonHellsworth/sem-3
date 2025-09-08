// full strassen vs traditional matrix multiplication
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int nextpow(int n)
{
    int p=1;
    while(p<n) p<<=1;
    return p;
}

int** allocm(int n)
{
    int **m=(int**)malloc(n*sizeof(int*));
    if(!m) return NULL;
    for(int i=0;i<n;i++)
    {
        m[i]=(int*)malloc(n*sizeof(int));
        if(!m[i]) return NULL;
    }
    return m;
}

void addm(int **a,int **b,int **c,int n)
{
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            c[i][j]=a[i][j]+b[i][j];
}

void subm(int **a,int **b,int **c,int n)
{
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            c[i][j]=a[i][j]-b[i][j];
}

void multrad(int **a,int **b,int **c,int n)
{
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
        {
            long long sum=0;
            for(int k=0;k<n;k++)
                sum += (long long)a[i][k]*b[k][j];
            c[i][j]=(int)sum;
        }
}

void strassenRec(int **a,int **b,int **c,int n)
{
    if(n<=64) 
    {
        multrad(a,b,c,n);
        return;
    }
    int m=n/2;
    int **a11=allocm(m),**a12=allocm(m),**a21=allocm(m),**a22=allocm(m);
    int **b11=allocm(m),**b12=allocm(m),**b21=allocm(m),**b22=allocm(m);
    int **c11=allocm(m),**c12=allocm(m),**c21=allocm(m),**c22=allocm(m);
    int **p1=allocm(m),**p2=allocm(m),**p3=allocm(m),**p4=allocm(m);
    int **p5=allocm(m),**p6=allocm(m),**p7=allocm(m);
    int **t1=allocm(m),**t2=allocm(m);
    for(int i=0;i<m;i++)
        for(int j=0;j<m;j++)
        {
            a11[i][j]=a[i][j];
            a12[i][j]=a[i][j+m];
            a21[i][j]=a[i+m][j];
            a22[i][j]=a[i+m][j+m];
            b11[i][j]=b[i][j];
            b12[i][j]=b[i][j+m];
            b21[i][j]=b[i+m][j];
            b22[i][j]=b[i+m][j+m];
        }
    addm(a11,a22,t1,m); addm(b11,b22,t2,m); strassenRec(t1,t2,p1,m);
    addm(a21,a22,t1,m); strassenRec(t1,b11,p2,m);
    subm(b12,b22,t2,m); strassenRec(a11,t2,p3,m);
    subm(b21,b11,t2,m); strassenRec(a22,t2,p4,m);
    addm(a11,a12,t1,m); strassenRec(t1,b22,p5,m);
    subm(a21,a11,t1,m); addm(b11,b12,t2,m); strassenRec(t1,t2,p6,m);
    subm(a12,a22,t1,m); addm(b21,b22,t2,m); strassenRec(t1,t2,p7,m);
    addm(p1,p4,t1,m); subm(t1,p5,t2,m); addm(t2,p7,c11,m);
    addm(p3,p5,c12,m);
    addm(p2,p4,c21,m);
    subm(p1,p2,t1,m); addm(t1,p3,t2,m); addm(t2,p6,c22,m);
    for(int i=0;i<m;i++)
    {
        for(int j=0;j<m;j++)
        {
            c[i][j]=c11[i][j];
            c[i][j+m]=c12[i][j];
            c[i+m][j]=c21[i][j];
            c[i+m][j+m]=c22[i][j];
        }
    }
}
void strassen(int **a,int **b,int **c,int n)
{
    int p=nextpow(n);
    int **ap=allocm(p),**bp=allocm(p),**cp=allocm(p);
    for(int i=0;i<p;i++)
    {
        for(int j=0;j<p;j++)
        {
            ap[i][j]=(i<n&&j<n)?a[i][j]:0;
            bp[i][j]=(i<n&&j<n)?b[i][j]:0;
            cp[i][j]=0;
        }
    }
    strassenRec(ap,bp,cp,p);
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            c[i][j]=cp[i][j];
        }
    }
}
void printPart(int **c,int n)
{
    for(int i=0;i<n&&i<5;i++)
    {
        for(int j=0;j<n&&j<5;j++) printf("%d ",c[i][j]);
        if(n>5) 
        {
            printf("...(etc.)");
        }
        printf("\n");
    }
}
int main()
{
    int n;
    printf("enter matrix size (n):");
    if(scanf("%d",&n)!=1) return 0;
    int **a=allocm(n),**b=allocm(n),**c1=allocm(n),**c2=allocm(n);
    if(!a||!b||!c1||!c2) { printf("alloc fail\n"); return 0; }
    srand(69);
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
        {
            a[i][j]=rand()%10;
            b[i][j]=rand()%10;
            c1[i][j]=0;
            c2[i][j]=0;
        }
    clock_t s=clock();
    multrad(a,b,c1,n);
    clock_t e=clock();
    double t1=(double)(e-s)/CLOCKS_PER_SEC;
    s=clock();
    strassen(a,b,c2,n);
    e=clock();
    double t2=(double)(e-s)/CLOCKS_PER_SEC;
    printf("first part of result matrix using traditional:\n");
    printPart(c1,n);
    printf("first part of result matrix using Strassen:\n");
    printPart(c2,n);
    printf("results (n=%d):\n",n);
    printf("traditional time: %lf sec\n",t1);
    printf("Strassen time: %lf sec\n",t2);
    return 0;
}
