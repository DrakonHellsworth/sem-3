#include <stdio.h>
#include <stdlib.h>
#include <time.h>
void floyd(int n,int **G)
{
    for(int k=0;k<n;k++)
    {
        for(int i=0;i<n;i++)
        {
            for(int j=0;j<n;j++)
            {
                if(G[i][k]+G[k][j]<G[i][j])
                {
                    G[i][j]=G[i][k]+G[k][j];
                }
            }
        }
    }
}
int main()
{
    int n;
    printf("Enter number of vertices:");
    scanf("%d",&n);
    int **G=(int**)malloc(n*sizeof(int*));
    int **T=(int**)malloc(n*sizeof(int*));
    for(int i=0;i<n;i++)
    {
        G[i]=(int*)malloc(n*sizeof(int));
        T[i]=(int*)malloc(n*sizeof(int));
    }
    srand(time(NULL));
    printf("Adjacency matrix (fully connected, weights 1–10):\n");
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            if(i==j)
            {
                G[i][j]=0;
            }
            else
            {
                G[i][j]=(rand()%10)+1;
            }
            T[i][j]=G[i][j];
            if(i<10 && j<10)
            {
                printf("%4d ",G[i][j]);
            }
        }
        if(i<10)
        {
            printf("\n");
        }
    }
    if(n>10)
    {
        printf("... (first 10x10 elements)\n");
    }
    clock_t st=clock();
    for(int r=0;r<1000;r++)
    {
        for(int i=0;i<n;i++)
        {
            for(int j=0;j<n;j++)
            {
                G[i][j]=T[i][j];
            }
        }
        floyd(n,G);
    }
    clock_t en=clock();
    double t=(double)(en-st)*1000.0/CLOCKS_PER_SEC/1000.0;
    printf("\nShortest distance matrix (first 10x10 shown):\n");
    for(int i=0;i<n && i<10;i++)
    {
        for(int j=0;j<n && j<10;j++)
        {
            printf("%4d ",G[i][j]);
        }
        printf("\n");
    }
    if(n>10)
    {
        printf("... (matrix of size %dx%d)\n",n,n);
    }
    printf("\nAverage execution time (1000 runs): %.10f ms\n",t);
    for(int i=0;i<n;i++)
    {
        free(G[i]);
        free(T[i]);
    }
    free(G);
    free(T);
    return 0;
}
