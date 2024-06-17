def Post(inord):
    if len(inord) == 0:
        return
    root = predor.pop(0)
    for id in range(len(inord)):
        if inord[id] == root:
            Post(inord[:id])
            Post(inord[id+1:])
    postor.append(root)
    return


n = input()
predor = list(map(int, input().split()))
inord = list(map(int, input().split()))
postor = []
Post(inord)
print(*postor)