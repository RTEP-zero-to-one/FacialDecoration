if [ ! -d "build" ];then
   mkdir -p "build"
fi
cmake -B build/ -DCMAKE_BUILD_TYPE=Release
cmake --build build/ --config Release
cd build && make -j4
cd .. && cp build/FacialDecoration .
echo "Success! Now Run with ./FacialDecoration"