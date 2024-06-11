local char3 = Entity:New({
	components = {
		transform = { size = { width = 120, height = 120 } },
		spriteRender = { sprite = "char3" },
		collider = { width = 50, height = 100, collisionLayer = 10 },
	},
	tags = { "wall" },
})

return char3
