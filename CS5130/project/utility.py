import math


# p is reference point, Vec has all the list of trash location
def sortVec(vec, n, p):
    vp = []
    for i in range(n):

        dist = pow((p[0][0] - vec[i][0]), 2) + pow((p[0][1] - vec[i][1]), 2)
        vp.append([vec[i][0], vec[i][1]])

    vp.sort()
    return vp
