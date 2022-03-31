import random

import dolp

# Images
spaceship = bytearray(b'\x10\x10\x00\x00\xb4\x00\x00\xc0\xfc\x15\x15\xfc\xc0\x00\x00\xb4\x00\x00\x40\xfc\x7f\x20\x38\x98\x49\xef\xef\x49\x98\x38\x20\x7f\xfc\x40')
enemy1 = bytearray(b'\x10\x10\x00\x80\xc0\x60\xf5\x35\x60\xc8\xc8\x60\x35\xf5\x60\xc0\x80\x00\x00\x36\x02\x00\x1d\x26\x4c\x93\x93\x4c\x26\x1d\x00\x02\x36\x00')
enemy1mask = bytearray(b'\x10\x10\x00\x80\xc0\x60\xff\xff\xf0\xf8\xf8\xf0\xff\xff\x60\xc0\x80\x00\x00\x3f\x03\x00\x1d\x3f\x7f\xff\xff\x7f\x3f\x1d\x00\x03\x3f\x00')
enemy2 = bytearray(b'\x10\x10\x00\xfc\x46\x23\x16\xdc\xa1\x6e\x6e\xa1\xdc\x16\x23\x46\xfc\x00\x00\x55\x10\x0a\x00\x02\x08\x10\x10\x08\x02\x00\x0a\x10\x55\x00')
enemy2mask = bytearray(b'\x10\x10\x00\xfc\xfe\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xfe\xfc\x00\x00\x7f\x1f\x0f\x07\x07\x0f\x1f\x1f\x0f\x07\x07\x0f\x1f\x7f\x00')
explosion1 = bytearray(b'\x10\x10\x00\x00\x00\x00\x90\x40\x40\x20\x40\x40\x84\x00\x10\x00\x00\x00\x00\x00\x04\x00\x00\x05\x01\x02\x01\x21\x00\x04\x00\x00\x00\x00')
explosion2 = bytearray(b'\x10\x10\x00\x00\x00\x00\x88\x60\x24\x10\x20\x60\x80\x00\x12\x00\x00\x00\x00\x40\x02\x00\x00\x03\x02\x24\x02\x03\x00\x00\x00\x44\x00\x00')
explosion3 = bytearray(b'\x10\x10\x00\x00\x60\x44\x84\x40\xa6\x14\x10\x20\x42\x82\x00\x08\x40\x00\x00\x08\x00\x08\x01\x22\x04\x4b\x48\x05\x02\x01\x00\x60\x06\x00')
explosion4 = bytearray(b'\x10\x10\x00\x00\x00\x18\xa8\xc8\xf0\xf0\xf0\xe0\xe8\xb8\x08\x00\x00\x00\x00\x00\x00\x30\x39\x17\x17\x1f\x0f\x17\x13\x21\x78\x20\x00\x00')
explosionAnim = dolp.Animation([explosion1, explosion2, explosion3, explosion4], [100, 100, 100, 100])

# Entity types
BULLET_TYPE = 0
ENEMY_TYPE  = 1

LIVE_TIMEOUT = 0
def update_explosion(obj):
	t = obj.get_timeout(LIVE_TIMEOUT)
	if dolp.check_timeout(t):
		dolp.delete_entity(obj)
def explosion(x, y):
	obj = dolp.new_entity()
	obj.configure(x, y, 0, 0)
	t = obj.new_timeout(LIVE_TIMEOUT)
	dolp.set_timeout(t, 400, False)
	obj.set_animation(explosionAnim)
	obj.update(update_explosion)

def update_bullet(obj):
	if not obj.is_moving():
		dolp.delete_entity(obj)
def spawn_bullet(x, y):
	w, h = 2, 4
	speed = 10
	obj = dolp.new_entity()
	obj.set_type(BULLET_TYPE)
	obj.configure(x, y, w, h)
	obj.move_to(x, dolp.height() - 10, speed)
	obj.collision()
	obj.update(update_bullet)

def update_ship(obj):
	w, h = 16, 16
	if dolp.pressed(dolp.BUTTON_A):
		spawn_bullet(obj.get_x(), obj.get_y() + int(h/2))
def spawn_ship():
	w, h = 16, 16
	obj = dolp.new_entity()
	obj.configure(int(dolp.width() / 2), int(w/2), w, h)
	obj.set_image(spaceship)
	obj.update(update_ship)

class Enemy:
	ENEMY_HIT_STATE = 0
	w, h = 16, 16
	count = 0

	def collision(obj, other):
		if other.get_type() != BULLET_TYPE:
			return
		if obj.get_state(Enemy.ENEMY_HIT_STATE) == 1:
			return
		dolp.delete_entity(obj)
		dolp.delete_entity(other)
		explosion(obj.get_x(), obj.get_y())
		obj.set_state(Enemy.ENEMY_HIT_STATE, 1)
		Enemy.count -= 1

	def update(obj):
		if not obj.is_moving():
			randX = random.randint(10, 100)
			randY = random.randint(16 + 8, dolp.height() - 8)
			obj.move_to(randX, randY, 5)

	def spawn():
		if Enemy.count > 4:
			return
		obj = dolp.new_entity()
		Enemy.count += 1
		obj.configure(0, dolp.height() - 8, 16, 16)
		obj.set_type(ENEMY_TYPE)
		obj.set_image(enemy2, enemy2mask)
		if random.randint(0, 1) == 1:
			obj.set_image(enemy1, enemy1mask)
		obj.update(Enemy.update)
		obj.collision(Enemy.collision)
		obj.set_state(Enemy.ENEMY_HIT_STATE, 0)

# setup
dolp.begin()
spawn_timeout = dolp.new_timeout()
dolp.set_timeout(spawn_timeout, 1000, True)
spawn_ship()

# loop
while True:
	dolp.loop_begin()
	if dolp.check_timeout(spawn_timeout):
		Enemy.spawn()
	dolp.loop_end()
