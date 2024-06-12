local start_button = Entity:New({
	components = {
		transform = { size = { width = 32 * 18, height = 16 * 18 } },
		spriteRender = { sprite = "btn_background1" },
	},
})

function start_button:OnUpdate(deltaTime)
	if KeyPressed("mouse_left") then
		local mouseX, mouseY = GetMousePos()
		local x, y = GetEntityPos(self)
		local hWidth = self.components.transform.size.width * 0.5
		local hHeight = self.components.transform.size.height * 0.5

		local isInside = mouseX > (x - hWidth)
			and mouseX < (x + hWidth)
			and mouseY > (y - hHeight)
			and mouseY < (y + hHeight)

		if isInside then
			LoadScene("level1")
		end
	end
end

return start_button
