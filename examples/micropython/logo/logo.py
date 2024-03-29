import random

import dolp

arduinoImg = bytearray([0x0F, 0x08, 0x3c, 0x66, 0xc2, 0x92, 0xd2, 0x46, 0x6c, 0x38, 0x6c, 0x46, 0xd2, 0x92, 0xc2, 0x66, 0x3c])
maskImg = bytearray([0x0F, 0x08, 0x3c, 0x66, 0xc2, 0x92, 0xd2, 0x46, 0x6c, 0x38, 0x6c, 0x46, 0xd2, 0x92, 0xc2, 0x66, 0x3c]) 

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
