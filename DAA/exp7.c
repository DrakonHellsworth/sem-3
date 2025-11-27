#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define INF 999
void dijk(int n,int G[200][200],int src)
{
    int vis[200]={0},dis[200];
    for(int i=0;i<n;i++)
    {
        dis[i]=(G[src][i]==0)?INF:G[src][i];
    }
    dis[src]=0;
    vis[src]=1;
    for(int k=1;k<n-1;k++)
    {
        int mn=INF,u=-1;
        for(int i=0;i<n;i++)
        {
            if(!vis[i] && dis[i]<mn)
            {
                mn=dis[i];
                u=i;
            }
        }
        if(u==-1) 
        {
            break;
        }
        vis[u]=1;
        for(int j=0;j<n;j++)
        {
            if(!vis[j] && G[u][j] && dis[u]+G[u][j]<dis[j])
            {
                dis[j]=dis[u]+G[u][j];
            }
        }
    }
}
void bell(int n,int e,int u[],int v[],int w[],int src)
{
    int dis[200];
    for(int i=0;i<n;i++)
    {
        dis[i]=INF;
    }
    dis[src]=0;
    for(int i=0;i<n-1;i++)
    {
        for(int j=0;j<e;j++)
        {
            if(dis[u[j]]+w[j]<dis[v[j]])
            {
                dis[v[j]]=dis[u[j]]+w[j];
            }
        }
    }
}
int main()
{
    int n,e,src;
    printf("Enter number of vertices:");
    scanf("%d",&n);
    printf("Enter number of edges:");
    scanf("%d",&e);
    printf("Enter source vertex:");
    scanf("%d",&src);
    int G[200][200]={0},u[e],v[e],w[e];
    srand(time(NULL));
    for(int i=0;i<e;i++)
    {
        u[i]=rand()%n;
        v[i]=rand()%n;
        if(u[i]==v[i]) 
        {
            v[i]=(v[i]+1)%n;
        }
        w[i]=(rand()%50)+1;
        G[u[i]][v[i]]=w[i];
    }
    printf("\nRandom graph generated with %d vertices and %d edges.\n",n,e);
    printf("(Weights are between 1 and 50)\n");
    clock_t st,en;
    double ms1,ms2;
    st=clock();
    for(int i=0;i<1000;i++)
    {
        dijk(n,G,src);
    }
    en=clock();
    ms1=(double)(en-st)*1000.0/CLOCKS_PER_SEC/1000.0;
    st=clock();
    for(int i=0;i<1000;i++)
    {
        bell(n,e,u,v,w,src);
    }
    en=clock();
    ms2=(double)(en-st)*1000.0/CLOCKS_PER_SEC/1000.0;
    printf("\nAverage time per run (1000 repeats):\n");
    printf("Dijkstra's algorithm: %.3f ms\n",ms1);
    printf("Bellman-Ford algorithm: %.3f ms\n",ms2);
    return 0;
}
