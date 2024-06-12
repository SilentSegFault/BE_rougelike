local wall_horizontal = Entity:New({
	components = {
		transform = { size = { width = 1920, height = 50 } },
		collider = { width = 1920, height = 50, collisionLayer = 10 },
	},
	tags = { "wall" },
})

return wall_horizontal
