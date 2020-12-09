import pygame as pg
import sys
import math
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
        self.wall_list = []
        self.virtual_world = Grid(GRIDWIDTH, GRIDHEIGHT)
        self.arrows = {}
        self.arrow_img = pg.transform.scale(self.arrow_img, (64,64))
        for dir in [(1, 0), (0, 1), (-1, 0), (0, -1)]:
            self.arrows[dir] = pg.transform.rotate(self.arrow_img, vec(dir).angle_to(vec(1, 0)))

        self.goal = vec(0,0)
        self.start = vec(0,0)

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
        #self.wall_list = wall_list
        self.start_location = start_location

        #initialize all variables and do all the setup for a new game
        self.all_sprites = pg.sprite.Group()
        self.walls = pg.sprite.Group()
        self.trashs = pg.sprite.Group()
        #self.arrows = pg.sprite.Group()

        for tile_object in self.map.tmxdata.objects:
            obj_center = vec(tile_object.x + tile_object.width/2,
                             tile_object.y + tile_object.height/2)
            if tile_object.name == 'Robot':
                self.player = Player(self, obj_center.x, obj_center.y)
                self.start_location.append((obj_center.x, obj_center.y))
            if tile_object.name == 'Trash':
                self.trash_list.append([tile_object.x, tile_object.y])
                #print("After if statemetn", self.trash_list)
                self.trash = Trash(self, tile_object.x, tile_object.y)
            if tile_object.name == 'Wall':
                Obstacle(self, tile_object.x, tile_object.y,
                        tile_object.width, tile_object.height)

                # Since wall should be recognized as Tile Location.
                self.wall_list.append((int(tile_object.x // 64), int(tile_object.y // 64) ))

        print(self.wall_list)
        #Track the element of trash's locations.
        self.num_elm = len(trash_list)

        #Pass the trash_list, element number, and start_location
        TrashObj(self.trash_list, self.num_elm, self.start_location)

        self.camera = Camera(self.map.width, self.map.height)
        #Very Important : To Check what is robot is acutally colliding with
        self.draw_debug = False

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

        #Collision between the robot and the trashs
        hits = pg.sprite.spritecollide(self.player, self.trashs, False, collide_hit_rect)
        for hit in hits:
            hit.health -= 1
            hit.vel = vec(0,0)

            #When you hit the trash, you need to get rid of that list.
            for i in range(len(hit.position_list)-1):
                if hit.position_list[i][0] == hit.pos.x:
                    hit.position_list.pop(i)
        #find the start and goal location based on tile number.
        self.start = finding_tile(self.start_location[0][0], self.start_location[0][1])
        #print(self.start)
        self.goal = finding_tile(self.trash_list[0][0], self.trash_list[0][1])
        #print(self.goal)
        self.path = breadth_first_search(self.virtual_world, self.goal, self.start)

    def draw(self):
        self.path = breadth_first_search(self.virtual_world, self.goal, self.start)
        current = self.start + self.path[vec2int(self.start)]
        # Setting for FPS, so that the game flows well
        pg.display.set_caption("{:.2f}".format(self.clock.get_fps()))
        self.screen.blit(self.map_img, self.camera.apply_rect(self.map_rect))

        # while current != self.goal:
        #
        #     x = current.x * TILESIZE + TILESIZE / 2
        #     y = current.y * TILESIZE + TILESIZE / 2
        #     #print(int(self.current.x), int(self.current.y))
        #     #print(self.path[(int(self.current.x), int(self.current.y))])
        #     #print(self.path[vec2int(finding_tile(self.current.x, self.current.y))])
        #     img = self.arrows[vec2int(self.path[(int(current.x), int(current.y))])]
        #     img = img.get_rect(center=(x, y))
        #     self.screen.blit(self.screen, img)
        #     current = current + self.path[vec2int(current)]
        self.route = []
        for sprite in self.all_sprites:
            self.screen.blit(sprite.image, self.camera.apply(sprite))

            if self.draw_debug:
                pg.draw.rect(self.screen, BLACK, self.camera.apply_rect(sprite.hit_rect))

        if self.draw_debug:
            for wall in self.walls:
                pg.draw.rect(self.screen, BLACK, self.camera.apply_rect(wall.rect), 1)

        while current != self.goal:

            x = current.x * TILESIZE + TILESIZE / 2
            y = current.y * TILESIZE + TILESIZE / 2
            #print(int(self.current.x), int(self.current.y))
            #print(self.path[(int(self.current.x), int(self.current.y))])
            #print(self.path[vec2int(finding_tile(self.current.x, self.current.y))])
            self.img = self.arrows[vec2int(self.path[(int(current.x), int(current.y))])]
            self.r = self.img.get_rect(center=(x, y))
            self.screen.blit(self.img, self.r)
            #print(vec2int(self.path[(int(current.x), int(current.y))]))
            current = current + self.path[vec2int(current)]

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

            #find the start and goal location based on tile number.
            #self.start = finding_tile(self.start_location[0][0], self.start_location[0][1])
            #print(self.start)
            #self.goal = finding_tile(self.trash_list[0][0], self.trash_list[0][1])
            #print(self.goal)
            #self.path = breadth_first_search(self.virtual_world, self.goal, self.start)
            #print(self.path)


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
