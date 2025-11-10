// 0/1 Knapsack using Dynamic Programming
#include <stdio.h>
#include <stdlib.h>

int max(int a,int b)
{
    if(a>b)
        return a;
    else
        return b;
}
int knap(int n,int w,int val[],int wt[])
{
    int **k=(int**)malloc((n+1)*sizeof(int*));
    for(int i=0;i<=n;i++)
    {
        k[i]=(int*)malloc((w+1)*sizeof(int));
    }
    for(int i=0;i<=n;i++)
    {
        for(int j=0;j<=w;j++)
        {
            if(i==0||j==0)
            {
                k[i][j]=0;
            }
            else if(wt[i-1]<=j)
                {
                    k[i][j]=max(val[i-1]+k[i-1][j-wt[i-1]],k[i-1][j]);
                }
            else
                {
                    k[i][j]=k[i-1][j];
                }
        }
    }
    int res=k[n][w];
    for(int i=0;i<=n;i++) 
    {
        free(k[i]);
    }
    free(k);
    return res;
}
int main()
{
    int n,w;
    printf("Enter number of items: ");
    scanf("%d",&n);
    printf("Enter knapsack capacity: ");
    scanf("%d",&w);
    int *val=(int*)malloc(n*sizeof(int));
    int *wt=(int*)malloc(n*sizeof(int));
    printf("\nEnter values of items:\n");
    for(int i=0;i<n;i++)
    {
        printf("Value of item %d: ",i+1);
        scanf("%d",&val[i]);
    }
    printf("\nEnter weights of items:\n");
    for(int i=0;i<n;i++)
    {
        printf("Weight of item %d: ",i+1);
        scanf("%d",&wt[i]);
    }
    int ans=knap(n,w,val,wt);
    printf("\nMaximum profit = %d\n",ans);
    free(val);
    free(wt);
    return 0;
}
