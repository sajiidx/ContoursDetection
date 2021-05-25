g++ -c -fPIC gaussianBlur.cpp && 
swig -c++ -python gaussianBlur.i && 
g++ -c -fPIC gaussianBlur_wrap.cxx -I/usr/include/python3.9 -I/usr/lib/python3.9 && 
g++ -shared -Wl,-soname,_gaussianBlur.so -o _gaussianBlur.so gaussianBlur.o gaussianBlur_wrap.o && 
g++ -c -fPIC grayscale.cpp && 
swig -c++ -python grayscale.i && 
g++ -c -fPIC grayscale_wrap.cxx -I/usr/include/python3.9 -I/usr/lib/python3.9 && 
g++ -shared -Wl,-soname,_grayscale.so -o _grayscale.so grayscale.o grayscale_wrap.o && 
g++ -c -fPIC sobel.cpp && 
swig -c++ -python sobel.i && 
g++ -c -fPIC sobel_wrap.cxx -I/usr/include/python3.9 -I/usr/lib/python3.9 && 
g++ -shared -Wl,-soname,_sobel.so -o _sobel.so sobel.o sobel_wrap.o