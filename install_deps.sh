#!/bin/bash

# Roman Larionov
# it is assumed that on OS X, you have XCode & Command Line Tools installed.

if [ "$(lsb_release -si)" == "Ubuntu" ]; then
  sudo apt-get install g++ curl git cmake xorg-dev libglu1-mesa-dev libXmu-dev libXi-dev dos2unix wget libboost-dev zlib1g-dev
fi

if [ ! -d "deps" ]; then
  mkdir deps
fi

if [ ! -d "bin" ]; then
  mkdir bin && cd bin
  mkdir include && cd include
  mkdir SOIL assimp
  cd ../../
fi

cd deps

if [ ! -d "glfw" ]; then
  git clone https://github.com/glfw/glfw.git
  cd glfw
  git checkout 29b40112c234c3021648ea42a5e74cc122ba08b4
  mkdir build
  cd build
  cmake ..
  make
  sudo make install
  cd ../../
fi

if [ ! -d "glew" ]; then
  curl -o glew.tgz -L http://sourceforge.net/projects/glew/files/glew/1.12.0/glew-1.12.0.tgz/download
  tar -zxvf glew.tgz
  rm glew.tgz
  mv glew-1.12.0 glew
  cd glew
  make
  cd ..
fi

if [ ! -d "glm" ]; then
  curl -o glm.zip -L http://sourceforge.net/projects/ogl-math/files/glm-0.9.6.1/glm-0.9.6.1.zip/download
  unzip glm.zip 
  rm glm.zip
  cd glm
  mkdir build
  cd build
  cmake ..
  make 
  sudo make install
  cd ../../
fi

if [ ! -d "assimp" ]; then
  git clone https://github.com/assimp/assimp.git 
  cd assimp 
  git checkout 36c08a0a7df8f79d0abe869768f6b912c75f2969
  mkdir build 
  cd build 
  cmake -G 'Unix Makefiles' .. 
  make
  cd code
  cp libassimp.* ../../../../bin/
  cd ../../
  cp -r include ../../bin/
  cd ../
fi

if [ ! -d "soil" ]; then
  git clone https://github.com/kbranigan/Simple-OpenGL-Image-Library.git
  mv Simple-OpenGL-Image-Library soil
  cd soil
  mkdir build
  cd build
  cmake ..
  make
  cp libSOIL.a ../../../bin/
  cp -r ../src/*.h ../../../bin/include/SOIL/
  cd ../../
fi

cd ../
echo "Completed Dependency Downloads"
