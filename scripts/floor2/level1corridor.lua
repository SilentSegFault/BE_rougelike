local level1corridor = Entity:New({
	components = {
		transform = { size = { width = 50, height = 1080 } },
		collider = { width = 50, height = 1080, collisionLayer = 10 },
	},
	tags = { "door" },
})

function level1corridor:OnCollision(ent)
    print("O kurwa")
	if ent:HasTag("player") and CanAccesLevel2Floor2 then
		local x, _ = GetEntityPos(self)
		local px, py = GetEntityPos(ent)

		LastPlayerPos = { x = 150, y = py }

		if math.abs(x - px) < 30 then
			LoadScene("level2f2")
		end
	end
end

    return level1corridor
