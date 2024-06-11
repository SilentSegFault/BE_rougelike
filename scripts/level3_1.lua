local level31 = Entity:New({
	components = {
		transform = { size = { width = 1920, height = 1080 } },
		tilemapRender = { tilemap = "level31" },
	},
})

function level31:OnCreate()
	CanLeaveLevel3_1 = false
end

function level31:OnStart()
	SpawnEntity("WallHorizontal", 1920 / 2, 100, 0)
	SpawnEntity("WallHorizontal", 1920 / 2, 1080 - 30, 0)
	SpawnEntity("WallVertical", 70, 1080 / 2, 0)
	SpawnEntity("WallVertical", 1920 - 70, 1080 / 2, 0)

	playerID = SpawnEntity("Player", LastPlayerPos.x, LastPlayerPos.y, 0)

	local ent = Ecs:GetEntity(playerID)
	local playerX, playerY = GetEntityPos(ent)
	local holderID = SpawnEntity("WeaponHolder", playerX, playerY, 0)
	weaponID = SpawnEntity(PlayerGun, playerX + 50, playerY, 0)
	SetEntityParent(weaponID, holderID)
	SetEntityParent(holderID, playerID)

	ent.holder = holderID
	ent.weapon = weaponID

	local doorID = SpawnEntity("Level31Door", 1920 / 2, 1080 - 60, 0)
	FlipDown(Ecs:GetEntity(doorID))

	SpawnEntity("Char2", 1920 -150,200,0)

	SpawnEntity("Enemy1", 1920 - 350, 200, 0)
	SpawnEntity("Enemy1", 1920 - 350, 400, 0)
	SpawnEntity("Enemy1", 1920 - 150, 400, 0)

	SpawnEntity("Enemy2", 400, 400, 0)
	SpawnEntity("Enemy2", 500, 700, 0)
	SpawnEntity("Enemy2", 1500, 600, 0)
end

function level31:OnUpdate(deltaTime)
	if EntitiesToKill <= 0 and RoomsToClear > 1 then
		CanLeaveLevel3_1 = true
		RoomsToClear = RoomsToClear - 1
	end
end

return level31
