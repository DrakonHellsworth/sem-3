#include <stdio.h>
#include <stdlib.h>

#define INF 999

// ----------- Prim's Algorithm -----------
void prim(int n,int G[20][20])
{
    int vis[20]={0};
    vis[0]=1;
    int e=0,tot=0;
    printf("\nEdges in MST (Prim's):\n");
    while(e<n-1)
    {
        int mn=INF,a=-1,b=-1;
        for(int i=0;i<n;i++)
        {
            if(vis[i])
            {
                for(int j=0;j<n;j++)
                {
                    if(!vis[j] && G[i][j])
                    {
                        if(G[i][j]<mn)
                        {
                            mn=G[i][j];
                            a=i;
                            b=j;
                        }
                    }
                }
            }
        }
        printf("%d - %d : %d\n",a,b,G[a][b]);
        tot+=G[a][b];
        vis[b]=1;
        e++;
    }
    printf("Total Weight = %d\n",tot);
}

// ----------- Kruskal's Algorithm -----------
int par[20];

int find(int i)
{
    while(par[i]!=i)
    {
        i=par[i];
    }
    return i;
}

void uni(int i,int j)
{
    int a=find(i);
    int b=find(j);
    par[a]=b;
}

void kruskal(int n,int G[20][20])
{
    for(int i=0;i<n;i++)
    {
        par[i]=i;
    }
    int e=0,tot=0;
    printf("\nEdges in MST (Kruskal's):\n");
    while(e<n-1)
    {
        int mn=INF,a=-1,b=-1;
        for(int i=0;i<n;i++)
        {
            for(int j=0;j<n;j++)
            {
                if(find(i)!=find(j) && G[i][j]<mn)
                {
                    mn=G[i][j];
                    a=i;
                    b=j;
                }
            }
        }
        uni(a,b);
        printf("%d - %d : %d\n",a,b,mn);
        tot+=mn;
        e++;
    }
    printf("Total Weight = %d\n",tot);
}

// ----------- Main Function -----------
int main()
{
    int n;
    printf("Enter number of vertices:");
    scanf("%d",&n);
    int G[20][20];
    printf("Enter adjacency matrix:\n");
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            scanf("%d",&G[i][j]);
            if(G[i][j]==0)
            {
                G[i][j]=INF; // treat 0 as no edge
            }
        }
    }
    prim(n,G);
    kruskal(n,G);
    return 0;
}
