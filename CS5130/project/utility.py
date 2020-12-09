import math
import pygame as pg
from settings import *

vec = pg.math.Vector2

# p is reference point, Vec has all the list of trash location
def sortVec(vec, n, p):
    vp = []
    for i in range(n):
        dist = pow((p[0][0] - vec[i][0]), 2) + pow((p[0][1] - vec[i][1]), 2)
        vp.append([vec[i][0], vec[i][1]])
    vp.sort()
    return vp

# To find the tile
def finding_tile(one, two):
    one = int(math.floor(one / TILESIZE))
    two = int(math.floor(two / TILESIZE))
    return vec(one, two)

class TrashObj:
    def __init__(self, trash_list, num_elm, start_location):
        self.trash_list = trash_list
        self.num_elm = num_elm
        self.start_location = start_location

        ########################################################################
        print("Trash Location is : ", self.trash_list)
        print("start location of robot is : ", self.start_location)

        sorted_list = sortVec(self.trash_list, self.num_elm, self.start_location)
        print("Sorted Trash Location :", sorted_list)

    def get_trash_list(self):
        return self.trash_list

    def get_sort_trash_list(self):
        sorted_list = sortVec(self.trash_list, self.num_elm, self.start_location)
        print(sorted_list)

    def get_numElm(self):
        return self.num_elm

    def get_started_list(self):
        return self.start_location
