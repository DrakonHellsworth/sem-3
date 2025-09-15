#include <stdio.h>
#include <stdlib.h>

struct Act 
{
    int s,f;
};

int cmp(const void *a,const void *b) 
{
    struct Act *x=(struct Act*)a;
    struct Act *y=(struct Act*)b;
    return x->f-y->f;
}

void actSel(struct Act arr[],int n,int l) 
{
    qsort(arr,n,sizeof(struct Act),cmp);

    printf("\nAll activities after sorting (start,finish):\n");
    for(int i=0;i<n;i++)
        printf("(%d,%d)",arr[i].s,arr[i].f);
    printf("\n\n");
    printf("Selected activities (l=%d):\n",l);
    int c=0;
    int i=0;
    printf("(%d,%d)\n",arr[i].s,arr[i].f);
    c++;
    for(int j=1;j<n&&c<l;j++) 
    {
        if(arr[j].s>=arr[i].f) 
        {
            printf("(%d,%d)\n",arr[j].s,arr[j].f);
            i=j;
            c++;
        } 
        else 
        {
            printf("Skipped (%d,%d)->overlaps with (%d,%d)\n",
                arr[j].s,arr[j].f,arr[i].s,arr[i].f);
        }
    }
    printf("\nTotal selected: %d\n",c);
}

int main() 
{
    int n,l;
    printf("Enter number of activities:");
    scanf("%d",&n);
    struct Act arr[n];
    printf("Enter start and finish times (s,f):\n");
    for(int i=0;i<n;i++)
    {
        scanf("%d,%d",&arr[i].s,&arr[i].f);
    }
    printf("Enter activity selection l(like bag size):");
    scanf("%d",&l);
    actSel(arr,n,l);
    return 0;
}
