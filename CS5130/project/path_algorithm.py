import pygame as pg
import collections
from settings import *
from collections import deque

vec = pg.math.Vector2
#pg.init()
#screen = pg.display.set_mode((VIRTUAL_WORLD_WIDTH, VIRTUAL_WORLD_HEIGHT))
#screen = pg.display.set_mode(())

class Grid:
    def __init__(self, width, height):
        self.width = GRIDWIDTH
        self.height = GRIDHEIGHT
        self.walls = [(31, 17), (39, 7), (33, 13), (31, 7), (26, 7), (17, 9),
        (29, 24), (35, 21), (14, 10), (12, 10), (19, 10), (16, 20), (10, 20),
        (4, 15), (4, 22), (17, 10), (5, 28), (11, 26), (32, 24), (32, 26),
        (38, 26), (38, 24), (32, 17), (33, 17), (33, 16), (34, 16), (35, 16),
        (36, 16), (37, 16), (38, 16), (39, 16), (34, 17), (35, 17), (36, 17),
        (37, 17), (38, 17), (39, 17), (39, 18), (39, 19), (39, 20), (39, 21),
        (39, 22), (34, 23), (35, 23), (36, 23), (36, 24), (35, 24), (34, 24),
        (34, 25), (35, 25), (36, 25), (36, 26), (35, 26), (34, 26), (34, 27),
        (35, 27), (36, 27), (27, 30), (26, 30), (28, 30), (29, 30), (30, 30),
        (30, 29), (31, 29), (32, 29), (33, 29), (37, 29), (36, 29), (35, 29),
        (34, 29), (38, 29), (39, 29), (40, 29), (40, 27), (40, 28), (40, 23),
        (40, 24), (40, 25), (40, 26), (30, 24), (30, 25), (30, 26), (30, 27),
        (30, 28), (27, 26), (28, 26), (29, 26), (29, 27), (28, 27), (27, 27),
        (22, 30), (23, 30), (24, 30), (25, 30), (21, 30), (20, 30), (19, 30),
        (18, 30), (17, 30), (17, 29), (17, 28), (17, 27), (17, 26), (17, 25),
        (17, 24), (18, 25), (18, 26), (18, 27), (18, 28), (18, 23), (17, 23),
        (16, 23), (15, 23), (14, 23), (13, 23), (12, 23), (11, 23), (10, 23),
        (9, 23), (9, 24), (9, 25), (10, 25), (11, 25), (12, 25), (12, 26),
        (12, 27), (12, 28), (12, 29), (12, 30), (11, 30), (10, 30), (9, 30),
        (8, 30), (7, 30), (6, 30), (5, 30), (11, 29), (10, 29), (4, 30),
        (3, 30), (2, 26), (2, 27), (2, 28), (2, 29), (2, 30), (3, 27),
        (3, 28), (3, 29), (2, 25), (3, 25), (4, 25), (5, 25), (6, 24), (6, 25),
        (6, 23), (5, 23), (4, 23), (3, 23), (3, 22), (3, 21), (3, 20), (12, 20),
        (13, 20), (14, 20), (15, 22), (14, 22), (13, 22), (12, 22), (11, 22),
        (3, 18), (3, 19), (3, 15), (3, 16), (3, 17), (3, 14), (4, 14), (5, 14),
        (6, 14), (7, 14), (8, 14), (9, 14), (10, 14), (11, 14), (12, 14),
        (13, 14), (14, 14), (6, 11), (7, 11), (8, 11), (26, 20), (26, 21),
        (26, 22), (21, 23), (22, 23), (23, 23), (24, 23), (25, 23), (26, 23),
        (27, 23), (28, 23), (29, 23), (30, 23), (25, 20), (25, 21), (25, 22),
        (25, 19), (26, 19), (40, 22), (40, 21), (40, 20), (40, 19), (40, 18),
        (40, 17), (40, 16), (40, 15), (40, 14), (40, 13), (40, 12), (40, 11),
        (40, 10), (40, 9), (40, 8), (40, 7), (32, 7), (32, 8), (32, 9), (32, 10),
        (32, 11), (32, 12), (32, 13), (33, 7), (34, 7), (35, 7), (30, 7),
        (29, 7), (28, 7), (27, 7), (25, 7), (25, 8), (25, 9), (25, 10), (25, 11),
        (25, 12), (25, 13), (25, 14), (24, 14), (23, 14), (22, 14), (21, 14),
        (20, 14), (19, 14), (18, 14), (17, 14), (19, 7), (19, 8), (20, 7),
        (21, 7), (22, 7), (23, 7), (24, 7), (20, 9), (20, 10), (20, 11), (20, 12),
        (20, 13), (11, 9), (11, 10), (11, 11), (11, 12), (11, 13), (12, 9),
        (13, 9), (14, 9), (12, 5), (12, 6), (12, 7), (12, 8), (13, 4), (14, 4),
        (17, 4), (18, 4), (19, 4), (20, 4), (21, 4), (22, 4), (23, 4), (24, 4),
        (25, 4), (26, 4), (27, 4), (28, 4), (29, 4), (30, 4), (31, 4), (32, 4),
        (33, 4), (34, 4), (35, 4)]

        self.connections = [vec(1, 0), vec(-1, 0), vec(0, 1), vec(0, -1)]
        #self.connections += [vec(1, 1), vec(-1, 1), vec(1, -1), vec(-1, -1)]
    
    # Bounded By Map
    def is_bounds(self, node):
        #print(node.x, node.y)
        node.x = node.x
        node.y = node.y
        return 0 <= node.x  < self.width and 0 <= node.y  < self.height
    
    # Whether it's passable by the wall
    def passable(self, node):
        #print(self.walls)
        return node not in self.walls

    def find_neighbors(self, node):
        #print(node)
        neighbors = [node + connection for connection in self.connections]
        #print(list(neighbors))
        if(node.x + node.y) % 2:
            neighbors.reverse()
        #Filter out whether the location can go outside of the world (in_bound)
        #Filter out whether the location doesn't collide with walls.
        neighbors = filter(self.is_bounds, neighbors)
        neighbors = filter(self.passable, neighbors)
        #print(list(neighbors))
        return neighbors

# Converting something like the list () inside of the dict
def vec2int(v):
    return (int(v.x), int(v.y))

def breadth_first_search(graph, start, end):
    frontier = deque()
    frontier.append(start)

    path = {}
    path[vec2int(start)] = None
    while len(frontier) > 0:

        current = frontier.popleft()
        #print(current)
        if current == end:
            break
        for next in graph.find_neighbors(current):
            if vec2int(next) not in path:
                #print(frontier)
                frontier.append(next)
                #print(frontier)
                path[vec2int(next)] = current - next
    return path
