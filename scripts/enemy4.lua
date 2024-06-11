local enemy4 = Entity:New({
  components = {
    transform = { size = { width = 100, height = 100 } },
    animator = { animation = "enemy4Walk" },
    collider = { width = 70, height = 140, collisionLayer = 6 },
  },
  tags = { "enemy" },
  health = 5,
  speed = 400,
  isMoving = true
})

function enemy4:OnCreate()
  EntitiesToKill = EntitiesToKill + 1
end

function enemy4:OnUpdate(deltaTime)
	if self.health <= 0 then
		EntitiesToKill = EntitiesToKill - 1
		DestroyEntity(self)
		return
	end

	local player = Ecs:GetEntity(playerID)
	local targetX, targetY = GetEntityPos(player)
	local posX, posY = GetEntityPos(self)

  local dist = math.sqrt((targetX - posX) * (targetX - posX) + (targetY - posY) * (targetY - posY))

  if dist < 100 then
    self.isMoving = false
    PlayAnimationOnce(self, "enemy4Boom", 0)
  end

  if not self.isMoving then
    if AnimationFinished(self) then
      SpawnEntity("Explosion", posX, posY, 0)
      if dist < 150 then
        local player = Ecs:GetEntity(playerID)
        player.health = player.health - 3
        PlayerHealth = player.health
      end
      DestroyEntity(self)
    end
    return
  end

	local dirX = targetX - posX
	local dirY = targetY - posY

	local len = math.sqrt(dirX * dirX + dirY * dirY)

	local velX = (dirX / len) * self.speed * deltaTime
	local velY = (dirY / len) * self.speed * deltaTime

	MoveEntity(self, velX, velY)
	self.lastMove = { x = velX, y = velY }
end

return enemy4
