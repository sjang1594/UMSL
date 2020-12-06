import pygame as pg

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
        neighbors = filter(self.in_bounds, neighbors)
        neighbors = filter(self.passable, neighbors)
        #print(list(neighbors))
        return neighbors

    # def draw(self):
    #     for wall in self.walls:
    #         rect = pg.Rect(wall * TILESIZE, (TILESIZE, TILESIZE))
    #         pg.draw.rect(screen, LIGHTGRAY, rect)
