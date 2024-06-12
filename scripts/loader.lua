package.path = package.path .. ";../../scripts/?.lua"


Entity = require("entity")
Ecs = require("ecs")
Player = require("player")
StartButton = require("start_button")
QuitButton = require("quit_button")
StartLabel = require("start_label")
QuitLabel = require("quit_label")
StartMenu = require("start_menu")
GameTitleLabel = require("gametitle_label")

Level1 = require("level1")
Char1 = require("char1")
Char1Desk = require("char1_desk")
Char1Label = require("char1_label")
WeaponHolder = require("weapon_holder")
Weapon = require("weapon")
PlayerBullet = require("player_bullet")

WallHorizontal = require("wall_horizontal")
WallVertical = require("wall_vertical")
Level1Door = require("level1_door")

Level21 = require("level2_1")
Door = require("door")
Enemy1 = require("enemy1")
Level21Corridor = require("level2_1_corridor")
Level21Door = require("level2_1_door")

Level22 = require("level2_2")
Level22Corridor = require("level2_2_corridor")
Level22Door = require("level2_2_door")
Level22BossDoor = require("level2_2_boss_door")

Level31 = require("level3_1")
Level31Door = require("level3_1_door")

Level32 = require("level3_2")
Level32Door = require("level3_2_door")

Level33 = require("level3_3")
Boss = require("boss")
Chest = require("chest")
Enemy2 = require("enemy2")
EnemyProjectile = require("enemy_projectile")

LostLabel = require("lost_label")
Bench = require("bench")
Plants = require("plants")
Desk = require("desk")
Char2 = require("char2")
Char3 = require("char3")
Char4 = require("char4")
Char2Label = require("char2_label")

Enemy3 = require("enemy3")
Shotgun = require("Shotgun")
Ak47 = require("Ak47")
Enemy4 = require("enemy4")
Explosion = require("explosion")

--Floor2 
Level1Floor2 = require("floor2/level1")
Level2Floor2 = require("floor2/level2")
Level1Florr2Corridor = require("floor2/level1corridor")
Level2Floor2Corridor = require("floor2/level2corridor")
Level1Florr2Door = require("floor2/level1door")
Level1Floor2Room1 = require("floor2/room1")
Level1Floor2Room1Door =require("floor2/room1door")