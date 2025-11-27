#include <stdio.h>
#include <stdlib.h>

struct Item
{
    int v,w;
};

int cmp(const void *a,const void *b)
{
    struct Item *x=(struct Item*)a;
    struct Item *y=(struct Item*)b;
    double r1=(double)x->v/x->w;
    double r2=(double)y->v/y->w;
    return (r2>r1)?1:(r2<r1?-1:0);
}

void knap(struct Item arr[],int n,int W)
{
    qsort(arr,n,sizeof(struct Item),cmp);
    printf("\nAll items after sorting by value/weight:\n");
    for(int i=0;i<n;i++)
    {
        printf("(v=%d,w=%d) ",arr[i].v,arr[i].w);
    }
    printf("\n\n");
    int curW=0;
    double totVal=0.0;
    printf("Selected items (capacity=%d):\n",W);
    for(int i=0;i<n;i++)
    {
        if(curW+arr[i].w<=W)
        {
            curW+=arr[i].w;
            totVal+=arr[i].v;
            printf("(v=%d,w=%d) -> FULL\n",arr[i].v,arr[i].w);
        }
        else
        {
            int rem=W-curW;
            if(rem>0)
            {
                totVal+=arr[i].v*((double)rem/arr[i].w);
                printf("(v=%d,w=%d) -> %.2f part\n",arr[i].v,arr[i].w,(double)rem/arr[i].w);
                curW=W;
            }
            else
            {
                printf("Skipped (v=%d,w=%d) -> bag full\n",arr[i].v,arr[i].w);
            }
            break;
        }
    }
    printf("\nTotal value in bag=%.2f\n",totVal);
}

int main()
{
    int n,W;
    printf("Enter number of items:");
    scanf("%d",&n);
    struct Item arr[n];
    printf("Enter value and weight (v,w):\n");
    for(int i=0;i<n;i++)
    {
        scanf("%d,%d",&arr[i].v,&arr[i].w);
    }
    printf("Enter bag capacity:");
    scanf("%d",&W);
    knap(arr,n,W);
    return 0;
}
