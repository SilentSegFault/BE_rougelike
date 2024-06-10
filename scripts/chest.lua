local chest = Entity:New({
	components = {
		transform = { size = { width = 140, height = 140 } },
		animator = { animation = "chestClosed" },
	},
})

chest.desiredY = 0
chest.timeToLive = 5
chest.spawned = false

function chest:OnCreate()
	self.desiredY = RandomRange(200, 800)
end

function chest:OnUpdate(deltaTime)
	local x, y = GetEntityPos(self)

	if y < self.desiredY then
		MoveEntity(self, 0, 300 * deltaTime)
	else
		PlayAnimationOnce(self, "chestOpening", 0)
		self.timeToLive = self.timeToLive - deltaTime
	end

	if not self.spawned and AnimationFinished(self) then
		SpawnEntity("Enemy2", x, y, 0)
		self.spawned = true
	end

	if self.timeToLive <= 0 then
		DestroyEntity(self)
	end
end

return chest
