
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

if [[ ! -d "build" ]]; then
  mkdir build
fi

cd build
cmake -DGLFW_BUILD_DOCS=OFF -DGLFW_BUILD_EXAMPLES=OFF -DGLFW_BUILD_TESTS=OFF ..
make


