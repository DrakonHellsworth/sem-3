// Job Sequencing with Deadlines - Greedy vs Brute Force with Random Jobs
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
struct job 
{
    int id;
    int profit;
    int deadline;
};

void swap(struct job *a,struct job *b) 
{
    struct job temp=*a;
    *a=*b;
    *b=temp;
}

int calculateProfit(struct job jobs[], int n, int maxD, int sequence[]) 
{
    int *slot=(int*)malloc(maxD*sizeof(int));
    for(int i=0; i < maxD; i++) 
    {
        slot[i]=-1;
    }
    int profitSum=0,idx=0;

    for(int i=0;i<n;i++) 
    {
        for(int j=(jobs[i].deadline>maxD?maxD:jobs[i].deadline)-1;j>=0;j--) 
        {
            if(slot[j]==-1) 
            {
                slot[j]=i;
                profitSum+=jobs[i].profit;
                if(sequence!=NULL)
                {
                    sequence[idx++]=jobs[i].id;
                }
                break;
            }
        }
    }

    free(slot);
    return idx;
}

void permute(struct job jobs[],int l,int r,int maxD,int *maxProfit,int bestSeq[],int n) 
{
    if(l==r) 
    {
        int tempSeq[maxD];
        int profit=calculateProfit(jobs,n,maxD,tempSeq);
        int totalProfit=0;
        for(int i=0; i<profit;i++)
            {
                for(int j=0;j<n;j++)
                {
                    if(jobs[j].id==tempSeq[i])
                    {
                        totalProfit+=jobs[j].profit;
                    }
                }
            }
        if(totalProfit>*maxProfit) 
        {
            *maxProfit=totalProfit;
            for(int i=0;i<profit;i++)
                {
                    bestSeq[i]=tempSeq[i];
                }
            for(int i=profit;i<maxD;i++)
                {
                    bestSeq[i]=0;
                }
        }
        return;
    }
    for(int i=l;i<=r;i++) 
    {
        swap(&jobs[l],&jobs[i]);
        permute(jobs,l+1,r,maxD,maxProfit,bestSeq,n);
        swap(&jobs[l],&jobs[i]);
    }
}

int main() 
{
    int n,i,j,maxD=0;
    srand(time(0));
    printf("Enter number of jobs: ");
    scanf("%d",&n);

    struct job *jobs=(struct job*)malloc(n*sizeof(struct job));

    printf("\nGenerated Jobs:\n");
    for(i=0;i<n;i++) 
    {
        jobs[i].id=i+1;
        jobs[i].profit=rand()%100+1;
        jobs[i].deadline=rand()%n+1;
        printf("Job %d: Profit=%d,Deadline=%d\n",jobs[i].id,jobs[i].profit,jobs[i].deadline);
        if(jobs[i].deadline > maxD) 
        {
            maxD=jobs[i].deadline;
        }
    }

    clock_t startGreedy=clock();
    int *slot=(int*)malloc(maxD*sizeof(int));
    for(i = 0; i < maxD; i++) 
    {
        slot[i]=-1;
    }

    for(i=0;i<n-1;i++)
        {
            for(j=i+1;j<n;j++)
            {
                if(jobs[i].profit<jobs[j].profit) 
                {
                struct job temp=jobs[i];
                jobs[i]=jobs[j];
                jobs[j]=temp;
            }
        }
    }

    int greedyProfit=0;
    int *greedySeq=(int*)malloc(maxD * sizeof(int));
    int idx=0;
    for(i=0;i<n;i++)
        {
            for(j=(jobs[i].deadline>maxD?maxD:jobs[i].deadline)-1;j>=0;j--)
            {
                if(slot[j]==-1) 
                {
                slot[j]=i;
                greedyProfit+=jobs[i].profit;
                greedySeq[idx++]=jobs[i].id;
                break;
            }

    clock_t endGreedy=clock();
    double greedyTime=((double)(endGreedy-startGreedy))/CLOCKS_PER_SEC;

    printf("\nGreedy Job sequence: ");
    for(i=0;i<idx;i++) 
    {
        printf("%d ",greedySeq[i]);
    }
    printf("\nTotal Profit (Greedy)=%d",greedyProfit);
    printf("\nGreedy execution time: %.6f seconds\n",greedyTime);

    free(slot);
    free(greedySeq);

    clock_t startBF=clock();

    int maxProfitBF=0;
    int *bestSeqBF=(int*)malloc(maxD*sizeof(int));
    for(i=0;i<maxD;i++)
    {
        bestSeqBF[i]=0;
    }
    permute(jobs,0,n-1,maxD,&maxProfitBF,bestSeqBF,n);

    clock_t endBF=clock();
    double bfTime=((double)(endBF-startBF))/CLOCKS_PER_SEC;

    printf("\nBrute Force Job sequence: ");
    for(i=0;i<maxD && bestSeqBF[i]!=0;i++) 
    {
        printf("%d ",bestSeqBF[i]);
    }
    printf("\nTotal Profit (Brute Force)=%d",maxProfitBF);
    printf("\nBrute Force execution time:%.6f seconds\n",bfTime);

    free(jobs);
    free(bestSeqBF);
    return 0;
}}}