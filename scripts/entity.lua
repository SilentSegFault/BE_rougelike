local entity = {
	id = -1,
	components = {},
	tags = {},
}

function entity:New(o, id)
	o = o or {}
	setmetatable(o, self)
	self.__index = self
	o.id = id or -1
	return o
end

function entity:SetID(id)
	self.id = id
end

function entity:HasTag(tag)
	for _, t in ipairs(self.tags) do
		if t == tag then
			return true
		end
	end

	return false
end

function entity:OnCreate()
	-- code
end

function entity:OnStart()
	-- code
end

function entity:OnUpdate(deltaTime)
	-- code
end

function entity:OnCollision(ent)
	-- code
end

function entity:OnDestroy()
	-- code
end

return entity
