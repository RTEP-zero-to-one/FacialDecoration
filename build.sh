if [ ! -d "build" ];then
   mkdir -p "build"
fi
cd build
cmake -B . -DCMAKE_BUILD_TYPE=Release
cmake --build . --config Release
make
cp FacialDecoration ..
cd ..
./FacialDecoration