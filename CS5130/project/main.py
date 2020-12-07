import pygame as pg
import sys
from os import path
from random import uniform

from settings import *
from sprites import *
from tile_map import *
from path_algorithm import *
from utility import *

class Game:
    def __init__(self):
        pg.init()
        self.screen = pg.display.set_mode((WIDTH, HEIGHT))
        pg.display.set_caption(TITLE)
        self.clock = pg.time.Clock()
        self.load_data()

    # Loading data
    def load_data(self):
        game_folder = path.dirname(__file__)
        img_folder = path.join(game_folder, 'image')
        map_folder = path.join(game_folder, 'maps')
        self.map = TiledMap(path.join(map_folder, 'map.tmx'))
        self.map_img = self.map.make_map()
        self.map_rect = self.map_img.get_rect()
        self.player_img = pg.image.load(path.join(img_folder, PLAYER_IMG)).convert_alpha()
        self.trash_img = pg.image.load(path.join(img_folder, TRASH_IMG)).convert_alpha()

        # Direction module
        self.arrow_img = pg.image.load(path.join(img_folder, ARROW_IMG)).convert_alpha()

    def new(self):
        trash_list = []
        wall_list = []
        start_location = []

        self.trash_list = trash_list
        self.wall_list = wall_list
        self.start_location = start_location
        #initialize all variables and do all the setup for a new game
        self.all_sprites = pg.sprite.Group()
        self.walls = pg.sprite.Group()
        self.trashs = pg.sprite.Group()

        for tile_object in self.map.tmxdata.objects:
            obj_center = vec(tile_object.x + tile_object.width/2,
                             tile_object.y + tile_object.height/2)
            if tile_object.name == 'Robot':
                self.player = Player(self, obj_center.x, obj_center.y)
                self.start_location.append([obj_center.x, obj_center.y])

            if tile_object.name == 'Trash':
                Trash(self, tile_object.x, tile_object.y)
                self.trash_list.append([tile_object.x, tile_object.y])

            if tile_object.name == 'Wall':
                Obstacle(self, tile_object.x, tile_object.y,
                        tile_object.width, tile_object.height)
                wall_list = []
                self.wall_list.append([tile_object.x, tile_object.y])

        ########################################################################
        print("Wall locatiion is : ", self.wall_list)
        print("Trash Location is : ", self.trash_list)

        self.num_elm = len(trash_list)
        # Sorting the trash list, so that you can calculate
        self.sort_trash_list = sortVec(self.trash_list, self.num_elm, self.start_location)
        print("Sorted Wall locatiion is : ", self.sort_trash_list)

        self.camera = Camera(self.map.width, self.map.height)
        #Very Important : To Check what is robot is acutally colliding with
        self.draw_debug = False
        print("start location of robot is : ", start_location)

    ## Run the Game
    def run(self):
        # game loop - set self.pl aying = False to end the game
        self.playing = True
        while self.playing:
            self.dt = self.clock.tick(FPS) / 1000
            self.events()
            self.update()
            self.draw()

    def quit(self):
        pg.quit()
        sys.exit()

    def update(self):
        # update portion of the game loop
        self.all_sprites.update()
        self.camera.update(self.player)

        #Collision the robot and the trashs
        hits = pg.sprite.spritecollide(self.player, self.trashs, False, collide_hit_rect)
        for hit in hits:
            hit.health -= 1
            hit.vel = vec(0,0)

    def draw(self):
        # Setting for FPS, so that the game flows well
        pg.display.set_caption("{:.2f}".format(self.clock.get_fps()))
        #self.screen.fill(BGCOLOR)
        self.screen.blit(self.map_img, self.camera.apply_rect(self.map_rect))
        #self.draw_grid()
        for sprite in self.all_sprites:
            self.screen.blit(sprite.image, self.camera.apply(sprite))
            if isinstance(sprite, Trash):
                sprite.draw_health()

            if self.draw_debug:
                pg.draw.rect(self.screen, BLACK, self.camera.apply_rect(sprite.hit_rect))

        if self.draw_debug:
            for wall in self.walls:
                pg.draw.rect(self.screen, BLACK, self.camera.apply_rect(wall.rect), 1)

        pg.display.flip()

    def events(self):
        # catch all events here
        for event in pg.event.get():
            if event.type == pg.QUIT:
                self.quit()
            if event.type == pg.KEYDOWN:
                if event.key == pg.K_ESCAPE:
                    self.quit()
                if event.key == pg.K_h:
                    self.draw_debug = not self.draw_debug

            ## How to select the closest one

    def show_start_screen(self):
        pass

    def show_go_screen(self):
        self.screen.fill(BLACK)
        self.draw_text("Game Over", self.title_font, 100, RED,
                       WIDTH/2, HEIGHT/2, align = "center")

        self.draw_text("Press a key to start", self.title_font, 75, WHITE,
                       WIDTH/2, HEIGHT * 3/4, align = "center")

        pg.display.flip()
        self.wait_for_key()

    def wait_for_key(self):
        pg.event.wait()
        waiting = True
        while wating:
            self.clock.tick(FPS)
            for even in pg.event.get():
                if event.type == pg.QUIT:
                    waiting = False
                    self.quit()
                if event.type == pg.KEYUP:
                    waiting = False

# create the game object
g = Game()
g.show_start_screen()
while True:
    g.new()
    g.run()
    g.show_go_screen()
