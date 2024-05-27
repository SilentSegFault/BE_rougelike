-- Creating new entity type
-- 1. First we have to create new entity class and set default properties that we want to change
-- Available default properties are as below:
-- Entity.size = {width = 20, height = 20}
-- Entity.render = {sprite = "default", shader = "sprite", colorMask = {256, 256, 256}, drawLayer = 0}
-- Entity.stats = {health = 0, speed = 0}
-- Entity.collisionShape = "circle"
-- Entity.tags = {} - not implemented
--
Human = Entity:New({
	size = { width = 80, height = 80 },
	render = { sprite = "human", drawLayer = 0 },
	stats = { health = 100, speed = 50 },
})

-- And add our own default properties for our entities

-- 3. Nex we can define behaviour of our entities by overriding default methods and by creating new ones
-- There are few default methods:
-- Entity:OnCreate() - method is run once, when entity is created
-- Entity:OnUpdate(deltaTime) - method is run once per frame
-- Entity:OnDestroy() - method is run once, when entity is destroyed

function Human:OnUpdate(deltaTime)
	if KeyPressed("key_a") then
		FlipLeft(self)
		MoveEntity(self, -self.stats.speed * deltaTime, 0)
	end

	if KeyPressed("key_d") then
		FlipRight(self)
		MoveEntity(self, self.stats.speed * deltaTime, 0)
	end

	if KeyPressed("key_w") then
		MoveEntity(self, 0, -self.stats.speed * deltaTime)
	end

	if KeyPressed("key_s") then
		MoveEntity(self, 0, self.stats.speed * deltaTime)
	end

	if KeyPressed("mouse_left") then
		local x, y = GetMousePos()
		SetEntityPos(self, x, y)
	end
	if KeyDown("key_p") then
		local mouseX, mouseY = GetMousePos()
		local posX, posY = GetEntityPos(self)

		local id = SpawnEntity("Bullet", posX, posY, 0)
		local e = Entities[id]
		EntityLookAt(e, mouseX, mouseY)
	end
end

-- 4. Everything is set up! Now create scene with our new entity in it and watch it live!
