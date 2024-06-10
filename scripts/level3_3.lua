local level33 = Entity:New({
	components = {
		transform = { size = { width = 1920, height = 1080 } },
		tilemapRender = { tilemap = "level33" },
	},
})

function level33:OnCreate()
	CanLeaveLevel3_3 = false
end

function level33:OnStart()
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

	local doorID = SpawnEntity("Level33Door", 1920 / 2, 1080 - 60, 0)
	FlipDown(Ecs:GetEntity(doorID))

	SpawnEntity("Boss", 1920 / 2, 1080 / 2, 0)
end

function level33:OnUpdate(deltaTime)
	if EntitiesToKill <= 0 then
		CanLeaveLevel3_3 = true
	end
end

return level33
