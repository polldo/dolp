import dolp

arduinoImg = bytearray(b'\x0F\x08\x3c\x66\xc2\x92\xd2\x46\x6c\x38\x6c\x46\xd2\x92\xc2\x66\x3c')
maskImg = bytearray(b'\x08\x08\xf7\xbe\xff\xf7\x5f\xfe\xf7\xbd') 

dolp.begin()

ani = dolp.Animation([maskImg, arduinoImg], [200,200])
o = dolp.new_entity()
o.set_animation(ani)
o.configure(30,30,8,8)
