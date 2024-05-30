Entity = {
	id = -1,
	tags = {},
}

function Entity:New(o)
	o = o or {}
	setmetatable(o, self)
	self.__index = self
	return o
end

function Entity:OnCreate() end

function Entity:OnUpdate(deltaTime) end

function Entity:OnDestroy() end

Entities = {}

function CallOnCreate(id)
	Entities[id]:OnCreate()
end

function CallOnUpdate(id, deltaTime)
	Entities[id]:OnUpdate(deltaTime)
end

function UpdateEntities(deltaTime)
	for _, entity in pairs(Entities) do
		entity:OnUpdate(deltaTime)
	end
end

function CallOnDestroy(id)
	Entities[id]:OnDestroy()
end

function NewEntity(ent, id)
	local newEnt = ent:New({ id = id })
	Entities[id] = newEnt
	return newEnt
end

function HasKey(ent, key)
	return ent[key] ~= nil
end

function IsEntity(ent)
	return type(ent) == "table"
		and HasKey(ent, "id")
		and HasKey(ent, "OnCreate")
		and HasKey(ent, "OnUpdate")
		and HasKey(ent, "OnDestroy")
end

function RemoveEntity(ent)
	Entities[ent.id] = nil
end
