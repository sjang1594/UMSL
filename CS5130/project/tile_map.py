import pygame as pg
import pytmx
from settings import *

class Map:
    def __init__(self, filename):
        self.data = []
        with open(filename, 'rt') as f:
            for line in f:
                self.data.append(line.strip())

        #Tile Width
        self.tileWidth = len(self.data[0])
        self.tileHeight = len(self.data)

        #Map width and height
        self.width = self.tileWidth * TILESIZE
        self.height = self.tileHeight * TILESIZE

class TiledMap:
    def __init__(self, filename):
        tm = pytmx.load_pygame(filename, pixelalpha=True)
        self.width = tm.width * tm.tilewidth
        self.height = tm.height * tm.tileheight
        self.tmxdata = tm

    def render(self, surface):
        #Grab Certain Identifier
        ti = self.tmxdata.get_tile_image_by_gid
        for layer in self.tmxdata.visible_layers:
            if isinstance(layer, pytmx.TiledTileLayer):
                #Read Layers
                for x, y, grid, in layer:
                    tile = ti(grid)
                    if tile:
                        surface.blit(tile, (x * self.tmxdata.tilewidth,
                                            y * self.tmxdata.tileheight))

    def make_map(self):
        #Create a surface to draw a map on to
        temp_surface = pg.Surface((self.width, self.height))
        self.render(temp_surface)
        return temp_surface

class Camera:
    def __init__(self, width, height):
        self.camera = pg.Rect(0, 0, width, height)
        self.width = width
        self.height = height

    def apply(self, entity):
        return entity.rect.move(self.camera.topleft)

    def apply_rect(self, rect):
        return rect.move(self.camera.topleft)

    def update(self, target):
         x = -target.rect.x + int(WIDTH / 2)
         y = -target.rect.y + int(HEIGHT / 2)

         x = min(0, x)  # left
         y = min(0, y)  # top
         x = max(-(self.width - WIDTH), x)  # right
         y = max(-(self.height - HEIGHT), y)  # bottom
         self.camera = pg.Rect(x, y, self.width, self.height)
