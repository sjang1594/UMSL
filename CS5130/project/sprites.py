import pygame as pg
from settings import *
from tile_map import *

#Use Vector for Player
vec = pg.math.Vector2

def collide_with_walls(sprite, group, dir):
    if dir == 'x':
        hits = pg.sprite.spritecollide(sprite, group, False, collide_hit_rect)
        if hits:
            if hits[0].rect.centerx > sprite.hit_rect.centerx:
                sprite.pos.x = hits[0].rect.left - sprite.hit_rect.width / 2
            if hits[0].rect.centerx < sprite.hit_rect.centerx:
                sprite.pos.x = hits[0].rect.right + sprite.hit_rect.width / 2
            sprite.vel.x = 0
            sprite.hit_rect.centerx = sprite.pos.x
    if dir == 'y':
        hits = pg.sprite.spritecollide(sprite, group, False, collide_hit_rect)
        if hits:
            if hits[0].rect.centery > sprite.hit_rect.centery:
                sprite.pos.y = hits[0].rect.top - sprite.hit_rect.height / 2
            if hits[0].rect.centery < sprite.hit_rect.centery:
                sprite.pos.y = hits[0].rect.bottom + sprite.hit_rect.height / 2
            sprite.vel.y = 0
            sprite.hit_rect.centery = sprite.pos.y

class Player(pg.sprite.Sprite):
    def __init__(self, game, x, y):
        self.groups = game.all_sprites
        pg.sprite.Sprite.__init__(self, self.groups)
        self.game = game
        self.image = game.player_img
        self.rect = self.image.get_rect()

        #since the rectangle around the player changes, make it set box
        #around the player
        self.hit_rect = PLAYER_HIT_RECT
        self.hit_rect.center = self.rect.center

        #Define Player position and Velocity
        self.vel = vec(0,0)
        self.pos = vec(x, y)

        #Rotation
        self.rot = 0
        self.health = PLAYER_HEALTH

    def get_keys(self):
        #init the rotation and velocity
        self.rot_speed = 0
        self.vel = vec(0,0)
        keys = pg.key.get_pressed()

        #Left and Right movement
        if keys[pg.K_LEFT] or keys[pg.K_a]:
            self.rot_speed = PLAYER_ROT_SPEED
        if keys[pg.K_RIGHT] or keys[pg.K_d]:
            self.rot_speed = -PLAYER_ROT_SPEED

        #Up and Down movement
        if keys[pg.K_UP] or keys[pg.K_w]:
            self.vel = vec(PLAYER_SPEED,0).rotate(-self.rot)
        if keys[pg.K_DOWN] or keys[pg.K_s]:
            self.vel = vec(-PLAYER_SPEED / 2, 0).rotate(-self.rot)

        #diagnol movement
        #if self.vel.x != 0 and self.vel.y != 0:
        #    self.vel *= 0.7071

    def update(self):
        self.get_keys()
        #Update the rotation speed and position.
        self.rot = (self.rot + self.rot_speed * self.game.dt) % 360

        #Transform the robot image
        self.image = pg.transform.rotate(self.game.player_img, self.rot)

        #find the center of robot image
        self.rect = self.image.get_rect()
        self.rect.center = self.pos

        # Position equation for velocity
        self.pos += self.vel * self.game.dt

        #Update the center not the edge of robot and check the collision.
        self.hit_rect.centerx = self.pos.x
        collide_with_walls(self, self.game.walls, 'x')
        self.hit_rect.centery = self.pos.y
        collide_with_walls(self, self.game.walls, 'y')
        self.rect.center = self.hit_rect.center

class Trash(pg.sprite.Sprite):
    def __init__(self, game, x, y):
        self.groups = game.all_sprites, game.trashs
        pg.sprite.Sprite.__init__(self, self.groups)
        self.game = game
        self.image = game.trash_img
        self.rect = self.image.get_rect()
        self.hit_rect = TRASH_HIT_RECT.copy()
        self.hit_rect.center = self.rect.center
        self.pos = vec(x, y)
        self.vel = vec(0, 0)
        self.acc = vec(0, 0)
        self.rect.center =  self.pos
        self.rot = 0
        self.health = TRASH_HEALTH

    def update(self):
        self.rect.center = self.pos
        self.hit_rect.centerx = self.pos.x
        collide_with_walls(self, self.game.walls, 'x')
        self.hit_rect.centery = self.pos.y
        collide_with_walls(self, self.game.walls, 'y')
        self.rect.center = self.hit_rect.center

        if self.health <= 0 :
            self.kill()

    def draw_health(self):
        if self.health > 60:
            col = GREEN
        elif self.health > 30:
            col = YELLOW
        else:
            col = RED
        width = int(self.rect.width * self.health / TRASH_HEALTH)
        self.health_bar = pg.Rect(0, 0, width, 7)
        if self.health < TRASH_HEALTH:
            pg.draw.rect(self.image, col, self.health_bar)


class Obstacle(pg.sprite.Sprite):
    def __init__(self, game, x, y, w, h):
        self.groups = game.walls
        pg.sprite.Sprite.__init__(self, self.groups)
        self.game = game
        self.rect = pg.Rect(x, y, w, h)
        self.x = x
        self.y = y
        self.rect.x = x
        self.rect.y = y

class Arrow(pg.sprite.Sprite):
    def __init__(self, game, x, y):
        self.groups = game.all_sprites, game.arrows
        pg.sprite.Sprite.__init__(self, self.groups)
