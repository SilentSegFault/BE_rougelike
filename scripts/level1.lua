local level1 = Entity:New({
	components = {
		transform = { size = { width = 1920, height = 1080 } },
		tilemapRender = { tilemap = "basement" },
	},
})

function level1:OnCreate()
	CanAccesLevel2 = false
	EntitiesToKill = 0
end

function level1:OnStart()
	SpawnEntity("WallHorizontal", 1920 / 2, 100, 0)
	SpawnEntity("WallHorizontal", 1920 / 2, 1080 - 70, 0)
	SpawnEntity("WallVertical", 70, 1080 / 2, 0)
	SpawnEntity("WallVertical", 1920 - 70, 1080 / 2, 0)
	SpawnEntity("Level1Door", 1920 / 2, 150, 0)
	SpawnEntity("Char1", 1500, 800, 0)
	SpawnEntity("Char1Desk", 1420, 820, 0)
	SpawnEntity("Player", 300, 300, 0)
end

return level1
