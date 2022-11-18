mkdir build
cp main.cpp build/
cp Class.h build/
cp test_suite/ClassWithFixedSize.h build/
cp Class.cpp build/
g++ -std=c++0x build/Class.cpp build/main.cpp -o build/main
./build/main
