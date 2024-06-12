local char2 = Entity:New({
	components = {
		transform = { size = { width = 120, height = 120 } },
		spriteRender = { sprite = "char2" },
		collider = { width = 50, height = 100, collisionLayer = 10 },
	},
	tags = { "wall" },
    visited = false,
})

function char2:OnCollision(ent)
	if ent:HasTag("player") and not self.visited then
		self.visited = true
		SpawnEntity("Char2Label", 1920 -500, 120, 0)
	end
end
return char2
