# dolp on micropython

Here's the external module for micropython that exposes dolp APIs.

In `release` folder there are some ready to upload micropython binaries with this module compiled on top.

## Get started

Upload to your board the binary corresponding to the hardware you're going to use.
Access the REPL via USB Serial (more on [raspberry](https://www.raspberrypi.com/documentation/microcontrollers/micropython.html) and [micropython](https://docs.micropython.org/en/latest/reference/repl.html))

On linux:
```console
$ minicom -D /dev/ttyACM0
```
Access the Paste mode by pressing `Ctrl-E`, then paste your program and press `Ctrl-D`.
As an example, try to paste the following simple program (you can find it also in [examples](https://github.com/polldo/dolp/tree/master/examples/micropython)):
```python
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

```

## How to build:

If you are trying to port this module to another rp2040 board or you want to customize [dolp configuration](https://github.com/polldo/dolp/blob/master/micropython/micropython.cmake#L3-L5), then you need to build the binary yourself. These are the steps.

- Clone micropython repo with its submodules (you'd better cherry-pick the needed submodules):

```console
$ git clone --recurse-submodules -j8 https://github.com/micropython/micropython-lib.git
```

- Build cross-compiler:
```
$ cd micropython
$ make -C mpy-cross
```

- Go to the board folder:
```console
$ cd ports/rp2/
```

- Change the configuration according to your needs in your board's directory (i.e. `ARDUINO_NANO_RP2040_CONNECT`).
You may need to disable some feature to save memory.

- Build:
```console
$ make -j 8 BOARD=ARDUINO_NANO_RP2040_CONNECT USER_C_MODULES=/path-to-dolp/dolp/micropython/micropython.cmake
```
