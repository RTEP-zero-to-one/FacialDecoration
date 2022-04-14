if [ ! -d "build" ];then
   mkdir -p "build"
fi
cd build
cmake -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build --config Debug
cd build && make