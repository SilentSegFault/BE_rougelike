local char2_label = Entity:New({
	components = {
		textRender = {
			text = "Thank you for saving me !! :)",
			scale = 1,
			color = { r = 0, g = 0, b = 0 },
		},
	},
	timeToLive = 5,
})

function char2_label:OnUpdate(deltaTime)
	if self.timeToLive <= 0 then
		DestroyEntity(self)
	end

	self.timeToLive = self.timeToLive - deltaTime
end

return char2_label
