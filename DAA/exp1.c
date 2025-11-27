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

struct node* newNode(int v) 
{
    struct node *n=(struct node*)malloc(sizeof(struct node));
    n->d=v;
    n->l=NULL;
    n->r=NULL;
    return n;
}

struct node* insRe(struct node *re,int v) 
{
    if(re==NULL)
    {
        return newNode(v);
    }
    if(v<re->d)
    {
        re->l=insRe(re->l,v);
    }
    else
    {
        re->r=insRe(re->r,v);
    }
    return re;
}

void insIt(struct node **it,int v) 
{
    if(*it==NULL) 
    {
        *it=newNode(v);
        return;
    }
    struct node *cur=*it;
    struct node *par=NULL;
    while(cur!=NULL) 
    {
        par=cur;
        if(v<cur->d)
        {
            cur=cur->l;
        }
        else
        {
            cur=cur->r;
        }
    }
    if(v<par->d)
    {
        par->l=newNode(v);
    }
    else
    {
        par->r=newNode(v);
    }
}

int searchRe(struct node *re,int v) 
{
    if(re==NULL)
        return 0;
    if(re->d==v)
        return 1;
    if(v<re->d)
        return searchRe(re->l,v);
    return searchRe(re->r,v);
}

int searchIt(struct node *it,int v) 
{
    struct node *cur=it;
    while(cur!=NULL) 
    {
        if(cur->d==v)
        {
            return 1;
        }
        if(v<cur->d)
        {
            cur=cur->l;
        }
        else
        {
            cur=cur->r;
        }
    }
    return 0;
}

void inorder(struct node *f) 
{
    struct node *st[100];
    int top=-1;
    struct node *cur=f;
    int c=0;
    while(top!=-1||cur!=NULL) 
    {
        while(cur!=NULL) 
        {
            st[++top]=cur;
            cur=cur->l;
        }
        cur=st[top--];
        printf("%d ",cur->d);
        c++;
        if(c>=20) 
        {
            printf("...(etc.)\n");
            return;
        }
        cur=cur->r;
    }
    printf("\n");
}

int main() 
{
    int n,x;
    printf("Enter number of nodes for test:");
    if(scanf("%d",&n)!=1) 
    {
        return 0;
    }
    int *a=(int*)malloc(sizeof(int)*n);
    for(x=0;x<n;x++)
    {
        a[x]=rand();
    }
    clock_t s=clock();
    for(x=0;x<n;x++)
    {
        r=insRe(r,a[x]);
    }
    clock_t e=clock();
    double t1=(double)(e-s)/CLOCKS_PER_SEC;
    s=clock();
    for(x=0;x<n;x++)
    {
        insIt(&i,a[x]);
    }
    e=clock();
    double t2=(double)(e-s)/CLOCKS_PER_SEC;
    printf("First 20 of recursive BST (inorder): ");
    s=clock();
    inorder(r);
    e=clock();
    double t0=(double)(e-s)/CLOCKS_PER_SEC;
    printf("Time taken for inorder traversal for recursion: %lf sec\n", t0);
    printf("First 20 of iterative BST (inorder): ");
    s=clock();
    inorder(i);
    e=clock();
    double t00=(double)(e-s)/CLOCKS_PER_SEC;
    printf("Time taken for inorder traversal for iteration: %lf sec\n",t00);
    
    inorder(i);
    s=clock();
    int f=0;
    for(x=0;x<n;x++)
    {
        if(searchRe(r,a[x])) 
        {
            f++;
        }
    }
    e=clock();
    double t3=(double)(e-s)/CLOCKS_PER_SEC;

    s=clock();
    f=0;
    for(x=0;x<n;x++)
    {
        if(searchIt(i,a[x])) 
        {
            f++;
        }
    }
    e=clock();
    double t4=(double)(e-s)/CLOCKS_PER_SEC;
    printf("Recursive insert time: %lf sec\n",t1);
    printf("Iterative insert time: %lf sec\n",t2);
    printf("Recursive search time: %lf sec\n",t3);
    printf("Iterative search time: %lf sec\n",t4);
    return 0;
}
