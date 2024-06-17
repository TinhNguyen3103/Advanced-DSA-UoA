from operator import itemgetter

class Graph:
    def __init__(self, V):
        self.edges = []
        self.V = V

    def addEdge(self, u, v, w):
        self.edges.append([u, v, w])
    
    def kruskal(self):
        MST = []
        sum_weight = 0

        # Sort the edges
        self.edges = sorted(self.edges, key=itemgetter(2))
        
        DS = Disjoint_Set(V)
        for i in range(V):
            DS.makeSet(i)
        
        for e in self.edges:
            u = e[0]
            v = e[1]
            
            if DS.findSet(u) != DS.findSet(v):
                # print(u, v)
                DS.union(u, v)
                MST.append(e)
                sum_weight += e[2]
        return sum_weight
            
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

if __name__ == "__main__":
    V, E = [int(x) for x in input().split()]
    g = Graph(V)
    for i in range(E):
        u, v, w = [int(x) for x in input().split()]
        g.addEdge(u, v, w)
    
    print(g.kruskal())