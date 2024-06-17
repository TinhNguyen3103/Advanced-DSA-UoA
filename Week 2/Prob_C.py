class Disjoint_Set:
    def __init__(self, n) -> None:
        self.p = [[0,0] for i in range(n)] 
        self.rank = [0 for i in range(n)] 

    def makeSet(self, x):
        self.p[x] = [x,0]
        self.rank[x] = 0

    def union(self, x, y, z):
        root_x, diff_x = self.findSet(x, 0)
        root_y, diff_y = self.findSet(y, 0)

        if root_x != root_y:
            diff = diff_y - diff_x + z
            inc = 1
        else:
            diff = 0
            inc = 0

        if self.rank[root_x] > self.rank[root_y]:
            self.p[root_y] = [root_x, -diff]
        else:
            self.p[root_x] = [root_y, diff]
            if self.rank[root_x] == self.rank[root_y]:
                self.rank[root_y] += inc


    def findSet(self, x, diff):
        if x != self.p[x][0]:
            diff += self.p[x][1]
            x, diff = self.findSet(self.p[x][0], diff)
        return x, diff
    
    def getDiff(self, x, y):
        root_x, diff_x = self.findSet(x, 0)
        root_y, diff_y = self.findSet(y, 0)
        # print(root_x, root_y)
        if root_x == root_y:
            print(-diff_y + diff_x)
        else:
            print('?')

if __name__ == "__main__":
    n, q = [int(z) for z in input().split()]
    DS = Disjoint_Set(n)
    for i in range(n):
        DS.makeSet(i)
    for i in range(q):
        querry = [int(z) for z in input().split()]
        if len(querry) == 4:
            DS.union(querry[1], querry[2], querry[3])
            # print(DS.p)
        else:
            DS.getDiff(querry[1], querry[2])
    # print(DS.p)