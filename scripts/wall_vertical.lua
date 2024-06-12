local wall_vertical = Entity:New({
	components = {
		transform = { size = { width = 50, height = 1080 } },
		collider = { width = 50, height = 1080, collisionLayer = 10 },
	},
	tags = { "wall" },
})

return wall_vertical
