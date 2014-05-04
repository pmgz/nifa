Nifa
=
**Nifa** is a Lua-scripted 2D game engine intended for fast prototyping. It is written in C++ and uses SFML for graphics, audio and input.

###Dependencies###
- SFML 2.1
- lua 5.1
- luabind 0.9.1


Getting started
-
Once you have the Nifa binary, all you have to do is create a file named **main.lua** in the same directory.
Here is a snippet of code which draws an image of ball on screen.
```lua
class "Ball" (Sprite) -- Ball class declaration (must derive from Sprite)

function Ball:__init(x, y) -- Ball constructor
	Sprite.__init(self) -- call constructor of base class (obligatory)
	self:setTexture("ball.png") -- set the texture
	self:setPosition(x, y) -- set the position
end

state = State() -- create a new state
state:add(Ball(100, 100)) -- add ball to the state
Game():run(state, 640, 480, "Hello world!") -- run the game in a 640x480px window
```
