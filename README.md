OpenGL Endeavours
=================

How to compile and run
---------------

####From Terminal

On OS X:
```
cc -o out.exe src/main.cpp -lglfw3 -framework Cocoa -framework OpenGL -framework IOKit -framework CoreVideo && ./out.exe
```

####CLion and CMake: 

CMake works, so simply hit RUN and do good things.

It should be noted that GLEW does not have CMake style make files. This is a problem that I have yet to
resolve. For now, the only way to include it into the project is to manually install it based on the 
instructions they give [here](https://github.com/LuaDist/glew).

Notes
------

This only works on Mac OS X, for now.

Will extend to other operating systems in the future.
