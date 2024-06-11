local level1 = Entity:New({
	components = {
		transform = { size = { width = 1920, height = 1080 } },
		tilemapRender = { tilemap = "basement" },
	},
})

function level1:OnCreate()
	CanAccesLevel2 = false
	EntitiesToKill = 0

  PlayerHealth = 5
  PlayerGun = nil
end

function level1:OnStart()
	SpawnEntity("WallHorizontal", 1920 / 2, 100, 0)
	SpawnEntity("WallHorizontal", 1920 / 2, 1080 - 70, 0)
	SpawnEntity("WallVertical", 70, 1080 / 2, 0)
	SpawnEntity("WallVertical", 1920 - 70, 1080 / 2, 0)
	SpawnEntity("Level1Door", 1920 / 2, 150, 0)
	SpawnEntity("Char1", 1500, 800, 0)
	SpawnEntity("Char1Desk", 1420, 820, 0)
	playerID = SpawnEntity("Player", 1300, 300, 0)
	for i = 1, 4, 1 do 
	 for j = 1, 3 , 1 do 
		--SpawnEntity("Desk", i * 300, 200 + j * 200, 0)
	 end
	end

  SpawnEntity("Enemy4", 400, 400, 0)
  SpawnEntity("Enemy4", 1400, 500, 0)
  SpawnEntity("Enemy4", 400, 600, 0)
  SpawnEntity("Enemy4", 1400, 700, 0)
  SpawnEntity("Enemy4", 400, 800, 0)
  SpawnEntity("Enemy4", 1400, 800, 0)

  SpawnEntity("Enemy3", 1400, 500, 0)
  SpawnEntity("Enemy3", 1400, 700, 0)
  SpawnEntity("Enemy3", 1400, 900, 0)
end

return level1
