if [ ! -d "build" ];then
   mkdir -p "build"
fi
cmake -B build/ -DCMAKE_BUILD_TYPE=Release
cmake --build build/ --config Release
make
cp build/FacialDecoration .
./FacialDecoration