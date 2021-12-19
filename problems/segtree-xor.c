#include <stdio.h>
#include <stdlib.h>

typedef struct node node;
struct node{
    int val;
    int tl, tr;
    node *left, *right;
    node* parent;
};

node* new_node(int l, int r, node* parent){
    node* n = (node*)malloc(sizeof(node));
    n->tl = l;
    n->tr = r;
    n->parent = parent;
    n->left = NULL;
    n->right = NULL;
    return n;
}
void delete_node(node* n){
    if(n == NULL)
        return;
    delete_node(n->left);
    delete_node(n->right);

    free(n);
}

node* build(int a[], int l, int r, node* p, node* leaves[]){
    if(l == r){
        node* n = new_node(l, l, p);
        n->val = a[l];
        leaves[l] = n;
        return n;
    }
    else{
        int m = (r+l)/2;
        node* n = new_node(l, r, p);
        n->parent = p;
        n->left = build(a, l, m, n, leaves);
        n->right = build(a, m+1, r, n, leaves);

        n->val = n->left->val ^ n->right->val;

        return n;
    }
}

void update(int id, int val, node* leaves[]){
    node* t = leaves[id];
    t->val = val;
    t = t->parent;

    while(t != NULL){
        t->val = t->left->val ^ t->right->val;
        t = t->parent;
    }
}

int querry(node* n, int l, int r){
    if(l <= n->tl &&  r >= n->tr)
        return n->val;
    if(n->tr < l || r < n->tl)    
        return 0;

    int b = querry(n->left, l, r); 
    int a = querry(n->right, l, r); 
    return a ^ b;
}

int main(){
    int n, m;
    scanf("%d%d", &n, &m);

    int size = 1;
    do {
        size *= 2;
    } while(size < n);

    int* a = (int*)calloc(size, sizeof(int));
    for(int i = 0; i < n; i++)
        scanf("%d", a+i);
    
    node** leaves = (node**)calloc(size, sizeof(node*));
    node* root = build(a, 0, size-1, NULL, leaves);

    for(int i = 0; i < m; i++){
        int code, p1, p2;
        scanf("%d%d%d", &code, &p1, &p2);
        if(code == 1)
            printf("%d\n", querry(root, p1, p2));
        else
            update(p1, p2, leaves);
    }

    delete_node(root);
    free(a);
    free(leaves);
    return 0;
}