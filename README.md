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

With no argument it draws the built in cube. Give it an OBJ and it scales the
model to a unit radius and picks the fov from the window size, so any model
turns up on screen at a sensible size.

## Keys

| key       | action                     |
|-----------|----------------------------|
| tab       | wireframe / solid / both   |
| g         | flat or gouraud shading    |
| c         | backface culling on or off |
| w a s d   | move the camera            |
| space     | pause the spin             |
| arrows    | turn the model             |
| + / -     | zoom                       |
| esc       | quit                       |
