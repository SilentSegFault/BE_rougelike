local start_menu = Entity:New({
	components = {
		transform = { size = { width = 1920, height = 1080 } },
		tilemapRender = { tilemap = "startmenu" },
	},
})

return start_menu
