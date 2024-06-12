local door = Entity:New({
	components = {
		transform = { size = { width = 120, height = 60 } },
		collider = { width = 120, height = 60, collisionLayer = 10 },
		spriteRender = { sprite = "door" },
	},
	tags = { "door" },
})

return door
