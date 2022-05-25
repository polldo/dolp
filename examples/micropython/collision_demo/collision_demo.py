import random

import dolp

# Particle vars
particleImg = bytearray([0x08, 0x08, 0xf7, 0xbe, 0xff, 0xf7, 0x5f, 0xfe, 0xf7, 0xbd])
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


# Monster vars
monsterCounter = 0
MONSTER_HIT = 0

def monsterCollision(monster, other):
  global monsterCounter
  if monster.get_state(MONSTER_HIT) == 1:
    return
  monster.set_state(MONSTER_HIT, 1)
  dolp.delete_entity(monster)
  spawnParticle(monster.get_x(), monster.get_y())
  monsterCounter -= 1

def monsterLoop(monster):
  if not monster.is_moving():
    randX = random.randint(10, 110)
    randY = random.randint(8, 48)
    monster.move_to(randX + 10, randY + 10, 5)

def spawnMonster():
  global monsterCounter
  if monsterCounter >= 12:
    return
  monster = dolp.new_entity()
  randX = random.randint(10, 110)
  randY = random.randint(8, 48)
  monster.configure(randX, randY, 8, 8)
  monster.collision(monsterCollision)
  monster.update(monsterLoop)
  monster.set_state(MONSTER_HIT, 0)
  monsterCounter += 1


dolp.begin()

spawnTimeout = dolp.new_timeout()
dolp.set_timeout(spawnTimeout, 500, True)
while True:
  dolp.loop_begin()
  if (dolp.check_timeout(spawnTimeout)):
    spawnMonster()
  dolp.loop_end()
