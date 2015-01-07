
#!/bin/bash

if [[ ! -d "deps" ]]; then
	mkdir deps
	cd deps
	
	# glfw
	git clone https://github.com/glfw/glfw.git

	# glew
	git clone https://github.com/nigels-com/glew.git

	# glm 
	curl -o glm.zip -L http://sourceforge.net/projects/ogl-math/files/glm-0.9.6.1/glm-0.9.6.1.zip/download
	unzip glm.zip 
	rm glm.zip

	cd ..
fi

mkdir build
cd build
cmake ..
make
shopt -s extglob
rm -rf !(VirtualVista.exe)
shopt -u extglob

