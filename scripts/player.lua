local player = Entity:New({
	components = {
		transform = { size = { width = 120, height = 120 } },
		animator = { animation = "playerIdle" },
		collider = { width = 50, height = 100, collisionLayer = 0 },
	},
	tags = { "player" },
	holder = nil,
	weapon = nil,
	health = 5,
})

function player:OnCreate()
	self.lastMove = { x = 0, y = 0 }
end

function player:OnUpdate(deltaTime)
	if self.health <= 0 then
		LoadScene("EndMenu")
	end

	local moveVec = { x = 0, y = 0 }
	if KeyPressed("key_w") then
		moveVec.y = moveVec.y - 1
	end
	if KeyPressed("key_s") then
		moveVec.y = moveVec.y + 1
	end
	if KeyPressed("key_a") then
		moveVec.x = moveVec.x - 1
	end
	if KeyPressed("key_d") then
		moveVec.x = moveVec.x + 1
	end

	if self.holder ~= nil then
		local holderEnt = Ecs:GetEntity(self.holder)
		local mouseX, mouseY = GetMousePos()
		EntityLookAt(holderEnt, mouseX, mouseY)

		local x, y = GetEntityPos(self)

		if mouseX < x then
			FlipDown(Ecs:GetEntity(self.weapon))
		else
			FlipUp(Ecs:GetEntity(self.weapon))
		end
	end

	if self.weapon ~= nil and KeyDown("mouse_left") then
		local x, y = GetEntityPos(Ecs:GetEntity(self.weapon))
		local rot = GetEntityRotation(Ecs:GetEntity(self.weapon))
		SpawnEntity("PlayerBullet", x, y, rot)
	end

	if moveVec.x == 0 and moveVec.y == 0 then
		return
	end

	local len = math.sqrt(moveVec.x * moveVec.x + moveVec.y * moveVec.y)
	moveVec.x = moveVec.x / len
	moveVec.y = moveVec.y / len
	moveVec.x = moveVec.x * 400 * deltaTime
	moveVec.y = moveVec.y * 400 * deltaTime
	MoveEntity(self, moveVec.x, moveVec.y)
	self.lastMove = moveVec
end

function player:OnCollision(ent)
	if ent:HasTag("movable") then
		MoveEntity(self, -self.lastMove.x * 0.5, -self.lastMove.y * 0.5)
		MoveEntity(ent, self.lastMove.x * 0.5, self.lastMove.y * 0.5)
	elseif ent:HasTag("wall") then
		MoveEntity(self, -self.lastMove.x, -self.lastMove.y)
	end
end

return player
