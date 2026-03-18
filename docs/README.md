# miniRT - a Raytracing Engine in C

## Description
This project has been created as part of the 42 curriculum by agara and hazunic.

### The "viewport"
To draw the picture we cast a ray from the camera through each pixel to compute the color. But where are the pixels? common approach is to use a viewport, a flat, 2D square in front of the camera, which represent our screen. We can change the width of this surface to set the right FOV, it wont work however in case of 180 FOV, because it would mean the camera is on the viewport and all the rays looking completely to the side, never what is in front of us. An other option is to implement a fisheye lens, using a curved surface as a viewport instead of flat one. It would look like a part of a spheres surface. That works well on 180 FOV, the camera casts rays the sides and to the front too, but it gives a distorted picture always, since our physical display is not curved. We didnt like the picture this approach draws on a normal FOV like 90. The solution for the problem is a spherical viewport, which can scale the radius of the sphere based on the recieved FOV value. in case of 180, the camera position is the same point as the center of the sphere. if we decrease the FOV the center moves behind the camera, creating a bigger sphere. This will mitigate the distortion, since our projected viewport is more similar to a flat surface.

### The rendering
The rendering process was guided by Data Oriented Design principals. This means we group frequently used data in arrays, not dynamically allocated. This way when we compute the first pixel, the computer loads relevant data (object geometry details, ray direction vectors) in the CPU cache memory. It will load the whole page, not only what we use at the moment. When we move on to the next pixels calculation we have the necesarry data already loaded in the cache, since the datapoints are neighbours in memory with the previous pixel!
The bonus version has no such optimisations, because of the anti aliasing implementation. One of our future plans is to use multiple threads on the bonus part. The other option is using interpolation to approximate efficiently insead of doing all calculations for each pixel.

### The shading

### Mandantory features
- Colorful ambient lightning
- Only white diffuse lightning
- Basic shapes: sphere, plane, cylider
### Bonus features
- Colorful diffuse lightning
- Specular lightning
- Multiple spot light scources
- Multisampling Anti Aliasing - MSAA (the MSAA resolution can be found in mrt.h under the MSAA macro)

## Instructions
### Build
make
### Build with bonus features
make bonus
### Testrun
./minirt tests/testfiles/mini.rt
### Draw your scene
The .rt file has to have a Camera('C'), an ambient value('A') and a spot light scource('A'), or more spot with bonus.
Its possibe to render 3 shapes:
- Spheres ('sp') defined by coordinates of center(x,y,z), length of radius and color
- Cylinder ('cy') defined by coordinates of center(x,y,z), length of radius, height of axis and color
- Planes ('pl') defined by coordinates of a point, normalvector and color
- the colors expected in R,G,B values between 0 - 255
- the vectors expected stricktly as normalized unit vectors
- the parsing is rigorous, the program expects a comma with no spaces between coordinates and color values!
- Example
```bash
A 0.8 255,0,0
C -10,0,0 1,0,0 120
L -20,0,15 0.8 0,0,255
sp 14,10,0 2 0,255,0
pl 0,0,-2 0,0,1 180,180,180
cy 10,0,1 0,0,1 4 6 0,0,255
```
## RESOURCES - LINKS

- [PLOTS-GRAPHS](https://academo.org/demos/)
- [README](https://readme.so/de/editor)
- [RAY-TRACING-PRIMITIVES](https://www.cl.cam.ac.uk/teaching/1999/AGraphHCI/SMAG/node2.html)
- [SHAPES](https://hugi.scene.org/online/hugi24/coding%20graphics%20chris%20dragan%20raytracing%20shapes.htm)
- [RAY-DISK-INTERSECION](https://www.scratchapixel.com/lessons/3d-basic-rendering/minimal-ray-tracer-rendering-simple-shapes/ray-plane-and-ray-disk-intersection.html)
- [CYLINDRICAL-COORDINATE-SYSTEM](https://en.wikipedia.org/wiki/Cylindrical_coordinate_system)
- [GPROF-INFO](https://www.thegeekstuff.com/2012/08/gprof-tutorial/)



- [PHOTO-VIDEO-CALULCATORS](https://www.omnicalculator.com/other#:~:text=Photo%20and%20video%20calculators)
- [LINEAR-ALGEBRA-CALCULATOR](https://www.omnicalculator.com/math#:~:text=Linear%20algebra%20calculators)
- [TRIG-CALCULATOR](https://www.omnicalculator.com/math#:~:text=Tensor%20Product%20Calculator-,Trigonometry%20calculators,-%F0%9F%93%90)
- [CYLINDER-INTERSECTION](https://www.youtube.com/watch?v=6VHpZYTHZG4&pp=ygUSY3lsaW5kZXIgcmF5dHJhY2Vy)


- [EXAMPLE-DOCUMENTATION](https://ygor-sena.github.io/42cursus-miniRT/structs__camera.html#a8944ccdbc9a175ea4cdb00439aaad118)
