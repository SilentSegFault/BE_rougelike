local enemy3 = Entity:New({
  components = {
    transform = { size = { width = 150, height = 150 } },
    animator = { animation = "enemy3Idle" },
    collider = { width = 70, height = 140, collisionLayer = 6 },
  },
  tags = { "enemy" },
  health = 8,
  distance = 450,
  distanceBias = 50,
  speed = 200,
  timeToShoot = 1,
  timesShot = 0
})

function enemy3:OnCreate()
  EntitiesToKill = EntitiesToKill + 1
end

function enemy3:OnUpdate(deltaTime)
  if self.health <= 0 then
    EntitiesToKill = EntitiesToKill - 1
    DestroyEntity(self)
    return
  end

  self.timeToShoot = self.timeToShoot - deltaTime

  local x, y = GetEntityPos(self)
  local px, py = GetEntityPos(Ecs:GetEntity(playerID))

  if self.timeToShoot <= 0 then
    self.timesShot = self.timesShot + 1
    if self.timesShot == 2 then
      self.timesShot = 0
      self.timeToShoot = 0.6
    else
      self.timeToShoot = 0.1
    end
    local bulletID = SpawnEntity("EnemyProjectile", x, y, 0)
    local bullet = Ecs:GetEntity(bulletID)
    EntityLookAt(bullet, px, py)
  end


  if px > x then
    PlayAnimation(self, "enemy3Idle", 1)
  else
    PlayAnimation(self, "enemy3Idle", 0)
  end

  local dist = math.sqrt((px - x) * (px - x) + (py - y) * (py - y))

  local dirX = px - x
  local dirY = py - y

  local acc = 0

  if dist > self.distance + self.distanceBias then
    acc = dist / (self.distance + self.distanceBias)
  elseif dist < self.distance - self.distanceBias then
    acc = dist / (self.distance - self.distanceBias) - 2
  end

  local len = math.sqrt(dirX * dirX + dirY * dirY)

  local velX = acc * dirX / len * self.speed * deltaTime
  local velY = acc * dirY / len * self.speed * deltaTime

  MoveEntity(self, velX, velY)
end

return enemy3
