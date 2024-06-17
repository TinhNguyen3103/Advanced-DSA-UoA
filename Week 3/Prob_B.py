class Segment_tree:
    def __init__(self, n_) -> None:
        self.n = 1        
        while self.n < n_:
            self.n = self.n * 2
        self.D = [2**31 - 1 for i in range(2*self.n-1)]

        self.lazy = [None for i in range(2*self.n-1)]

    def update(self, a, b, k, l, r, x):
        self.lazy_evaluate(k)
        if r <= a or b <= l:
            return 
                
        if a <= l and r <= b:
            self.lazy[k] = x
        else:        
            self.update(a, b, k*2+1, l, (l+r)//2, x)
            self.update(a, b, k*2+2, (l+r)//2, r, x)
            self.D[k] = min(self.D[2*k+1], self.D[2*k+2])
        self.lazy_evaluate(k)

    def make_update(self, a, b, x):
        self.update(a, b+1, 0, 0, self.n, x)

    # def find(self, i):
    #     self.lazy_evaluate(i + self.n - 1)
    #     return self.D[i + self.n - 1]

    def findMin(self, a, b):
        return self.query(a, b+1, 0, 0, self.n)

    def query(self, a, b, k, l, r):
        if r <= a or b <= l:
            return 2**31 - 1
        
        self.lazy_evaluate(k)

        if a <= l and r <= b:
            return self.D[k]
        
        vl = self.query(a, b, k*2+1, l, (l+r)//2)
        vr = self.query(a, b, k*2+2, (l+r)//2, r)
        return min(vl, vr)
    
    def lazy_evaluate(self, k):
        if self.lazy[k] == None:
            return
        self.D[k] = self.lazy[k]
        if k < self.n-1:
            self.lazy[2*k+1] = self.lazy[k]
            self.lazy[2*k+2] = self.lazy[k]
        self.lazy[k] = None

if __name__ == "__main__":
    n, q = [int(z) for z in input().split()]
    ST = Segment_tree(n)

    for i in range(q):       
        querry = [int(z) for z in input().split()]
        if len(querry) == 4:
            ST.make_update(querry[1], querry[2], querry[3])
        else:
            print(ST.findMin(querry[1], querry[1]))