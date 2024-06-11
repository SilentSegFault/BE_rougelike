local enemy1 = Entity:New({
	components = {
		transform = { size = { width = 160, height = 160 } },
		animator = { animation = "enemy1" },
		collider = { width = 70, height = 140, collisionLayer = 6 },
	},
	tags = { "enemy" },
})

enemy1.health = 4
enemy1.attackTimer = 0
enemy1.timeToAttack = 1
enemy1.lastMove = { x = 0, y = 0 }
enemy1.timeToStart = 0.5

function enemy1:OnCreate()
	EntitiesToKill = EntitiesToKill + 1
end

function enemy1:OnUpdate(deltaTime)
	if self.health <= 0 then
		EntitiesToKill = EntitiesToKill - 1
		DestroyEntity(self)
		return
	end

	if self.timeToStart > 0 then
		self.timeToStart = self.timeToStart - deltaTime
		return
	end

	if self.attackTimer > 0 then
		self.attackTimer = self.attackTimer - deltaTime
	end

	local player = Ecs:GetEntity(playerID)
	local targetX, targetY = GetEntityPos(player)
	local posX, posY = GetEntityPos(self)

	local dirX = targetX - posX
	local dirY = targetY - posY

	local len = math.sqrt(dirX * dirX + dirY * dirY)

	local velX = (dirX / len) * 350 * deltaTime
	local velY = (dirY / len) * 350 * deltaTime

	MoveEntity(self, velX, velY)
	self.lastMove = { x = velX, y = velY }
end

function enemy1:OnCollision(ent)
	if ent:HasTag("player") then
		MoveEntity(self, -self.lastMove.x, -self.lastMove.y)
		if self.attackTimer <= 0 then
			ent.health = ent.health - 1
      PlayerHealth = PlayerHealth - 1
			self.attackTimer = self.timeToAttack
			print(ent.health)
		end
	end
end

return enemy1
