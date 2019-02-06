#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <cfloat>
#include <bits/stdc++.h>
 
#define MAX_DIM 3

using namespace std;

struct kd_node_t{
    double x[MAX_DIM];
    kd_node_t *left, *right;
};

int compare (const void * a, const void * b)
{
  return ( *(double*)a - *(double*)b );
}
 
inline double dist(kd_node_t *a, kd_node_t *b, int dim){
    double t, d = 0;
    while (dim--) {
        t = a->x[dim] - b->x[dim];
        d += t * t;
    }
    return d;
}

inline void swap(kd_node_t *x, kd_node_t *y) {
    double tmp[MAX_DIM];
    memcpy(tmp,  x->x, sizeof(tmp));
    memcpy(x->x, y->x, sizeof(tmp));
    memcpy(y->x, tmp,  sizeof(tmp));
}
  
/* see quickselect method */
kd_node_t* find_median(kd_node_t *start, kd_node_t *end, int idx){
    if (end <= start) return NULL;
    if (end == start + 1)
        return start;
 
    kd_node_t *p, *store, *md = start + (end - start) / 2;
    double pivot;
    while (1) {
        pivot = md->x[idx];
 
        swap(md, end - 1);
        for (store = p = start; p < end; p++) {
            if (p->x[idx] < pivot) {
                if (p != store)
                    swap(p, store);
                store++;
            }
        }
        swap(store, end - 1);
 
        /* median has duplicate values */
        if (store->x[idx] == md->x[idx])
            return md;
 
        if (store > md) end = store;
        else        start = store;
    }
}
 
kd_node_t* make_tree(kd_node_t *t, int len, int i, int dim){
    kd_node_t *n;
 
    if (!len) return 0;
 
    if ((n = find_median(t, t + len, i))) {
        i = (i + 1) % dim;
        n->left  = make_tree(t, n - t, i, dim);
        n->right = make_tree(n + 1, t + len - (n + 1), i, dim);
    }
    return n;
}
 
void orderArray(double *a){
    double temp;
    int n = sizeof(a)/sizeof(a[0]);
    
    sort(a, a+n);
}

/* global variable, so sue me */
int visited;
 
void nearest(kd_node_t *root, kd_node_t *nd, int i, int dim, kd_node_t **best, double best_dist[]){

    double d, dx, dx2;
 
    if (!root) return;
    d = dist(root, nd, dim);
    dx = root->x[i] - nd->x[i];
    dx2 = dx * dx;
    visited ++;
 
    if (!*best || d < best_dist[4]) {

        best_dist[4] = d;
        *best = root;

        qsort(best_dist, 5, sizeof(double), compare);
    }
 
    /* if chance of exact match is high */
    if (!best_dist[4]) return;
 
    if (++i >= dim) i = 0;
 
    nearest(dx > 0 ? root->left : root->right, nd, i, dim, best, best_dist);
    if (dx2 >= best_dist[4]) return;
    nearest(dx > 0 ? root->right : root->left, nd, i, dim, best, best_dist);
}

int main(void)
{

    int n, m, sum;

    cin >> n;

    kd_node_t wp[n];

    for(int i=0; i<n; i++){
        cin >> wp[i].x[0];
        cin >> wp[i].x[1];
    }

    cin >> m;

    kd_node_t testNode[m];

    for(int i=0; i<m; i++){
        cin >> testNode[i].x[0];
        cin >> testNode[i].x[1];
    }

    kd_node_t *root, *found;
    double best_dist[5];
    double init [5] = {1000000000,1000000000,1000000000,1000000000,1000000000};
 
    root = make_tree(wp, sizeof(wp) / sizeof(wp[1]), 0, 2);
    
    for(int i=0; i<m; i++){
        visited = 0;
        found = 0;
        std::copy(init, init+5, best_dist);
        
        nearest(root, &testNode[i], 0, 2, &found, best_dist);
     
        //sum += sqrt(best_dist);

        double sum_dist = 0.0;
        for(int j = 0; j < 5; j++)
        	sum_dist += sqrt(best_dist[j]);

        printf("%.2f\n", sum_dist);
    }
    return 0;
}