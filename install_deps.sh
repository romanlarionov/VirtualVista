#!/bin/bash

# Roman Larionov
# it is assumed that on OS X, you have XCode & Command Line Tools installed. 

if [{uname -o} == "Linux"]; then
  sudo apt-get install xorg-dev libglu1-mesa-dev libXmu-dev libXi-dev dos2unix wget
fi

if [ ! -d "deps" ]; then
  mkdir deps
fi

cd deps

# glfw
if [ ! -d "glfw" ]; then
  git clone https://github.com/glfw/glfw.git
  cd glfw
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
  sudo make install
  cd ..
fi

# glm
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

cd ../
echo "Complete Dependency Downloads"
