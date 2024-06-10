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
Level33Door = require("level3_3_door")
Boss = require("boss")
Chest = require("chest")
Enemy2 = require("enemy2")
EnemyProjectile = require("enemy_projectile")

LostLabel = require("lost_label")
