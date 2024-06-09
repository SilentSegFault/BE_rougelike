local player = Entity:New({
	components = {
		transform = { size = { width = 300, height = 300 } },
		animator = { animation = "PlayerIdle" },
		collider = { width = 30, height = 30 },
	},
})

function player:OnCreate()
	print("Created new player")
end

function player:OnUpdate(deltaTime)
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

	if moveVec.x > 0 then
		PlayAnimation(self, "PlayerMoveSide", 0)
	elseif moveVec.x < 0 then
		PlayAnimation(self, "PlayerMoveSide", 1)
	elseif moveVec.y > 0 then
		PlayAnimation(self, "PlayerMoveDown", 0)
	elseif moveVec.y < 0 then
		PlayAnimation(self, "PlayerMoveUp", 0)
	else
		PlayAnimation(self, "PlayerIdle", 0)
	end

	if moveVec.x == 0 and moveVec.y == 0 then
		return
	end

	local len = math.sqrt(moveVec.x * moveVec.x + moveVec.y * moveVec.y)
	moveVec.x = moveVec.x / len
	moveVec.y = moveVec.y / len
	MoveEntity(self, moveVec.x * 50 * deltaTime, moveVec.y * 50 * deltaTime)
end

return player
