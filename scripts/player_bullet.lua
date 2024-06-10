local player_bulllet = Entity:New({
	components = {
		transform = { size = { width = 30, height = 30 } },
		spriteRender = { sprite = "projectile" },
		collider = { width = 20, height = 20, collisionLayer = 8 },
	},
	timeToLive = 5,
})

function player_bulllet:OnUpdate(deltaTime)
	if self.timeToLive <= 0 then
		DestroyEntity(self)
	end

	self.timeToLive = self.timeToLive - deltaTime

	local rot = GetEntityRotation(self)
	local x = math.cos(rot)
	local y = math.sin(rot)

	MoveEntity(self, x * 900 * deltaTime, y * 900 * deltaTime)
end

function player_bulllet:OnCollision(ent)
	if ent:HasTag("wall") then
		DestroyEntity(self)
	elseif ent:HasTag("enemy") then
		ent.health = ent.health - 1
		DestroyEntity(self)
	end
end

return player_bulllet
