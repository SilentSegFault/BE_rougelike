local ak47 = Entity:New({
	components = {
		transform = { size = { width = 100, height = 50 } },
		spriteRender = { sprite = "ak47" },
	},
  reloadTime = 0.15,
  timeToShoot = 0
})

function ak47:OnCreate()
  local px, py = GetEntityPos(Ecs:GetEntity(playerID))
  local x, y = GetEntityPos(self)

  local dirX = px - x
  local dirY = py - y
  local len = math.sqrt(dirX * dirX + dirY * dirY)

  MoveEntity(self, -30 * dirX / len, -30 * dirY / len)
end

function ak47:OnUpdate(deltaTime)

  if self.timeToShoot > 0 then
    self.timeToShoot = self.timeToShoot - deltaTime
  end

  if self.timeToShoot <= 0 and KeyPressed("mouse_left") then
    self.timeToShoot = self.reloadTime
    local x, y = GetEntityPos(self)
    local rot = GetEntityRotation(self)
    SpawnEntity("PlayerBullet", x, y, rot)
  end
end

return ak47
