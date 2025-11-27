// Merge Sort vs Quick Sort (Simple Version)
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int isSorted(int a[],int n)
{
    for(int i=1;i<n;i++)
        {
            if(a[i]<a[i-1]) return 0;
        }
    return 1;
}
void merge(int a[],int l,int m,int r)
{
    int n1=m-l+1,n2=r-m;
    int L[n1],R[n2];
    for(int i=0;i<n1;i++) 
    {
        L[i]=a[l+i];
    }
    for(int j=0;j<n2;j++) 
    {
        R[j]=a[m+1+j];
    }
    int i=0,j=0,k=l;
    while(i<n1 && j<n2)
    {
        if(L[i]<=R[j]) a[k++]=L[i++];
        else a[k++]=R[j++];
    }
    while(i<n1) 
    {
        a[k++]=L[i++];
    }
    while(j<n2) 
    {
        a[k++]=R[j++];
    }
}
void mergeSort(int a[],int l,int r)
{
    if(l>=r) return;
    int m=(l+r)/2;
    mergeSort(a,l,m);
    mergeSort(a,m+1,r);
    merge(a,l,m,r);
}
void quickSort(int a[],int l,int r)
{
    if(l>=r) return;
    int p=a[(l+r)/2];
    int i=l,j=r;
    while(i<=j)
    {
        while(a[i]<p) 
        {
            i++;
        }
        while(a[j]>p) 
        {
            j--;
        }
        if(i<=j)
        {
            int t=a[i];
            a[i]=a[j];
            a[j]=t;
            i++;
            j--;
        }
    }
    quickSort(a,l,j);
    quickSort(a,i,r);
}
void printArr(int a[],int n)
{
    for(int i=0;i<n;i++) 
    {
        printf("%d ",a[i]);
    }
    printf("\n");
}
int main()
{
    int n;
    printf("Enter array size: ");
    scanf("%d",&n);
    int *a=malloc(n*sizeof(int));
    int *b=malloc(n*sizeof(int));
    printf("Enter %d elements:\n",n);
    for(int i=0;i<n;i++)
    {
        scanf("%d",&a[i]);
        b[i]=a[i];
    }
    clock_t s,e;
    double tm,tq;
    s=clock();
    if(!isSorted(a,n)) mergeSort(a,0,n-1);
    e=clock();
    tm=(double)(e-s)/CLOCKS_PER_SEC;
    s=clock();
    if(!isSorted(b,n)) quickSort(b,0,n-1);
    e=clock();
    tq=(double)(e-s)/CLOCKS_PER_SEC;
    printf("\nSorted by Merge Sort:\n");
    printArr(a,n);
    printf("\nSorted by Quick Sort:\n");
    printArr(b,n);
    printf("\nMerge Sort time: %lf sec\n",tm);
    printf("Quick Sort time: %lf sec\n",tq);
    free(a);
    free(b);
    return 0;
}
