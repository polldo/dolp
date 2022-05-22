# dolp 
dolp is a library that allows you to craft simple games for microcontrollers. It can be used as Arduino library, as micropython module and it could also be integrated in other C++ projects.

table with game gifs of examples here. with a link to examples

### Supported hardware

| Environment | Board                  | Display                 |
| ----------- | ---------------------- | ----------------------- |
| micropython | arduino rp2040 connect | SSD1306, SH1106         |
| micropython | generic rp2040         | SSD1306, SH1106         |
| arduino     | arduino rp2040 connect | SSD1306, SH1106         |
| arduino     | arduino nano 33 ble    | SSD1306, SH1106, ST7735 |

### Hardware configuration
**Arduino environment**: to set your configuration you need to modify the [hardware configuration](src/hardware/HwConfiguration.h) by commenting/uncommenting defines according to your needs.

**micropython environment**: configuration is resolved at compile time, thus you need to recompile the module if you want to change it. 
More information in [micropython](micropython) subfolder.


## API documentation:

dolp API for micropython and C++ is very similar. Here's an overview.


#### Game control
The first step is to create a skeleton to control the flow of your game.
Here you need to import and initialize dolp. 
This should be called before any other dolp function.
`dolp.begin()` 

`dolp.loop_begin()`
Start a dolp frame. 
This operation checks for changes on the input buttons, then updates all the entities of the current world and checks for collisions.

`dolp.loop_end()`
Terminate a dolp frame.
This operation finally renders all the entities and waits for the end of frame (only if the frame time did not exceed its limit, which depends on the set FPS).
Between the `loop_begin` and `loop_end` you can manually change entities' behavior or state.
Also, this is the place where the game orchestration should be implemented (i.e. change level or check for a game over).

example: 
```python
import dolp

dolp.begin()

# Just run dolp forever.
while True:
	dolp.loop_begin()
	print("I'm inside a dolp loop")
	dolp.loop_end()

```



#### Timeouts
`dolp.new_timeout()`
`dolp.delete_timeout(tm)`
`dolp.set_timeout(..)`
`check_timeout`
Timeouts are components that allow you to execute functions at specific time. 
They can be set as one-shot or repetitive.
- One-shot timeouts are used to delay some action.
- Repetitive timeouts are used to schedule periodic events.
```python
# Instantiate a new timeout. 
spawn_time = dolp.new_timeout()

# Set the timeout to 500 ms and make it repetitive.
dolp.set_timeout(spawn_timeout, 500, True)

while True:
	dolp.loop_begin()
	# Do something here..

	# Check if the timeout has expired.
	if dolp.check_timeout(spawn_timeout):
		# Since we set spawn_timeout to be repetitive
		# this block will be executed every 500 ms.
		#
		# Spawn some enemies here.
		pass

	dolp.loop_end()

# A timeout can be deleted if not needed anymore.
dolp.delete_timeout(spawn_time)
```

#### Input buttons
`pressed`
`held`
`BUTTON_A`
`BUTTON_B`
`BUTTON_C`
`BUTTON_D`
You probably need to check input buttons to make your game playable. Here is how you can do that.
Note that the pin assigned to the button definitions are retrievable from the source of the [target](src/target) you're working on.
```python
# Check if BUTTON_A has been pressed in
# this specific frame.
if dolp.pressed(dolp.BUTTON_A):
	move()

# Check if BUTTON_A is pressed and held.
if dolp.held(dolp.Button_A):
	speedup()
```

#### Display size
`width`
Returns the width of the display.
`height`
Returns the height of the display.

### Entity
Your game needs entities! Entities are display objects that can be controlled through the following methods.

`dolp.new_entity()`
`dolp.delete_entity(entity)`

```python
# Create a new empty display object. 
hero = dolp.new_entity()

# Delete and remove an entity from the display.
# The removed entity should not be used anymore.
dolp.delete_entity(hero)
```

`get_id`
`set_type`
`get_type`
You may specify a type for your entities. In this way you will be able to distinguish them (useful in collision callbacks).
A type is simply an integer: unfortunately there is no Enum in micropython, so you need to handle your types carefully.

`configure`
Set the properties of your entities in the following order: x, y, width, height.
```python
hero = dolp.new_entity()
hero.configure(int(dolp.width() / 2), 
		int(dolp.height() / 2), 
		8, 
		8)
```

`move_to`
`is_moving`
dolp is able to move your object over time, just use the `move_to` method specify the destination x and y and the entity speed.
```python
if not hero.is_moving():
	hero.move_to(100, 30, 4)
```

`update`
Your entities need a behavior, the way to go with dolp is to define an update function that takes an entity as parameter and manages it. Then, you then need to assign such update function to your entity (or multiple entities). This function will be executed at each dolp loop.
```python
def hero_update(hero):
	if not hero.is_moving():
			hero.move_to(random.randint(0, 128), 
					random.randint(0, 64), 
					6)

hero = dolp.new_entity()
hero.configure(0, 0, 8, 8)
hero.update(hero_update)

while True:
	dolp.loop()
```

`collision`
`collided`
Checking for collisions is important in most games.
In order to be able to detect if an entity collided with another one you need to 
You need to enable 
In order to make the engine able to detect collisions of your entities automatically, you need to explicitly enable collisions for the entities that need it.
To do that, just call the `collision` method without parameters.
Probably you would like your entities to react to collisions. To assign a on-collision behavior to your entity you can pass a function to `collision` that accepts two entities as parameters.
```python
HERO_TYPE = 1
MONSTER_TYPE = 2

hero = dolp.new_entity()
hero.configure(...)
hero.set_type(HERO_TYPE)

monster = dolp.new_entity()
monster.configure(...)
monster.set_type(MONSTER_TYPE)

def hero_collision(hero, obj):
	if obj.get_type() == MONSTER_TYPE:
		dolp.delete_entity(obj)

hero.collision(hero_collision)
monster.collision()

while True:
	dolp.loop()

```

Alternatively, if you have a very specific use case and want to manually check if entity `hero` collided with entity `monster` in the current frame you can invoke the method `hero.collided(monster)`.

`set_state`
`get_state`
Entities have an internal state that can store simple integer data. 
```python
MONSTER_LIFE = 0

def monster_collision(monster, obj):
	monster.set_state(MONSTER_LIFE, monster.get_state(MONSTER_LIFE) - 1)

monster = dolp.new_entity()
monster.set_state(MONSTER_LIFE, 10)
monster.collision(monster_collision)

```

`set_image`
`set_animation`
Entities without a specific image are rendered as rectangles with the size of their body (set through `configure` method).
Images and animations can be assigned to entities through the following methods.
To convert an image in bytes that dolp can understand, consult https://github.com/polldo/dolp/tree/master/tools/monochrome .
A collection of some ready to use images can be found at ...

```python
arduinoImg = bytearray(b'\x0F\x08\x3c\x66\xc2\x92\xd2\x46\x6c\x38\x6c\x46\xd2\x92\xc2\x66\x3c')

logo = dolp.new_entity()
logo.configure(32, 32, 8, 8)
logo.set_image(arduinoImg)
```
Add result here !!!

```python
explosion1 = bytearray(b'\x10\x10\x00\x00\x00\x00\x90\x40\x40\x20\x40\x40\x84\x00\x10\x00\x00\x00\x00\x00\x04\x00\x00\x05\x01\x02\x01\x21\x00\x04\x00\x00\x00\x00')
explosion2 = bytearray(b'\x10\x10\x00\x00\x00\x00\x88\x60\x24\x10\x20\x60\x80\x00\x12\x00\x00\x00\x00\x40\x02\x00\x00\x03\x02\x24\x02\x03\x00\x00\x00\x44\x00\x00')
explosion3 = bytearray(b'\x10\x10\x00\x00\x60\x44\x84\x40\xa6\x14\x10\x20\x42\x82\x00\x08\x40\x00\x00\x08\x00\x08\x01\x22\x04\x4b\x48\x05\x02\x01\x00\x60\x06\x00')
explosion4 = bytearray(b'\x10\x10\x00\x00\x00\x18\xa8\xc8\xf0\xf0\xf0\xe0\xe8\xb8\x08\x00\x00\x00\x00\x00\x00\x30\x39\x17\x17\x1f\x0f\x17\x13\x21\x78\x20\x00\x00')
explosion = dolp.Animation([explosion1, explosion2, explosion3, explosion4], 
			[150, 200, 200, 300])

xplode = dolp.new_entity()
xplode.set_animation(explosion)
xplode.configure(30, 30, 8, 8)
```

`new_timeout`
`delete_timeout`
`get_timeout`
Timeouts have been already covered. However, what if you want to use specific timeouts for different entities? 
As an example, let's design a very simple explosion. Let's imagine that when a monster collides with a bullet, we destroy the monster and render and explosion by spawning a new entity with a particular image/animation. Now, we want the explosion to only last 300 milliseconds.
Here entities' timeouts come in handy. We can initialize a timeout and retrieve it similarly to accessing the state of entities. Once you have a timeout, it can be used to control the duration of the explosion like generic timeouts.
Once an entity gets destroyed, its timeouts are destroyed too.
```python
particleImg = bytearray(b'\x08\x08\xf7\xbe\xff\xf7\x5f\xfe\xf7\xbd')
PARTICLE_LIVE = 0

def updateParticle(particle):
  timeout = particle.get_timeout(PARTICLE_LIVE);
  if (dolp.check_timeout(timeout)):
    dolp.delete_entity(particle)

def spawnParticle(x, y):
  particle = dolp.new_entity()
  particle.update(updateParticle)
  particle.set_image(particleImg)
  tm = particle.new_timeout(PARTICLE_LIVE)
  dolp.set_timeout(tm, 230, False)
  particle.configure(x, y, 8, 8)

```

`get_x`
`get_y`
`set_x`
`set_y`
Position of entities can be retrieved and manually changed.
```python
import dolp
dolp.begin()
hero = dolp.new_entity()
hero.configure(4, 4, 8, 8)

def hero_update(hero):
	if dolp.held(dolp.BUTTON_A):
		hero.set_x(hero.get_x() + 1)

hero.update(hero_update)

while True:
	dolp.loop()

```
