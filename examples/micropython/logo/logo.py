import random

import dolp

arduinoImg = bytearray(b'\x0F\x08\x3c\x66\xc2\x92\xd2\x46\x6c\x38\x6c\x46\xd2\x92\xc2\x66\x3c')
maskImg = bytearray(b'\x0F\x08\x3c\x66\xc2\x92\xd2\x46\x6c\x38\x6c\x46\xd2\x92\xc2\x66\x3c') 

dolp.begin()

def logo_update(logo):
	if not logo.is_moving():
		logo.move_to(random.randint(0, 128), random.randint(0, 64), 6)

for i in range(10):
	e = dolp.new_entity()
	e.configure(random.randint(0, 128), random.randint(0,64), 10, 10)
	e.update(logo_update)
	e.set_image(arduinoImg, maskImg)

while True:
	dolp.loop()
