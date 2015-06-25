Virtual Vista
=================

Soon to be procedural graphics engine.

Build
---------------

####OS X:

Make sure to run the build script first to install dependencies.
``` bash
./compile.sh
```

The output executable will be in the generated build directory.
``` bash 
./VirtualVista
```

Note: Glew is a pain to link correctly; if the build doesn't work because of it, install global static libraries and be done with it.

####CLion:

I suggest building with CLion if on Unix platform. I have yet to make things work for Visual Studio.
