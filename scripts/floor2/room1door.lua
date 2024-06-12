local room1door = Entity:New({
	components = {
		transform = { size = { width = 120, height = 60 } },
		collider = { width = 120, height = 60, collisionLayer = 10 },
		spriteRender = { sprite = "door" },
	},
	tags = { "door" },
})

function room1door:OnCollision(ent)
	if ent:HasTag("player") and CanLeaveLevel1Floor2Room1 then
		local _, y = GetEntityPos(self)
		local px, py = GetEntityPos(ent)

		LastPlayerPos = { x = px, y = 180 }

		if math.abs(y - py) < 50 then
			LoadScene("level1f2")
		end
	end
end

return room1door
