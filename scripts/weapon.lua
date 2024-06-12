local weapon = Entity:New({
  components = {
    transform = { size = { width = 100, height = 100 } },
    spriteRender = { sprite = "weapon" },
  },
})

function weapon:OnUpdate(deltaTime)
  if KeyDown("mouse_left") then
    local x, y = GetEntityPos(self)
    local rot = GetEntityRotation(self)
    SpawnEntity("PlayerBullet", x, y, rot)
  end
end

return weapon
