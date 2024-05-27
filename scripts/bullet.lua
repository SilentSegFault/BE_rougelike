Bullet = Entity:New({
	size = { width = 15, height = 15 },
	render = { sprite = "bullet", drawLayer = 0 },
	stats = { health = 0, speed = 300 },
})

function Bullet:OnUpdate(deltaTime)
	local rot = GetEntityRotation(self)
	MoveEntity(self, self.stats.speed * deltaTime * math.cos(rot), self.stats.speed * deltaTime * math.sin(rot))
end
