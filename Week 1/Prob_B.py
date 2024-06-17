from collections import defaultdict

class Graph:
    def __init__(self) -> None:
        
        self.graph = defaultdict(list)

    def addEdge(self, u, v):
        self.graph[u].append(v)

    def DFSUtil(self, v, visited, path):
        visited.add(v)
        path.add(v)
        for neighbour in self.graph[v]:
            if neighbour in path:
                print(1)
                quit()
            if neighbour not in visited:
                self.DFSUtil(neighbour, visited, path)
        path.remove(v)
        # print(visited, path)

    def DFS_cycle(self, v):
        visited = set()
        path = set()

        val = self.DFSUtil(v, visited, path)

if __name__ == "__main__":
    g = Graph()
    V, E = [int(x) for x in input().split()]
    for i in range(E):
        u, v = [int(x) for x in input().split()]
        g.addEdge(u, v)
    
    val = 0
    for i in range(V):
        g.DFS_cycle(i)
    print(0)