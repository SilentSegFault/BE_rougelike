local char1 = Entity:New({
	components = {
		transform = { size = { width = 120, height = 120 } },
		animator = { animation = "char1Idle" },
		collider = { width = 50, height = 100, collisionLayer = 10 },
	},
	tags = { "wall" },
})

return char1
