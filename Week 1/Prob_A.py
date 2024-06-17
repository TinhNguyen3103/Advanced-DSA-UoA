from math import sqrt

def circle_intersect(cx1, cy1, r1, cx2, cy2, r2):
    d = sqrt((cx1 - cx2)**2 + (cy1 - cy2)**2)
    if d > r1 + r2:
        print(4)
    elif d == r1 + r2:
        print(3)
    elif d > abs(r1-r2) and d < r1 + r2:
        print(2)
    elif d == abs(r1 - r2):
        print(1)
    else:
        print(0)

cx1, cy1, r1  = [float(x) for x in input().split()]
cx2, cy2, r2  = [float(x) for x in input().split()]

circle_intersect(cx1, cy1, r1, cx2, cy2, r2)