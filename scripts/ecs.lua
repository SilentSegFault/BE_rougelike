local ecs = {
	scenes = {},
	currentScene = nil,
}

function ecs:NewScene(name)
	self.scenes[name] = {}
end

function ecs:LoadScene(name)
	if self.scenes[name] == nil then
		self:NewScene(name)
	end

	self.currentScene = self.scenes[name]
end

function ecs:AddEntity(ent)
	if self.currentScene[ent.id] ~= nil then
		LogWarning("Entity with id " .. ent.id .. " already exists")
		return
	end

	self.currentScene[ent.id] = ent
end

function ecs:RemoveEntity(ent)
	if type(ent) == "number" then
		self.currentScene[ent] = nil
	elseif type(ent) == "table" then
		self.currentScene[ent.id] = nil
	else
		LogWarning("Invalid argument in RemoveEntity. Required number or entity")
	end
end

function ecs:GetEntity(id)
	if self.currentScene[id] == nil then
		LogWarning("Entity with doesn't exists")
		return
	end

	return self.currentScene[id]
end

function ecs:HasKey(ent, key)
	return ent[key] ~= nil
end

function ecs:IsEntity(ent)
	return type(ent) == "table"
		and self:HasKey(ent, "id")
		and self:HasKey(ent, "OnCreate")
		and self:HasKey(ent, "OnUpdate")
		and self:HasKey(ent, "OnDestroy")
		and self:HasKey(ent, "OnStart")
end

return ecs
