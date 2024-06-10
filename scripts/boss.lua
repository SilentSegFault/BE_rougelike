local boss = Entity:New({
	components = {
		transform = { size = { width = 350, height = 350 } },
		animator = { animation = "boss" },
		collider = { width = 70, height = 140, collisionLayer = 6 },
	},
	tags = { "enemy" },
	targetPos = { x = 0, y = 0 },
})

boss.health = 100

boss.timeToSummon = 8
boss.nextSummon = 8
boss.summonTime = 1

boss.timeToShoot = 3

function boss:OnCreate()
	self.targetPos = { x = RandomRange(200, 1700), y = RandomRange(200, 700) }
	EntitiesToKill = EntitiesToKill + 1
end

function boss:OnUpdate(deltaTime)
	if self.health <= 0 then
		EntitiesToKill = EntitiesToKill - 1
		DestroyEntity(self)
		return
	end

	local x, y = GetEntityPos(self)

	local dist =
		math.sqrt((self.targetPos.x - x) * (self.targetPos.x - x) + (self.targetPos.y - y) * (self.targetPos.y - y))

	if dist < 10 then
		self.targetPos = { x = RandomRange(200, 1700), y = RandomRange(200, 700) }
	end

	if self.nextSummon <= 0 then
		PlayAnimation(self, "bossSummon", 0)
		if self.summonTime <= 0 then
			self.nextSummon = self.timeToSummon
			self.summonTime = 1

			for i = 1, math.random(2, 5), 1 do
				SpawnEntity("Chest", RandomRange(200, 1700), 0, 0)
			end
		end
		self.summonTime = self.summonTime - deltaTime
	else
		PlayAnimation(self, "boss", 0)
		if self.timeToShoot < 0 then
			self.timeToShoot = 3
			for i = 0, 360, 36 do
				local theta = math.rad(i)
				SpawnEntity("EnemyProjectile", x, y, theta)
			end
		else
			local dirX = self.targetPos.x - x
			local dirY = self.targetPos.y - y
			local len = math.sqrt(dirX * dirX + dirY * dirY)

			local velX = dirX / len * 100 * deltaTime
			local velY = dirY / len * 100 * deltaTime

			MoveEntity(self, velX, velY)
		end
	end
	self.nextSummon = self.nextSummon - deltaTime
	self.timeToShoot = self.timeToShoot - deltaTime
end

return boss
