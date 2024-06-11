local plants = Entity:New({
	components = {
		transform = { size = { width = 240, height = 120 } },
		collider = { width = 240, height = 100, collisionLayer = 10 },
		spriteRender = { sprite = "plants" },
	},
	tags = { "plants" },
})

return plants