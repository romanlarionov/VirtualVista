
mkdir build
cd build
cmake ..
make
shopt -s extglob
rm -rf !(VirtualVista.exe)
shopt -u extglob

