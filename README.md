# 3d-renderer

A software rasteriser in C. No GPU, no OpenGL. SDL2 is only used to get a window
and push a pixel buffer to it.

It loads a wavefront OBJ, transforms it with 4x4 matrices, culls the back faces,
and fills the triangles with a z buffer and flat shading.

## Build

Needs SDL2 and its headers.

```
make build
./bin/renderer                      # spinning cube
./bin/renderer src/samples/bunny.obj
```
