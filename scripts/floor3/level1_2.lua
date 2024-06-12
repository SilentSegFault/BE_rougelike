local level12 = Entity:New({
	components = {
		transform = { size = { width = 1920, height = 1080 } },
		tilemapRender = { tilemap = "floor3Level12" },
	},
})

function level12:OnCreate()
	CanLeaveLevel1_2 = false
  CanAccesLevel2_2 = false
  EntitiesToKill = 0
end

function level12:OnStart()
  SpawnEntity("WallHorizontal", 1920 / 2, 100, 0)
	SpawnEntity("WallHorizontal", 1920 / 2, 1080 - 30, 0)
	SpawnEntity("WallVertical", 20, 1080 / 2, 0)
	SpawnEntity("WallVertical", 1920 - 70, 1080 / 2, 0)

	SpawnEntity("Level12Floor3Corridor", 60, 1080 / 2, 0)
	SpawnEntity("Level12Floor3Door", 1920 / 3, 150, 0)
	SpawnEntity("Level12Floor3BossDoor", 2 * 1920 / 3, 150, 0)

	playerID = SpawnEntity("Player", LastPlayerPos.x, LastPlayerPos.y, 0)

	local ent = Ecs:GetEntity(playerID)
	local playerX, playerY = GetEntityPos(ent)
	local holderID = SpawnEntity("WeaponHolder", playerX, playerY, 0)
	weaponID = SpawnEntity(PlayerGun, playerX + 50, playerY, 0)
	SetEntityParent(weaponID, holderID)
	SetEntityParent(holderID, playerID)

	ent.holder = holderID
	ent.weapon = weaponID


end

function level12:OnUpdate(deltaTime)
	if EntitiesToKill <= 0 then
		CanLeaveLevel1_2 = true
    CanAccesLevel2_2 = true
	end
end


return level12


