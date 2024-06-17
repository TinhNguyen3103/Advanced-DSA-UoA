class Segment_tree:
    def __init__(self, n_) -> None:
        self.n = 1        
        while self.n < n_:
            self.n = self.n * 2
        self.D = [2**31 - 1 for i in range(2*self.n-1)]
        # print(self.D)

    def update(self, k, x):
        k += self.n - 1
        self.D[k] = x
        while k > 0:
            k = (k-1)//2
            self.D[k] = min(self.D[2*k+1], self.D[2*k+2])

    def findMin(self, a, b):
        return self.query(a, b+1, 0, 0, self.n)

    def query(self, a, b, k, l, r):
        if r <= a or b <= l:
            return 2**31 - 1
        if a <= l and r <= b:
            return self.D[k]
        
        vl = self.query(a, b, k*2+1, l, (l+r)//2)
        vr = self.query(a, b, k*2+2, (l+r)//2, r)
        return min(vl, vr)

if __name__ == "__main__":
    n, q = [int(z) for z in input().split()]
    ST = Segment_tree(n)

    for i in range(q):
        com, x, y = [int(z) for z in input().split()]
        if com == 0:
            ST.update(x,y)
        else:
            print(ST.findMin(x,y))