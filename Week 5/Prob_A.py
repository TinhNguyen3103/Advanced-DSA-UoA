from operator import itemgetter
from collections import defaultdict
import sys
sys.setrecursionlimit(1000000)

class Graph:
    def __init__(self, V):
        self.V = V
        self.graph = defaultdict(list)
        self.prenum = [-1 for i in range(self.V)]
        self.parent = [-1 for i in range(self.V)]
        self.lowest = [-1 for i in range(self.V)]    
        self.visited = [False for i in range(self.V)]   

    def addEdge(self, u, v):
        self.graph[u].append(v)
        self.graph[v].append(u)
    
    def dfs(self, u, p, t):
        self.prenum[u] = t
        self.lowest[u] = t
        t += 1
        self.visited[u] = True

        for v in self.graph[u]:
            if not self.visited[v]:
                self.parent[v] = u
                self.dfs(v, u, t)
                self.lowest[u] = min(self.lowest[u], self.lowest[v])
            elif v != p:
                self.lowest[u] = min(self.lowest[u], self.prenum[v])
 
    def art_points(self):
        t = 1
        self.dfs(0, -1, t)

        AP = []
        nc = 0
        for u in range(1, self.V):
            p = self.parent[u]
            if p == 0:
                nc += 1
            elif self.prenum[p] <= self.lowest[u]:
                # if p not in AP:
                AP.append(p)
        
        if nc > 1:
            AP.append(0)
        
        return sorted(set(AP))
            
if __name__ == "__main__":
    V, E = [int(x) for x in input().split()]
    g = Graph(V)
    for i in range(E):
        s, t = [int(x) for x in input().split()]
        g.addEdge(s, t)
    
    AP = g.art_points()
    # AP = sorted(AP)
    # last = -1
    # for i in AP:
    #     if i != last:
    #         print(i)
    #     last = i

    for i in AP:
        print(i)