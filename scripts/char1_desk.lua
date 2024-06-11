local char1_desk = Entity:New({
	components = {
		transform = { size = { width = 120, height = 240 } },
		spriteRender = { sprite = "desk" },
		collider = { width = 60, height = 120, collisionLayer = 10 },
	},
	tags = { "wall" },
	visited = false,
})

function char1_desk:OnCollision(ent)
	if ent:HasTag("player") and not self.visited then
		self.visited = true
		SpawnEntity("Char1Label", 1250, 500, 0)
		local playerX, playerY = GetEntityPos(ent)
		local holderID = SpawnEntity("WeaponHolder", playerX, playerY, 0)
		local weaponID = SpawnEntity("Weapon", playerX + 50, playerY, 0)
		SetEntityParent(weaponID, holderID)
		SetEntityParent(holderID, ent.id)

		ent.holder = holderID
		ent.weapon = weaponID

		CanAccesLevel2 = true
	end
end

return char1_desk
