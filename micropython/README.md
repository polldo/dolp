
How to build:

Clone micropython repo with its submodules (you'd better cherry-pick the needed submodules)
`$ git clone --recurse-submodules -j8 https://github.com/micropython/micropython-lib.git`

Build cross-compiler
```
$ cd micropython
$ make -C mpy-cross
```

Go to the board folder
`$ cd ports/rp2/`

Change the configuration according to your needs in the board's folder `ARDUINO_NANO_RP2040_CONNECT`
You may need to disable some feature to save memory

Build
`$ make -j 8 BOARD=ARDUINO_NANO_RP2040_CONNECT USER_C_MODULES=/path-to-dolp/dolp/micropython/micropython.cmake`
