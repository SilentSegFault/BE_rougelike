local level32 = Entity:New({
	components = {
		transform = { size = { width = 1920, height = 1080 } },
		tilemapRender = { tilemap = "level31" },
	},
})

function level32:OnCreate()
	CanLeaveLevel3_2 = false
end

function level32:OnStart()
	SpawnEntity("WallHorizontal", 1920 / 2, 100, 0)
	SpawnEntity("WallHorizontal", 1920 / 2, 1080 - 30, 0)
	SpawnEntity("WallVertical", 70, 1080 / 2, 0)
	SpawnEntity("WallVertical", 1920 - 70, 1080 / 2, 0)

	playerID = SpawnEntity("Player", LastPlayerPos.x, LastPlayerPos.y, 0)

	local ent = Ecs:GetEntity(playerID)
	local playerX, playerY = GetEntityPos(ent)
	local holderID = SpawnEntity("WeaponHolder", playerX, playerY, 0)
	local weaponID = SpawnEntity("Weapon", playerX + 50, playerY, 0)
	SetEntityParent(weaponID, holderID)
	SetEntityParent(holderID, playerID)

	ent.holder = holderID
	ent.weapon = weaponID

	local doorID = SpawnEntity("Level32Door", 1920 / 2, 1080 - 60, 0)
	FlipDown(Ecs:GetEntity(doorID))

	SpawnEntity("Enemy1", 200, 200, 0)
	SpawnEntity("Enemy1", 100, 300, 0)

	SpawnEntity("Enemy1", 1920 - 250, 200, 0)
	SpawnEntity("Enemy1", 1920 - 150, 300, 0)

	SpawnEntity("Enemy2", 1920 / 2 - 300, 600, 0)
	SpawnEntity("Enemy2", 1920 / 2 + 300, 600, 0)

	SpawnEntity("Enemy2", 300, 1080 - 300, 0)
	SpawnEntity("Enemy2", 1920 - 350, 1080 - 300, 0)
end

function level32:OnUpdate(deltaTime)
	if EntitiesToKill <= 0 and RoomsToClear > 0 then
		CanLeaveLevel3_2 = true
		RoomsToClear = RoomsToClear - 1
	end
end

return level32
