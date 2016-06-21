/*
 *  Template for segment tree with range update (lazy)
 *  Author: asdoc
 *  Date: 5nd Jan, 2016
 *  Template Details:
 *  1. Define the node of the segment tree, structure name is seg_node
 *  2. Define the create_leaf function for your custom tree
 *  3. Define the zero() function, which states how your null seg_node will look like
 *  4. Define merge() function, which combines result of two nodes and returns parent node
 *  5. Define propogate_lazy() function to transfer lazy variables from index to
 *     it's children and update the value of lazy variable at index
 *  6. Update lazy_update(): Change function parameters if necessary
 *  7. Update lazy variable of node at index
 *
 * Tested on: https://www.hackerearth.com/code-monk-segment-tree-and-lazy-propagation/algorithm/monk-and-otakuland-1/
 */

#include <iostream>
#include <string.h>
using namespace std;

struct seg_node {
    // TODO 1: Define appropriate variables in this structure

    // default variable
    int left;
    int right;

    // local variable
    int cnt;

    // range update variable
    bool swap;
};

long long n, m, p[280000];
seg_node seg[800400];

seg_node create_leaf(int index) {
    // TODO 2: Code for creating the leaf node of index
    // N-indexed index
    seg_node to_ret;
    to_ret.left=index;
    to_ret.right=index;
    if(p[index-n]==1) {
        to_ret.cnt = 1;
    } else {
        to_ret.cnt = 0;
    }
    to_ret.swap = false;
    return to_ret;
}

inline seg_node zero() {
    // TODO 3: Write the function for zero value of seg_node
    seg_node to_ret;
    to_ret.cnt = 0;
    to_ret.swap = false;
    return to_ret;
}

inline seg_node merge(seg_node a, seg_node b) {
    // TODO 4: Write the merge function for merging two nodes into a parent node
    // Assumption: b.left = a.right + 1
    seg_node to_ret;
    to_ret.left = a.left;
    to_ret.right = b.right;

    to_ret.cnt = a.cnt + b.cnt;
    to_ret.swap = false;

    return to_ret;
}

inline void propogate_lazy(int index) {
    // TODO 5: Write a function to transfer lazy variables from index to
    // it's children and update the value of lazy variable at index
    if(index<n && seg[index].swap) {
        seg[2*index].swap^=true;
        seg[2*index+1].swap^=true;
    }
    if(seg[index].swap==true) {
        seg[index].cnt = (seg[index].right-seg[index].left+1-seg[index].cnt);
        seg[index].swap=false;
    }
}

// TODO 6: Change function parameters if necessary
void lazy_update(int index, int l, int r) {
    propogate_lazy(index);
    int cl = seg[index].left, cr = seg[index].right;
    if((cl < l && cr < l) || (cl > r && cr > r)) {
        // out of range
    } else if(l<=cl && r>=cr){
        // completely in range

        // TODO 7: Update the lazy variable of node at index
        seg[index].swap^=true;
        // END

        propogate_lazy(index);
    } else {
        int mid = (cl+cr)/2;
        if(r<=mid) {
            // not in range of right child
            lazy_update(2*index, l, r);
            propogate_lazy(2*index+1);
        } else if(l>=(mid+1)) {
            // not in range of left child
            propogate_lazy(2*index);
            lazy_update(2*index+1, l, r);
        } else {
            // in partial range of both children
            lazy_update(2*index, l, r);
            lazy_update(2*index+1, l, r);
        }
        seg[index] = merge(seg[2*index], seg[2*index+1]);
    }
}

seg_node query(int index, int l, int r) {
    // This function need not be changed
    propogate_lazy(index);
    int cl = seg[index].left, cr = seg[index].right;
    seg_node to_ret;
    if(index>=n) {
        if(l<=index && r>=index) {
            // leaf node, in range
            to_ret = seg[index];
        } else {
            // leaf node, not in range
            to_ret = zero();
        }
    } else {
        if((cl < l && cr < l) || (cl > r && cr > r)) {
            // out of range
            to_ret = zero();
        } else if(l<=cl && r>=cr){
            // completely in range
            to_ret = seg[index];
        } else {
            int mid = (cl+cr)/2;
            if(r<=mid) {
                // not in range of right child
                to_ret = query(2*index, l, r);
            } else if(l>=(mid+1)) {
                // not in range of left child
                to_ret = query(2*index+1, l, r);
            } else {
                // in partial range of both children
                seg_node a = query(2*index, l, r);
                seg_node b = query(2*index+1, l, r);
                to_ret = merge(a, b);
            }
        }
    }
    return to_ret;
}

void build() {
    // This function need not be changed
    for(int i=n;i<2*n;i++) {
        seg[i].left = i;
        seg[i].right = i;
        seg[i].swap = false;
	    if(p[i-n]==1) {
	        seg[i].cnt = 1;
	    } else {
	        seg[i].cnt = 0;
	    }
        // seg[i] = create_leaf(i);
    }
    for(int i=n-1;i>=1;i--) {
    	seg[i].cnt = seg[2*i].cnt + seg[2*i+1].cnt;
    	seg[i].left = seg[2*i].left;
    	seg[i].right = seg[2*i+1].right;
    	seg[i].swap = false;
        //seg[i] = merge(seg[2*i], seg[2*i+1]);
    }
}

void solve() {
    memset(p, 0, sizeof p);
    cin >> n >> m;
    n-=1;
    string s;
    cin >> s;
    for(int i=0;i<n;i++) {
        if(s[i]=='>') {
            p[i]=1;
        } else {
            p[i]=0;
        }
    }
    int nn = 1;
    while(nn<n) {
        nn*=2;
    }
    n=nn;
    build();
    while(m--) {
        int op, x, y;
        cin >> op >> x >> y;
        if(op==1) {
            lazy_update(1, n-1+x, n-1+y-1);
        } else {
            if(x>y) {
                int val = query(1, n-1+y, n-1+x-1).cnt;
                cout << val << "\n" ;
            } else {
                int val = query(1, n-1+x, n-1+y-1).cnt;
                cout << y - x - val << "\n" ;
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int t=1;
    while(t--) {
        solve();
    }
}
