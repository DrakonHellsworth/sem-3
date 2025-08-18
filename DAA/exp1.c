// Iterative vs Recursive BST insert & search
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct node 
{
    int d;
    struct node *l;
    struct node *r;
};

struct node *r=NULL;
struct node *i=NULL;

struct node* newNode(int v) {
    struct node *n=(struct node*)malloc(sizeof(struct node));
    n->d=v;
    n->l=NULL;
    n->r=NULL;
    return n;
}

struct node* insertRecursive(struct node *rt,int v) {
    if(rt==NULL)
        return newNode(v);
    if(v<rt->d)
        rt->l=insertRecursive(rt->l,v);
    else
        rt->r=insertRecursive(rt->r,v);
    return rt;
}

void insertIterative(struct node **rt,int v) {
    if(*rt==NULL) {
        *rt=newNode(v);
        return;
    }
    struct node *cur=*rt;
    struct node *par=NULL;
    while(cur!=NULL) {
        par=cur;
        if(v<cur->d)
            cur=cur->l;
        else
            cur=cur->r;
    }
    if(v<par->d)
        par->l=newNode(v);
    else
        par->r=newNode(v);
}

int searchRecursive(struct node *rt,int v) {
    if(rt==NULL)
        return 0;
    if(rt->d==v)
        return 1;
    if(v<rt->d)
        return searchRecursive(rt->l,v);
    return searchRecursive(rt->r,v);
}

int searchIterative(struct node *rt,int v) {
    struct node *cur=rt;
    while(cur!=NULL) {
        if(cur->d==v)
            return 1;
        if(v<cur->d)
            cur=cur->l;
        else
            cur=cur->r;
    }
    return 0;
}

void inorderPrint(struct node *rt) {
    struct node *st[1000];
    int top=-1;
    struct node *cur=rt;
    int c=0;
    while(top!=-1||cur!=NULL) {
        while(cur!=NULL) {
            st[++top]=cur;
            cur=cur->l;
        }
        cur=st[top--];
        printf("%d ",cur->d);
        c++;
        if(c>=20) {
            printf("... (truncated)\n");
            return;
        }
        cur=cur->r;
    }
    printf("\n");
}

int main() {
    int n,x;
    printf("Enter number of nodes for test: ");
    if(scanf("%d",&n)!=1) return 0;

    int *a=(int*)malloc(sizeof(int)*n);
    srand(1);
    for(x=0;x<n;x++)
        a[x]=rand();

    clock_t s=clock();
    for(x=0;x<n;x++)
        r=insertRecursive(r,a[x]);
    clock_t e=clock();
    double tRecIns=(double)(e-s)/CLOCKS_PER_SEC;

    s=clock();
    for(x=0;x<n;x++)
        insertIterative(&i,a[x]);
    e=clock();
    double tItIns=(double)(e-s)/CLOCKS_PER_SEC;

    printf("First 20 of recursive BST (inorder): ");
    inorderPrint(r);
    printf("First 20 of iterative BST (inorder): ");
    inorderPrint(i);

    s=clock();
    int found=0;
    for(x=0;x<n;x++)
        if(searchRecursive(r,a[x])) found++;
    e=clock();
    double tRecS=(double)(e-s)/CLOCKS_PER_SEC;

    s=clock();
    found=0;
    for(x=0;x<n;x++)
        if(searchIterative(i,a[x])) found++;
    e=clock();
    double tItS=(double)(e-s)/CLOCKS_PER_SEC;

    printf("Results (n=%d):\n",n);
    printf("Recursive insert time: %lf sec\n",tRecIns);
    printf("Iterative insert time: %lf sec\n",tItIns);
    printf("Recursive search time: %lf sec\n",tRecS);
    printf("Iterative search time: %lf sec\n",tItS);

    free(a);
    return 0;
}
