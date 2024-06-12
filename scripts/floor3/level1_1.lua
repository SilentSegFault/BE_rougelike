local level11 = Entity:New({
	components = {
		transform = { size = { width = 1920, height = 1080 } },
		tilemapRender = { tilemap = "floor3Level11" },
	},
})

function level11:OnCreate()
	CanAccesLevel1_2 = false
	CanAccesLevel2_1 = false
  EntitiesToKill = 0
end

function level11:OnStart()
  SpawnEntity("WallHorizontal", 1920 / 2, 100, 0)
	SpawnEntity("WallHorizontal", 1920 / 2, 1080 - 30, 0)
	SpawnEntity("WallVertical", 70, 1080 / 2, 0)
	SpawnEntity("WallVertical", 1920 - 20, 1080 / 2, 0)
	SpawnEntity("Level11Floor3Corridor", 1920 - 60, 1080 / 2, 0)
	SpawnEntity("Level11Floor3Door", 1920 / 2, 150, 0)

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

function level11:OnUpdate(deltaTime)
	if EntitiesToKill <= 0 then
	  CanAccesLevel1_2 = true
	  CanAccesLevel2_1 = true
		RoomsToClear = RoomsToClear - 1
	end
end


return level11


