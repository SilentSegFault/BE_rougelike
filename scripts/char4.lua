local char4 = Entity:New({
	components = {
		transform = { size = { width = 120, height = 120 } },
		spriteRender = { sprite = "char4" },
		collider = { width = 50, height = 100, collisionLayer = 10 },
	},
	tags = { "wall" },
})

return char4
