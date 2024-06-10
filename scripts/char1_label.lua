local char1_label = Entity:New({
	components = {
		textRender = {
			text = "Take this you may need it. Now go.",
			scale = 1.5,
			color = { r = 0, g = 0, b = 0 },
		},
	},
	timeToLive = 5,
})

function char1_label:OnUpdate(deltaTime)
	if self.timeToLive <= 0 then
		DestroyEntity(self)
	end

	self.timeToLive = self.timeToLive - deltaTime
end

return char1_label
