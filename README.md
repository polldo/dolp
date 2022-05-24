# dolp 
dolp is a library that allows you to craft simple games for microcontrollers. 

It can be used as Arduino library, as micropython module and it could also be integrated in other C++ projects.

## Examples
| <img src="https://user-images.githubusercontent.com/17302582/170138160-fee0bf2e-e6a3-40fb-89da-05ef6e52196c.gif" width="300" alt="examples/micropython/space"/> <a href="examples/micropython/space"> Space </a>         | <img src="https://user-images.githubusercontent.com/17302582/170138706-c430b367-bcc5-46f0-98c4-b0e2e8c4ecfc.gif" width="300" alt="examples/micropython/logo/"/> <a href="examples/micropython/logo"> Logo </a> | <img src="https://user-images.githubusercontent.com/17302582/170138698-3f53c44b-375e-4a11-9e3b-94b264b6d4f5.gif" width="300" alt="examples/micropython/collision_demo/"/> <a href="examples/micropython/collision_demo/"> Collisions </a>  |
|-------------------|-------------------|-------------------|

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

<br />

## API documentation:

dolp API for micropython and C++ is very similar. Here's an overview.

***

#### Basic template
Here is a basic template to control the flow of your game.

<details><summary>Python</summary>

```python
import dolp

# Init dolp. This must be called
# before any other dolp function.
dolp.begin()

# Just run dolp forever.
while True:
	# Start a dolp frame. 
	# This operation checks for changes on the input buttons, 
	# then updates all the entities of the current world 
	# and checks for collisions.
	dolp.loop_begin()

	# This is the place where the game orchestration 
	# should be implemented (i.e. change level or check for a game over).
	# Also, here you can use external libraries to integrate sensors or actuators.
	print("I'm inside a dolp loop")

	# Terminate a dolp frame.
	# This operation finally renders all the 
	# entities and waits for the end of frame 
	# (only if the frame time did not exceed its limit, 
	# which depends on the set FPS).
	dolp.loop_end()
```

</details>

<details><summary>C++</summary>

```C++
#include <dolp.h>

void setup()
{
	// Init dolp. This must be called
	// before any other dolp function.
	dolp.begin();
}

void loop()
{
	// Start a dolp frame. 
	// This operation checks for changes on the input buttons, 
	// then updates all the entities of the current world 
	// and checks for collisions.
	dolp.loopBegin();

	// This is the place where the game orchestration 
	// should be implemented (i.e. change level or check for a game over).
	// Also, here you can use external libraries to integrate sensors or actuators.

	// Terminate a dolp frame.
	// This operation finally renders all the 
	// entities and waits for the end of frame 
	// (only if the frame time did not exceed its limit, 
	// which depends on the set FPS).
	dolp.loopEnd();
}

```

</details>

***

#### Timeouts
Timeouts are components that allow you to execute functions at specific time. 
They can be set as one-shot or repetitive:
- One-shot timeouts are used to delay some action.
- Repetitive timeouts are used to schedule periodic events.

<details><summary>Python</summary>

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

# A timeout can be also be reconfigured by using the same `set_timeout` function.
dolp.set_timeout(spawn_timeout, 100, False)

# A timeout can be deleted if not needed anymore.
dolp.delete_timeout(spawn_time)
```
</details>

<details><summary>C++</summary>

```C++
// TimeoutId is the type for dolp timeouts.
TimeoutId spawnTimeout;

void timeoutExample()
{
	// Instantiate a new timeout. 
	spawnTimeout = dolp.newTimeout();

	// Set the timeout to 500 ms and make it repetitive.
	dolp.setTimeout(spawnTimeout, 500, true);
}

void loop()
{
	dolp.loopBegin();

	// Do something here..


	// Check if the timeout has expired.
	if (dolp.checkTimeout(spawnTimeout))
	{
		// Since we set spawnTimeout to be repetitive
		// this block will be executed every 500 ms.
		//	
		// Spawn some enemies here.
		//spawnEnemy();
	}

	dolp.loopEnd();
}

void extra() {
	// A timeout can be also be reconfigured using the same `setTimeout` function.
	dolp.setTimeout(spawnTimeout, 100, false);

	// A timeout can be deleted if not needed anymore.
	dolp.deleteTimeout(spawnTimeout);
}
```
</details>

***

#### Input buttons
You probably need to check input buttons to make your game playable. Here is how you can do that.
Note that the actual pins assigned to the button definitions are retrievable from the source of the [target](src/target) you're working on.

<details><summary>Python</summary>

```python
# The available buttons are:
# dolp.BUTTON_A
# dolp.BUTTON_B
# dolp.BUTTON_C
# dolp.BUTTON_D

# Check if BUTTON_A has been pressed in
# this specific frame.
if dolp.pressed(dolp.BUTTON_A):
	move()

# Check if BUTTON_A is pressed and held.
if dolp.held(dolp.Button_A):
	speedup()
```
</details>

<details><summary>C++</summary>

```C++
// The available buttons are:
// ButtonA 
// ButtonB 
// ButtonC 
// ButtonD

// Check if ButtonA has been pressed in
// this specific frame.
if (dolp.pressed(ButtonA))
{
	move();
}

// Check if ButtonA is pressed and held.
if (dolp.held(ButtonA))
{
	speedup();
}
```
</details>

***

#### Display size
If you need to calculate relative positions and size, you can leverage two functions to retrieve the size (in pixel) of the display.

<details><summary>Python</summary>

```Python
# Returns the width of the display.
w = dolp.width()
# Returns the height of the display.
h = dolp.height()
```
</details>


<details><summary>C++</summary>

```C++
// Returns the width of the display.
int w = dolp.width();
// Returns the height of the display.
int h = dolp.height();
```
</details>

***

### Entity
Your game needs entities! 
Entities are display objects that can be controlled through the following methods.

***

#### Create and destroy entities
<details><summary>Python</summary>

```python
# Create a new empty entity. 
hero = dolp.new_entity()

# Delete and remove an entity from the display.
# The removed entity should not be used anymore.
dolp.delete_entity(hero)
```
</details>

<details><summary>C++</summary>

```C++
// Create a new empty entity. 
// PEntity is a type that represents an entity.
// It stands for Pointer Entity, indeed it is just a wrapper
// for a pointer to an entity. It is used to not worry users with pointers.
PEntity hero = dolp.newEntity();

// Delete and remove an entity from the display.
// The removed entity should not be used anymore.
dolp.deleteEntity(hero);
```
</details>

***

#### Assign and retrieve entity types
Types are useful to distinguish among different kind of entities (very relevant in collision callbacks). For example you may need to detect if the entity colliding with your hero is a monster.
A type is a simple integer number that can be assigned to entities. 

<details><summary>Python</summary>

```python

# Unfortunately there is no Enum in micropython, so you need to handle your types carefully.
# Note that we start enumerating types from 1, 
# so that a zero-value type will not be confused
# with the first valid type (HERO_TYPE in this case).
HERO_TYPE = 1
MONSTER_TYPE = 2

hero = dolp.new_entity()
hero.set_type(HERO_TYPE)

t = hero.get_type()

```
</details>

<details><summary>C++</summary>

```C++
// You can model entity types with an enum.
// Note that the first type is set to None,
// so that a zero value will not be confused
// with the first valid type (Hero in this case).
enum EntityType
{
	None,
	Hero,
	Monster
};

PEntity hero = dolp.newEntity();
hero.setType(Hero);

int t = hero.getType();
```
</details>

***

#### Configure your entities
Once a new entity is created, it should be configured with an initial position and a size.

<details><summary>Python</summary>

```python
hero = dolp.new_entity()
# Configure entity with its properties in the following order: x, y, width, height.
hero.configure(int(dolp.width() / 2), 
		int(dolp.height() / 2), 
		8, 
		8)
```
</details>

<details><summary>C++</summary>

```C++
PEntity hero = dolp.newEntity();
// Configure entity with its properties in the following order: x, y, width, height.
hero.configure(dolp.width() / 2, dolp.height() / 2, 8, 8);
```
</details>

***

#### Add some movement
dolp is able to move your object over time and to detect whether an entity is already moving.

<details><summary>Python</summary>

```python
if not hero.is_moving():
	# Just specify the destination x and y and the speed.
	hero.move_to(100, 30, 4)
```
</details>

<details><summary>C++</summary>

```C++
if (!hero.isMoving())
{
	// Just specify the destination x and y and the speed.
	monster.moveTo(100, 30, 4);
}
```
</details>

***

#### Update mechanism
Your entities need a behavior, the way to go with dolp is to define an update function that takes an entity as parameter and manages it. 
Then, you then need to assign such update function to your entity (or multiple entities). 
This function will be executed at each dolp loop.

<details><summary>Python</summary>

```python
def hero_update(hero):
	if not hero.is_moving():
		hero.move_to(random.randint(0, 128), random.randint(0, 64), 6)

hero = dolp.new_entity()
hero.configure(0, 0, 8, 8)
hero.update(hero_update)
```
</details>

<details><summary>C++</summary>

```C++
void heroUpdate(PEntity hero)
{
  if (!hero.isMoving())
  {
    int randX = random(display.width()-1);
    int randY = random(display.height()-1);
    hero.moveTo(randX, randY, 4);
  }
}

void heroSpawn()
{
	PEntity hero = dolp.newEntity();
	hero.configure(0, 0, 8, 8);
	hero.update(heroUpdate);
}
```
</details>

***

#### Collisions
Checking for collisions is important in most games.
In order to make the engine able to detect collisions of your entities automatically, you need to explicitly enable collisions for each entity that needs it.
To do that, just call the `collision` method without parameters.
Probably you would like your entities to react to collisions. 
To assign a on-collision behavior to your entity you can pass a function to `collision` that accepts two entities as parameters.

<details><summary>Python</summary>

```python
HERO_TYPE = 1
MONSTER_TYPE = 2

hero = dolp.new_entity()
# hero.configure(...)
hero.set_type(HERO_TYPE)

monster = dolp.new_entity()
# monster.configure(...)
monster.set_type(MONSTER_TYPE)

def hero_collision(hero, obj):
	if obj.get_type() == MONSTER_TYPE:
		dolp.delete_entity(obj)

# Enable collisions for hero and register its collision handler.
hero.collision(hero_collision)
# Enable collisions for monster.
monster.collision()

while True:
	dolp.loop()

```
</details>

<details><summary>C++</summary>

```C++

enum EntityType
{
	None,
	Hero,
	Monster
};

void spawn()
{
	PEntity hero = dolp.newEntity();
	// hero.configure(...);
	hero.setType(Hero);
	// Enable collisions for hero and register its collision handler.
	hero.collision(heroCollision);

	PEntity monster = dolp.newEntity();
	// monster.configure(...);
	monster.setType(Monster);
	// Enable collisions for monster.
	monster.collision();
}

void heroCollision(PEntity hero, PEntity obj)
{
	if (obj.getType() == Monster)
	{
		dolp.deleteEntity(obj);
	}
}

```
</details>

<br />

*Alternatively, if you have a very specific use case and want to manually check if entity `hero` collided with entity `monster` in the current frame you can invoke the method `hero.collided(monster)`.*

***

#### Internal state
Entities have an internal state that can store simple integer data. Each entity can store up to 4 values by default (can be overridden at compilation time) and you can access them using int indexes.

<details><summary>Python</summary>

```python
MONSTER_LIFE = 0

def monster_collision(monster, obj):
	monster.set_state(MONSTER_LIFE, monster.get_state(MONSTER_LIFE) - 1)

monster = dolp.new_entity()
monster.set_state(MONSTER_LIFE, 10)
monster.collision(monster_collision)
```
</details>

<details><summary>C++</summary>

```C++
enum MonsterState
{
	Life
};

void spawn()
{
	PEntity monster = dolp.newEntity();
	monster.collision(monsterCollision);
}

void monsterCollision(PEntity monster, PEntity obj)
{
	monster.setState(Life, monster.getState(Life) - 1);
}

```
</details>

***

#### Images and animations
Entities without a specific image are rendered as rectangles with the size of their body (set through `configure` method).
Images and animations can be assigned to entities through the following methods.
	
To convert an image in bytes that dolp can understand, consult [monochrome](tools/monochrome).
A collection of some ready to use images can be found at .

<details><summary>Python - Image</summary>

```python
# An image is just an array of bytes.
arduino_img = bytearray([0x0F, 0x08, 0x3c, 0x66, 0xc2, 0x92, 0xd2, 0x46, 0x6c, 0x38, 0x6c, 0x46, 0xd2, 0x92, 0xc2, 0x66, 0x3c])

logo = dolp.new_entity()
logo.configure(32, 32, 8, 8)
logo.set_image(arduino_img)
```
</details>

<details><summary>Python - Animation</summary>

```python
explosion1 = bytearray([0x10, 0x10, 0x00, 0x00, 0x00, 0x00, 0x90, 0x40, 0x40, 0x20, 0x40, 0x40, 0x84, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x05, 0x01, 0x02, 0x01, 0x21, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00])
explosion2 = bytearray([0x10, 0x10, 0x00, 0x00, 0x00, 0x00, 0x88, 0x60, 0x24, 0x10, 0x20, 0x60, 0x80, 0x00, 0x12, 0x00, 0x00, 0x00, 0x00, 0x40, 0x02, 0x00, 0x00, 0x03, 0x02, 0x24, 0x02, 0x03, 0x00, 0x00, 0x00, 0x44, 0x00, 0x00])
explosion3 = bytearray([0x10, 0x10, 0x00, 0x00, 0x60, 0x44, 0x84, 0x40, 0xa6, 0x14, 0x10, 0x20, 0x42, 0x82, 0x00, 0x08, 0x40, 0x00, 0x00, 0x08, 0x00, 0x08, 0x01, 0x22, 0x04, 0x4b, 0x48, 0x05, 0x02, 0x01, 0x00, 0x60, 0x06, 0x00])
explosion4 = bytearray([0x10, 0x10, 0x00, 0x00, 0x00, 0x18, 0xa8, 0xc8, 0xf0, 0xf0, 0xf0, 0xe0, 0xe8, 0xb8, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x39, 0x17, 0x17, 0x1f, 0x0f, 0x17, 0x13, 0x21, 0x78, 0x20, 0x00, 0x00])

# Specify a list of images and a list of durations to describe the animation's frames.
explosion = dolp.Animation([explosion1, explosion2, explosion3, explosion4], 
			[150, 200, 200, 300])

xplode = dolp.new_entity()
xplode.set_animation(explosion)
xplode.configure(30, 30, 8, 8)
```
</details>

<details><summary>C++ - Image</summary>

```C++
// An image is just an array of bytes.
const uint8_t arduinoImg[] = {0x0F, 0x08, 0x3c, 0x66, 0xc2, 0x92, 0xd2, 0x46, 0x6c, 0x38, 0x6c, 0x46, 0xd2, 0x92, 0xc2, 0x66, 0x3c};

PEntity logo = dolp.newEntity();
logo.configure(32, 32, 8, 8);
obj.setImage(arduinoImg);
```
</details>

<details><summary>C++ - Animation</summary>

```C++
const uint8_t explosion1[] = { 0x10, 0x10, 0x00, 0x00, 0x00, 0x00, 0x90, 0x40, 0x40, 0x20, 0x40, 0x40, 0x84, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x05, 0x01, 0x02, 0x01, 0x21, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00 };
const uint8_t explosion2[] = { 0x10, 0x10, 0x00, 0x00, 0x00, 0x00, 0x88, 0x60, 0x24, 0x10, 0x20, 0x60, 0x80, 0x00, 0x12, 0x00, 0x00, 0x00, 0x00, 0x40, 0x02, 0x00, 0x00, 0x03, 0x02, 0x24, 0x02, 0x03, 0x00, 0x00, 0x00, 0x44, 0x00, 0x00 };
const uint8_t explosion3[] = { 0x10, 0x10, 0x00, 0x00, 0x60, 0x44, 0x84, 0x40, 0xa6, 0x14, 0x10, 0x20, 0x42, 0x82, 0x00, 0x08, 0x40, 0x00, 0x00, 0x08, 0x00, 0x08, 0x01, 0x22, 0x04, 0x4b, 0x48, 0x05, 0x02, 0x01, 0x00, 0x60, 0x06, 0x00 };
const uint8_t explosion4[] = { 0x10, 0x10, 0x00, 0x00, 0x00, 0x18, 0xa8, 0xc8, 0xf0, 0xf0, 0xf0, 0xe0, 0xe8, 0xb8, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x39, 0x17, 0x17, 0x1f, 0x0f, 0x17, 0x13, 0x21, 0x78, 0x20, 0x00, 0x00 };

const uint8_t *monsterImages[] = {explosion1, explosion2, explosion3, explosion4};
const uint32_t monsterTimes[] = {150, 200, 200, 300};
// Specify a list of images and a list of durations to describe the animation's frames. 
// Also pass the number of frames as the third parameter.
const Animation explosionAnimation(monsterImages, monsterTimes, 4);

void explosion(int x, int y)
{
  PEntity xplode = dolp.newEntity();
  xplode.configure(x, y, 0, 0);
  xplode.setAnimation(explosionAnimation);
}

```
</details>

***

#### Entities Timeouts
Timeouts have been already covered. However, what if you want to use specific timeouts for different entities? 
	
As an example, let's design a very simple explosion. Let's imagine that when a monster collides with a bullet, we destroy the monster and render and explosion by spawning a new entity with a particular image/animation. Now, we want the explosion to only last 300 milliseconds.
Here entities' timeouts come in handy. 
	We can initialize a timeout and retrieve it similarly to accessing the state of entities. 
Once you have a timeout, it can be used to control the duration of the explosion like generic timeouts.
Once an entity gets destroyed, its timeouts are destroyed too.

<details><summary>Python</summary>

```python
particle_img = bytearray([0x08, 0x08, 0xf7, 0xbe, 0xff, 0xf7, 0x5f, 0xfe, 0xf7, 0xbd])

PARTICLE_LIVE_TIMEOUT = 0

def update_particle(particle):
  timeout = particle.get_timeout(PARTICLE_LIVE_TIMEOUT);
  if (dolp.check_timeout(timeout)):
    dolp.delete_entity(particle)

def spawn_particle(x, y):
  particle = dolp.new_entity()
  particle.configure(x, y, 8, 8)
  particle.set_image(particle_img)
  particle.update(update_particle)
  tm = particle.new_timeout(PARTICLE_LIVE_TIMEOUT)
  dolp.set_timeout(tm, 230, False)
```
</details>

<details><summary>C++</summary>

```C++
const uint8_t particleImg[] = {0x0F, 0x08, 0x3c, 0x66, 0xc2, 0x92, 0xd2, 0x46, 0x6c, 0x38, 0x6c, 0x46, 0xd2, 0x92, 0xc2, 0x66, 0x3c};

enum ParticleTimeout
{
  LiveTimeout
};

void spawnParticle(int x, int y)
{
  PEntity particle = dolp.newEntity();
  particle.configure(x, y, 8, 8);
  obj.setImage(particleImg);
  obj.update(updateParticle);
  auto tm = particle.newTimeout(LiveTimeout);
  dolp.setTimeout(tm, 230, false);
}

void updateParticle(PEntity obj)
{
  auto tm = obj.getTimeout(LiveTimeout);
  if (dolp.checkTimeout(tm))
  {
    dolp.deleteEntity(obj);
  }
}

```
</details>

***

#### Position and manual movement
Position of entities can be retrieved and manually changed.

<details><summary>Python</summary>

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
	dolp.loop_begin()
	dolp.loop_end()

```
</details>

<details><summary>C++</summary>

```C++
#include <dolp.h>

void setup()
{
	dolp.begin();
	hero = dolp.newEntity();
	hero.configure(4, 4, 8, 8);
	hero.update(updateHero);
}

void updateHero(PEntity hero)
{
	if (dolp.held(ButtonA))
	{
		hero.setX(hero.getX() + 1);
	}
}

void loop()
{
	dolp.loopBegin();
	dolp.loopEnd();
}

```
</details>

