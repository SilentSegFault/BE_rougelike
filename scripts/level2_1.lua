local level2_1 = Entity:New({
	components = {
		transform = { size = { width = 1920, height = 1080 } },
		tilemapRender = { tilemap = "level21" },
	},
})

function level2_1:OnCreate()
	CanAccesLevel2_2 = false
	CanAccesLevel3_1 = false
	RoomsToClear = 2
end

function level2_1:OnStart()
	SpawnEntity("WallHorizontal", 1920 / 2, 100, 0)
	SpawnEntity("WallHorizontal", 1920 / 2, 1080 - 70, 0)
	SpawnEntity("WallVertical", 70, 1080 / 2, 0)
	SpawnEntity("WallVertical", 1920 - 20, 1080 / 2, 0)
	SpawnEntity("Bench", 500 ,200 + 30,0)
	SpawnEntity("Bench", 150 ,1080 /2 + 40, -math.pi /2)
	SpawnEntity("Plants",1920 - 400, 200, 0)
	local doorID = SpawnEntity("Door", 1920 / 2, 1080 - 60, 0)
	FlipDown(Ecs:GetEntity(doorID))
	SpawnEntity("Level21Corridor", 1920 - 60, 1080 / 2, 0)
	SpawnEntity("Level21Door", 1920 / 2, 150, 0)
	playerID = SpawnEntity("Player", LastPlayerPos.x, LastPlayerPos.y, 0)

	local ent = Ecs:GetEntity(playerID)
	local playerX, playerY = GetEntityPos(ent)
	local holderID = SpawnEntity("WeaponHolder", playerX, playerY, 0)
	local weaponID = SpawnEntity("Weapon", playerX + 50, playerY, 0)
	SetEntityParent(weaponID, holderID)
	SetEntityParent(holderID, playerID)

	ent.holder = holderID
	ent.weapon = weaponID

	SpawnEntity("Enemy2", 200, 200, 0)
	SpawnEntity("Enemy2", 1920 - 200, 200, 0)
	SpawnEntity("Enemy1", 1920 / 2, 400, 0)
end

function level2_1:OnUpdate(deltaTime)
	if EntitiesToKill <= 0 then
		CanAccesLevel2_2 = true
		CanAccesLevel3_1 = true
	end
end

return level2_1
