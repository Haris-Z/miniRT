# miniRT - a Raytracing Engine in C

## Description
This project has been created as part of the 42 curriculum by agara and hazunic.

### Mandantory features
- Colorful ambient lightning
- Only white diffuse lightning
- Basic shapes: sphere, plane, cylider
### Bonus features
- Colorful diffuse lightning
- Specular lightning
- Multiple spot light scources
- Multisampling Anti Aliasing - MSAA

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
#### the colors expected in R,G,B values between 0 - 255
#### the vectors expected stricktly as normalized unit vectors
#### Example
A 0.8 255,0,0 
C -10,0,0 1,0,0 120 
L -20,0,15 0.8 0,0,255 
sp 14,10,0 2 0,255,0 
pl 0,0,-2 0,0,1 180,180,180 
cy 10,0,1 0,0,1 4 6 0,0,255 

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
