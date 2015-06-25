
#!/bin/bash

if [[ ! -d "deps" ]]; then
  mkdir deps
  cd deps

  # glfw
  git clone https://github.com/glfw/glfw.git
  cd glfw
  mkdir build
  cd build
  cmake ..
  make
  sudo make install
  cd ../../

  # glew
  git clone https://github.com/nigels-com/glew.git
  cd glew
  make -C auto
  sudo make install
  sudo make clean
  cd ..

  # glm 
  curl -o glm.zip -L http://sourceforge.net/projects/ogl-math/files/glm-0.9.6.1/glm-0.9.6.1.zip/download
  unzip glm.zip 
  rm glm.zip
  cd glm
  mkdir build
  cd build
  cmake ..
  make 
  sudo make install

  cd ../../../
fi

rm -rf build
mkdir build
cd build
cmake ..
make
shopt -s extglob
rm -rf !(VirtualVista)
shopt -u extglob

