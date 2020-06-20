# Simple-Mandelbrot-explorer
A minimalist Mandelbrot set explorer using SFML.

![N|Solid](/images/image1.png)
![N|Solid](/images/image2.png)

## Installation

Just clone or download this repo. You'll need to install SFML and CMake.

1. Install SFML from here: https://www.sfml-dev.org/download/sfml/2.5.1/ and put it on an standard installation path:
On Windows it's "C:\Program Files", on Linux it's "/usr/lib"

2. Install Cmake from here: https://cmake.org/download/

3. On the repository folder, run from the command prompt: (or use the CMake GUI selecting your C++ compiler and where to build the binaries)
```
cmake .
```
4. Compile the code with your C++ compiler and the generated proyect.

## Controls

* **W**: move Up
* **S**: move down
* **A**: move left
* **D**: move right
* **V**: increases samples per pixel
* **C**: decreases samples per pixel
* **Z**: increases max iterations
* **X**: decreases max iterations
* **1**: change colormap to COLORMAP_1  (image1.png)
* **2**: change colormap to COLORMAP_2  (image2.png)
