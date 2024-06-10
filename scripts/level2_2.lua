local level2_2 = Entity:New({
	components = {
		transform = { size = { width = 1920, height = 1080 } },
		tilemapRender = { tilemap = "level22" },
	},
})

function level2_2:OnCreate()
	CanAccesLevel2_1 = true
	CanAccesLevel3_2 = false
	CanAccesLevel3_3 = false
end

function level2_2:OnStart()
	SpawnEntity("WallHorizontal", 1920 / 2, 100, 0)
	SpawnEntity("WallHorizontal", 1920 / 2, 1080 - 70, 0)
	SpawnEntity("WallVertical", 30, 1080 / 2, 0)
	SpawnEntity("WallVertical", 1920 - 70, 1080 / 2, 0)

	SpawnEntity("Level22Corridor", 60, 1080 / 2, 0)
	SpawnEntity("Level22Door", 1920 / 3, 150, 0)
	SpawnEntity("Level22BossDoor", 2 * 1920 / 3, 150, 0)

	SpawnEntity("Door", 1920 - 67, 1080 / 2, math.pi / 2)

	playerID = SpawnEntity("Player", LastPlayerPos.x, LastPlayerPos.y, 0)

	local ent = Ecs:GetEntity(playerID)
	local playerX, playerY = GetEntityPos(ent)
	local holderID = SpawnEntity("WeaponHolder", playerX, playerY, 0)
	local weaponID = SpawnEntity("Weapon", playerX + 50, playerY, 0)
	SetEntityParent(weaponID, holderID)
	SetEntityParent(holderID, playerID)

	ent.holder = holderID
	ent.weapon = weaponID

	SpawnEntity("Enemy2", 1920 / 3, 300, 0)
	SpawnEntity("Enemy2", 2 * 1920 / 3, 300, 0)
	SpawnEntity("Enemy2", 1920 - 300, 1080 / 2, 0)
end

function level2_2:OnUpdate(deltaTime)
	if EntitiesToKill <= 0 and RoomsToClear <= 1 then
		CanAccesLevel3_2 = true
	end

	if EntitiesToKill <= 0 and RoomsToClear <= 0 then
		CanAccesLevel3_3 = true
	end
end

return level2_2
