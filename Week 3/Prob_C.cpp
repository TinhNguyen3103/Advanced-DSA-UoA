#include <bits/stdc++.h>

const int INF = std::pow(2,31)-1;

class segmentTree {
public:
    int n, *D, *lazy;

    segmentTree(int n_){
        this->n = 1;
        while (n < n_){
            n = n * 2;
        }

        D = new int[2*n-1];
        lazy = new int[2*n-1];

        for (int i = 0; i<2*n-1; i++){
            D[i] = INF;
            lazy[i] = -INF;
        }
    }

    void lazy_evaluate(int k){
        if (lazy[k] == -INF)
            return;
        D[k] = lazy[k];
        if (k < n - 1){
            lazy[2*k+1] = lazy[k];
            lazy[2*k+2] = lazy[k];
        }
        lazy[k] = -INF;
    }

    void make_update(int a, int b, int x){
        update(a, b+1, 0, 0, n, x);
    }

    void update(int a, int b, int k, int l, int r, int x){
        lazy_evaluate(k);
        if (r <= a || b <= l){
            return;
        }
        if (a <= l && r <= b){
            lazy[k] = x;
        }
        else {
            update(a, b, 2*k+1, l, int((l+r)/2), x);
            update(a, b, 2*k+2, int((l+r)/2), r, x);
            D[k] = std::min(D[2*k+1], D[2*k+2]);
        }
        lazy_evaluate(k);
    }

    int findMin(int a, int b){
        return query(a, b+1, 0, 0, n);
    }

    int query(int a, int b, int k, int l, int r){
        if (r <= a || b <= l)
            return INF;
        
        lazy_evaluate(k);

        if (a <= l && r <= b)
            return D[k]; 
        
        int vl = query(a, b, 2*k+1, l, int((l+r)/2));
        int vr = query(a, b, 2*k+2, int((l+r)/2), r);

        return std::min(vl, vr);
    }
};

int main(){
    int n, q;
    std::cin >> n >> q;

    segmentTree ST(n);

    int quer, s, t, x;
    for(int j=0; j<q; j++){
        std::cin >> quer ;
        if (quer == 0){
            std::cin >> s >> t >> x;
            ST.make_update(s, t, x);
        } else if (quer == 1){
            std::cin >> s >> t;
            int val = ST.findMin(s, t);
            std::cout << val << std::endl;
        }
    }

    return 0;
}