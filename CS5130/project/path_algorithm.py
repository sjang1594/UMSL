import pygame as pg
import collections
from collections import deque

vec = pg.math.Vector2

class SquareGrid:
    def __init__(self, width, height):
        self.width = width
        self.height = height
        self.walls = []
        self.connection = [vec(1, 0), vec(-1, 0), vec(0, 1), vec(0, -1)]

    def in_bounds(self, node):
        return 0 <= node.x < self.width and 0 <= node.y < self.height

    def passable(self, node):
        return node not in self.walls

    def find_neighbors(self, node):
        neighbors = [node + connection for connection in self.connections]
        if(node.x + node.y) % 2:
            neighbors.reverse()
        neighbors = filter(self.in_bounds, neighbors)
        neighbors = filter(self.passable, neighbors)
        #print(list(neighbors))
        return neighbors

    # def draw(self):
    #     for wall in self.walls:
    #         rect = pg.Rect(wall * TILESIZE, (TILESIZE, TILESIZE))
    #         pg.draw.rect(screen, LIGHTGRAY, rect)

def vec2int(v):
    return (int(v.x), int(v.y))

def breadth_first_search(graph, start, end):
    frontier = deque()
    frontier.append(start)
    path = {}
    path[vec2int(start)] = None
    while len(frontier) > 0:
        current = frontier.popleft()
        if current == end:
            break
        for next in graph.find_neighbors(current):
            if vec2int(next) not in path:
                frontier.append(next)
                path[vec2int(next)] = current - next
    return path
