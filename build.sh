if [ ! -d "build" ];then
   mkdir -p "build"
fi
cd build
cmake -B . -DCMAKE_BUILD_TYPE=Debug
cmake --build . --config Debug
make
cp QtTest ..