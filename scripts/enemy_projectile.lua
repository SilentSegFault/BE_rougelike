local enemy_projectile = Entity:New({
	components = {
		transform = { size = { width = 50, height = 50 } },
		spriteRender = { sprite = "enemyProjectile", drawLayer = 0 },
		collider = { width = 20, height = 20, collisionLayer = 8 },
	},
	timeToLive = 7,
  speed = 400
})

function enemy_projectile:OnUpdate(deltaTime)
	if self.timeToLive <= 0 then
		DestroyEntity(self)
	end

	self.timeToLive = self.timeToLive - deltaTime

	local rot = GetEntityRotation(self)
	local x = math.cos(rot)
	local y = math.sin(rot)

	MoveEntity(self, x * self.speed * deltaTime, y * self.speed * deltaTime)
end

function enemy_projectile:OnCollision(ent)
	if ent:HasTag("wall") then
		DestroyEntity(self)
	elseif ent:HasTag("player") then
		ent.health = ent.health - 1
    PlayerHealth = PlayerHealth - 1
		DestroyEntity(self)
	end
end

return enemy_projectile
