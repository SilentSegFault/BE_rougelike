local level2_1_corridor = Entity:New({
	components = {
		transform = { size = { width = 50, height = 1080 } },
		collider = { width = 50, height = 1080, collisionLayer = 10 },
	},
	tags = { "door" },
})

function level2_1_corridor:OnCollision(ent)
	if ent:HasTag("player") and CanAccesLevel2_2 then
		local x, _ = GetEntityPos(self)
		local px, py = GetEntityPos(ent)

		LastPlayerPos = { x = 150, y = py }

		if math.abs(x - px) < 30 then
			LoadScene("level22")
		end
	end
end

return level2_1_corridor
