local shotgun = Entity:New({
  components = {
    transform = { size = { width = 100, height = 50 } },
    spriteRender = { sprite = "shotgun" },
  },
  reloadTime = 2,
  timeToReload = 0,
  bullets = 5,
  currentBullets = 5
})

function shotgun:OnCreate()
  local px, py = GetEntityPos(Ecs:GetEntity(playerID))
  local x, y = GetEntityPos(self)

  local dirX = px - x
  local dirY = py - y
  local len = math.sqrt(dirX * dirX + dirY * dirY)

  MoveEntity(self, -30 * dirX / len, -30 * dirY / len)
end

function shotgun:OnUpdate(deltaTime)
  local px, py = GetEntityPos(Ecs:GetEntity(playerID))
  local x, y = GetEntityPos(self)

  if self.currentBullets <= 0 and self.timeToReload <= 0 then
    self.timeToReload = self.reloadTime
    RotateEntity(self, math.rad(-90))

    local dirX = px - x
    local dirY = py - y
    local len = math.sqrt(dirX * dirX + dirY * dirY)

    MoveEntity(self, 30 * dirX / len, 30 * dirY / len)
  end

  if self.timeToReload > 0 then
    self.timeToReload = self.timeToReload - deltaTime

    if self.timeToReload <= 0 then
      self.currentBullets = self.bullets
      RotateEntity(self, math.rad(90))

      local dirX = px - x
      local dirY = py - y
      local len = math.sqrt(dirX * dirX + dirY * dirY)

      MoveEntity(self, -30 * dirX / len, -30 * dirY / len)
    end
  end

  if self.currentBullets > 0 and KeyDown("mouse_left") then
    self.currentBullets = self.currentBullets - 1
    local x, y = GetEntityPos(self)
    local rot = GetEntityRotation(self)
    SpawnEntity("PlayerBullet", x, y, rot)
    SpawnEntity("PlayerBullet", x, y, rot + math.rad(10))
    SpawnEntity("PlayerBullet", x, y, rot + math.rad(5))
    SpawnEntity("PlayerBullet", x, y, rot - math.rad(10))
    SpawnEntity("PlayerBullet", x, y, rot - math.rad(5))
  end
end

return shotgun
