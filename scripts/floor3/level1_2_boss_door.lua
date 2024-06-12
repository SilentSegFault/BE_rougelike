local level1_2_boss_door = Entity:New({
	components = {
		transform = { size = { width = 120, height = 60 } },
		collider = { width = 120, height = 60, collisionLayer = 10 },
		spriteRender = { sprite = "bossDoor" },
	},
	tags = { "door" },
})

function level1_2_boss_door:OnCollision(ent)
	if ent:HasTag("player") and CanAccesLevel2_2 then
		local _, y = GetEntityPos(self)
		local px, py = GetEntityPos(ent)

		LastPlayerPos = { x = px, y = 1080 - 180 }

		if math.abs(y - py) < 30 then
			LoadScene("level23f3")
		end
	end
end

return level1_2_boss_door
