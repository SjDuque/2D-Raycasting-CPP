# 2D-Raycasting-CPP

Simple raycasting program made in C++.

Raylib was used to draw to the screen.

*Although I recommend installing Raylib through a package manager, this project doesn't require you to have raylib installed at all. In the event that CMake cannot find Raylib, it'll automatically install everything you need into the project's build directory.*

## Downloading

You can either use `git`, `curl`, or `wget` to download the repository.

(Recommended) Using git:

```
git clone --depth=1 https://github.com/SjDuque/2D-Raycasting-CPP
rm -rf 2D-Raycasting-CPP/.git
```

Using curl:

```
curl -L https://github.com/SjDuque/2D-Raycasting-CPP/archive/main.zip -o 2D-Raycasting-CPP.zip
unzip 2D-Raycasting-CPP.zip
rm -rf 2D-Raycasting-CPP.zip
```

Using wget:

```
wget https://github.com/SjDuque/2D-Raycasting-CPP/archive/main.zip -O 2D-Raycasting-CPP.zip
unzip 2D-Raycasting-CPP.zip
rm -rf 2D-Raycasting-CPP.zip
```

## Building

```
cd 2D-Raycasting-CPP
mkdir build
cd build
cmake ..
cmake --build .
```

## Acknowledgement Stuff
Project Template: https://github.com/SjDuque/Raylib-CMake
Algorithm: https://en.wikipedia.org/wiki/Line%E2%80%93line_intersection#Given_two_points_on_each_line_segment
