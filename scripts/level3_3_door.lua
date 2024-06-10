local level3_3_door = Entity:New({
	components = {
		transform = { size = { width = 120, height = 60 } },
		collider = { width = 120, height = 60, collisionLayer = 10 },
		spriteRender = { sprite = "door" },
	},
	tags = { "door" },
})

function level3_3_door:OnCollision(ent)
	if ent:HasTag("player") and CanLeaveLevel3_3 then
		local _, y = GetEntityPos(self)
		local px, py = GetEntityPos(ent)

		LastPlayerPos = { x = px, y = 180 }

		if math.abs(y - py) < 50 then
			LoadScene("level21")
		end
	end
end

return level3_3_door
