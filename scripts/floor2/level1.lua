local level1f2 = Entity:New({
	components = {
		transform = { size = { width = 1920, height = 1080 } },
		tilemapRender = { tilemap = "level41" },
	},
})

function level1f2:OnCreate()
	EntitiesToKill = 0
end

function level1f2:OnStart()
	SpawnEntity("WallHorizontal", 1920 / 2, 100, 0)
	SpawnEntity("WallHorizontal", 1920 / 2, 1080 - 70, 0)
	SpawnEntity("WallVertical", 70, 1080 / 2, 0)
	SpawnEntity("WallVertical", 1920 - 20, 1080 / 2, 0)
	SpawnEntity("Level1Florr2Corridor",1920 - 60, 1080 / 2, 0)
	playerID = SpawnEntity("Player", LastPlayerPos.x, LastPlayerPos.y, 0)
	local doorID = SpawnEntity("Door", 1920 / 2, 1080 - 60, 0)
	FlipDown(Ecs:GetEntity(doorID))
	SpawnEntity("Level1Florr2Door",1920 / 2, 150, 0)

	local ent = Ecs:GetEntity(playerID)
	local playerX, playerY = GetEntityPos(ent)
	local holderID = SpawnEntity("WeaponHolder", playerX, playerY, 0)
	weaponID = SpawnEntity(PlayerGun, playerX + 50, playerY, 0)
	SetEntityParent(weaponID, holderID)
	SetEntityParent(holderID, playerID)

	ent.holder = holderID
	ent.weapon = weaponID

	
end

function level1f2:OnUpdate(deltaTime)
	if EntitiesToKill <= 0 then
		CanAccesLevel2Floor2 = true
		
	end
end


return level1f2
