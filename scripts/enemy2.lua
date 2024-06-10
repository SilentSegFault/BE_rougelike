local enemy2 = Entity:New({
	components = {
		transform = { size = { width = 150, height = 150 } },
		animator = { animation = "boss" },
		collider = { width = 70, height = 140, collisionLayer = 6 },
	},
	tags = { "enemy" },
	targetPos = { x = 0, y = 0 },
	health = 5,
	timeToShoot = 1,
})

function enemy2:OnCreate()
	EntitiesToKill = EntitiesToKill + 1
	self.targetPos.x = RandomRange(200, 1700)
	self.targetPos.y = RandomRange(200, 700)
end

function enemy2:OnUpdate(deltaTime)
	if self.health <= 0 then
		EntitiesToKill = EntitiesToKill - 1
		DestroyEntity(self)
		return
	end

	local x, y = GetEntityPos(self)
	self.timeToShoot = self.timeToShoot - deltaTime

	local dist =
		math.sqrt((self.targetPos.x - x) * (self.targetPos.x - x) + (self.targetPos.y - y) * (self.targetPos.y - y))

	if dist < 10 then
		if self.timeToShoot > 0 then
			self.targetPos = { x = RandomRange(200, 1700), y = RandomRange(200, 700) }
		else
			self.timeToShoot = 1
			local px, py = GetEntityPos(Ecs:GetEntity(playerID))
			local bulletID = SpawnEntity("EnemyProjectile", x, y, 0)
			EntityLookAt(Ecs:GetEntity(bulletID), px, py)
		end
	end

	local dirX = self.targetPos.x - x
	local dirY = self.targetPos.y - y
	local len = math.sqrt(dirX * dirX + dirY * dirY)

	local velX = dirX / len * 300 * deltaTime
	local velY = dirY / len * 300 * deltaTime

	MoveEntity(self, velX, velY)
end

return enemy2
