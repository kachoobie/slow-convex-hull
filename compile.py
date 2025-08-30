import os

os.system("clang++ -std=c++20 -o exec main.cpp src/*.cpp -I include `pkg-config --libs --cflags sdl3`")