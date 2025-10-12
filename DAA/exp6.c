// Matrix Chain Multiplication using DP with dynamic arrays and time
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>

void printOpt(int **s,int i,int j)
{
    if(i==j)
    {
        printf("A%d",i+1); 
        return;
    }
    printf("(");
    printOpt(s,i,s[i][j]);
    printOpt(s,s[i][j]+1,j);
    printf(")");
}

int main()
{
    int n,opt;
    printf("Enter number of matrices:");
    scanf("%d",&n);

    int *p=(int*)malloc(sizeof(int)*(n+1));
    long long **dp=(long long**)malloc(sizeof(long long*)*n);
    int **s=(int**)malloc(sizeof(int*)*n);
    for(int i=0;i<n;i++)
    {
        dp[i]=(long long*)malloc(sizeof(long long)*n);
        s[i]=(int*)malloc(sizeof(int)*n);
    }

    printf("Choose input type:\n1. Manual\n2. Random\n");
    scanf("%d",&opt);

    if(opt==1)
    {
        printf("Enter dimensions (n+1 numbers):\n");
        for(int i=0;i<=n;i++) scanf("%d",&p[i]);
    }
    else
    {
        srand(time(0));
        printf("Random dimensions: ");
        for(int i=0;i<=n;i++)
        {
            p[i]=rand()%10+1;
            printf("%d ",p[i]);
        }
        printf("\n");
    }

    clock_t start=clock();

    for(int i=0;i<n;i++) 
    {
        dp[i][i]=0;
    }

    for(int l=2;l<=n;l++)
    {
        for(int i=0;i<=n-l;i++)
        {
            int j=i+l-1;
            dp[i][j]=LLONG_MAX;
            for(int k=i;k<j;k++)
            {
                long long cost=dp[i][k]+dp[k+1][j]+(long long)p[i]*p[k+1]*p[j+1];
                if(cost<dp[i][j])
                {
                    dp[i][j]=cost;
                    s[i][j]=k;
                }
            }
        }
    }

    clock_t end=clock();
    double t=(double)(end-start)/CLOCKS_PER_SEC;

    printf("Minimum multiplications:%lld\n",dp[0][n-1]);
    printf("Optimal parenthesis:");
    printOpt(s,0,n-1);
    printf("\nTime taken: %lf sec\n",t);

    free(p);
    for(int i=0;i<n;i++){free(dp[i]); free(s[i]);}
    free(dp); free(s);

    return 0;
}
