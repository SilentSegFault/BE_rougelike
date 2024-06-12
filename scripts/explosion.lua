local explosion = Entity:New({
	components = {
		transform = { size = { width = 140, height = 140 } },
		animator = { animation = "explosion" },
	},
})

function explosion:OnUpdate()
  PlayAnimationOnce(self, "explosion", 0)
  if AnimationFinished(self) then
    DestroyEntity(self)
  end
end

return explosion
