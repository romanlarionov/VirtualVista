#!/bin/bash
if [ ! -d "build" ]; then
  mkdir build
fi

cd build
cmake -DGLFW_BUILD_TESTS=OFF -DGLFW_BUILD_EXAMPLES=OFF -DGLFW_BUILD_DOCS=OFF ..
make
./VirtualVista
cd ..
