class Disjoint_Set:
    def __init__(self, n) -> None:
        self.p = [0 for i in range(n)] 
        self.rank = [0 for i in range(n)] 

    def makeSet(self, x):
        self.p[x] = x
        self.rank[x] = 0

    def union(self, x, y):
        self.link(self.findSet(x), self.findSet(y))

    def link(self, x, y):
        if self.rank[x] > self.rank[y]:
            self.p[y] = x
        else:
            self.p[x] = y
            if self.rank[x] == self.rank[y]:
                self.rank[y] = self.rank[y] + 1

    def findSet(self, x):
        if x != self.p[x]:
            self.p[x] = self.findSet(self.p[x])
        return self.p[x]

    def same(self, x, y):
        if self.findSet(x) == self.findSet(y):
            print(1)
        else: 
            print(0)

if __name__ == "__main__":
    n, q = [int(z) for z in input().split()]
    DS = Disjoint_Set(n)
    for i in range(n):
        DS.makeSet(i)
    for i in range(q):
        com, x, y = [int(z) for z in input().split()]
        if com == 0:
            DS.union(x, y)
        else:
            DS.same(x, y)