// BST vs AVL Tree Comparison
#include <stdio.h>
#include <stdlib.h>
struct node 
{
    int k,h;
    struct node *l,*r;
};
int ht(struct node *n)
{
    return n ? n->h : 0;
}
int mx(int a,int b)
{
    return a>b?a:b;
}
struct node* newN(int k)
{
    struct node* n=(struct node*)malloc(sizeof(struct node));
    n->k=k;
    n->l=n->r=NULL;
    n->h=1;
    return n;
}
struct node* insBST(struct node* r,int k)
{
    if(!r) return newN(k);
    if(k<r->k) r->l=insBST(r->l,k);
    else if(k>r->k) r->r=insBST(r->r,k);
    return r;
}
struct node* rRot(struct node* y)
{
    struct node* x=y->l;
    struct node* t=x->r;
    x->r=y;
    y->l=t;
    y->h=mx(ht(y->l),ht(y->r))+1;
    x->h=mx(ht(x->l),ht(x->r))+1;
    return x;
}
struct node* lRot(struct node* x)
{
    struct node* y=x->r;
    struct node* t=y->l;
    y->l=x;
    x->r=t;
    x->h=mx(ht(x->l),ht(x->r))+1;
    y->h=mx(ht(y->l),ht(y->r))+1;
    return y;
}
int bal(struct node* n)
{
    return n?ht(n->l)-ht(n->r):0;
}
struct node* insAVL(struct node* r,int k)
{
    if(!r) return newN(k);
    if(k<r->k) r->l=insAVL(r->l,k);
    else if(k>r->k) r->r=insAVL(r->r,k);
    else return r;
    r->h=1+mx(ht(r->l),ht(r->r));
    int b=bal(r);
    if(b>1 && k<r->l->k) return rRot(r);
    if(b<-1 && k>r->r->k) return lRot(r);
    if(b>1 && k>r->l->k) {r->l=lRot(r->l); return rRot(r);}
    if(b<-1 && k<r->r->k) {r->r=rRot(r->r); return lRot(r);}
    return r;
}
void in(struct node* r)
{
    if(r){in(r->l);printf("%d ",r->k);in(r->r);}
}
int tH(struct node* r)
{
    if(!r) return 0;
    int lh=tH(r->l),rh=tH(r->r);
    return (lh>rh?lh:rh)+1;
}
int main()
{
    int n,k;
    struct node *bst=NULL,*avl=NULL;
    printf("Enter number of elements:");
    scanf("%d",&n);
    printf("Enter %d elements:\n",n);
    for(int i=0;i<n;i++)
    {
        scanf("%d",&k);
        bst=insBST(bst,k);
        avl=insAVL(avl,k);
    }
    printf("\nBST Inorder: ");in(bst);
    printf("\nBST Height: %d",tH(bst));
    printf("\n\nAVL Inorder: ");in(avl);
    printf("\nAVL Height: %d\n",tH(avl));
    return 0;
}
