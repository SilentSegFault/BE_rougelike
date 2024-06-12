local bench = Entity:New({
	components = {
		transform = { size = { width = 360, height = 180 } },
		collider = { width = 200, height = 60, collisionLayer = 10 },
		spriteRender = { sprite = "bench" },
	},
	tags = { "wall" },
})

return bench