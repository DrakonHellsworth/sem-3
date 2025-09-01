// Merge Sort vs Quick Sort using Divide and Conquer
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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
    while(i<n1&&j<n2)
    {
        if(L[i]<=R[j])
        {
            a[k]=L[i];
            i++;
        }
        else
        {
            a[k]=R[j];
            j++;
        }
        k++;
    }
    while(i<n1)
    {
        a[k]=L[i];
        i++;k++;
    }
    while(j<n2)
    {
        a[k]=R[j];
        j++;k++;
    }
}
void mergeSort(int a[],int l,int r)
{
    if(l<r)
    {
        int m=l+(r-l)/2;
        mergeSort(a,l,m);
        mergeSort(a,m+1,r);
        merge(a,l,m,r);
    }
}
int partition(int a[],int l,int r)
{
    int p=a[r],i=l-1;
    for(int j=l;j<r;j++)
    {
        if(a[j]<=p)
        {
            i++;
            int t=a[i];
            a[i]=a[j];
            a[j]=t;
        }
    }
    int t=a[i+1];
    a[i+1]=a[r];
    a[r]=t;
    return i+1;
}
void quickSort(int a[],int l,int r)
{
    if(l<r)
    {
        int pi=partition(a,l,r);
        quickSort(a,l,pi-1);
        quickSort(a,pi+1,r);
    }
}
void printFirst(int a[],int n)
{
    for(int i=0;i<n&&i<20;i++)
    {
        printf("%d ",a[i]);
    }
    if(n>20) printf("...(etc.)");
    printf("\n");
}
int main()
{
    int n;
    printf("Enter number of elements:");
    scanf("%d",&n);
    int *a=(int*)malloc(sizeof(int)*n);
    int *b=(int*)malloc(sizeof(int)*n);
    for(int i=0;i<n;i++)
    {
        a[i]=rand()%100000;
        b[i]=a[i];
    }
    clock_t s=clock();
    mergeSort(a,0,n-1);
    clock_t e=clock();
    double t1=(double)(e-s)/CLOCKS_PER_SEC;
    s=clock();
    quickSort(b,0,n-1);
    e=clock();
    double t2=(double)(e-s)/CLOCKS_PER_SEC;
    printf("First 20 elements after Merge Sort:\n");
    printFirst(a,n);
    printf("First 20 elements after Quick Sort:\n");
    printFirst(b,n);
    printf("Results (n=%d):\n",n);
    printf("Merge Sort time: %lf sec\n",t1);
    printf("Quick Sort time: %lf sec\n",t2);
    return 0;
}
