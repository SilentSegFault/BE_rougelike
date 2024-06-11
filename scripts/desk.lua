local desk = Entity:New({
	components = {
		transform = { size = { width = 120, height = 240 } },
		spriteRender = { sprite = "desk" },
		collider = { width = 60, height = 120, collisionLayer = 10 },
	},
	tags = { "wall" },
	visited = false,
})

return desk