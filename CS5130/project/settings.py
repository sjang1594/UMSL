import pygame as pg


# Define Some Color Vector.
WHITE = (255, 255, 255)
BLACK = (0, 0, 0)
DARKGREY = (40, 40, 40)
LIGHTGREY = (100, 100, 100)
GREEN = (0, 255, 0)
RED = (255, 0, 0)
YELLOW = (255, 255, 0)

# game settings
WIDTH = 1024   # 16 * 64 or 32 * 32 or 64 * 16
HEIGHT = 768  # 16 * 48 or 32 * 24 or 64 * 12
FPS = 60
TITLE = "Cleaning Robots"
BGCOLOR = DARKGREY

#Tile Setting.
TILESIZE = 64
GRIDWIDTH = 40
GRIDHEIGHT = 30

VIRTUAL_WORLD_WIDTH = 2560
VIRTUAL_WORLD_HEIGHT = 1920

# Player Settings
PLAYER_SPEED = 300
PLAYER_ROT_SPEED = 250
PLAYER_IMG = 'robot.png'
PLAYER_HIT_RECT = pg.Rect(0, 0, 35, 35)

#Trash Settings
TRASH_IMG = 'trash.png'
TRASH_HIT_RECT = pg.Rect(0, 0, 35, 35)
#Kind of like health
TRASH_HEALTH = 1

#Arrow settings
ARROW_IMG = 'arrow.png'
