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

## How it draws a frame

- transform every vertex once with a single scale/rotate/translate matrix
- project to 2d, keeping the view space z for depth
- drop faces whose normal points away from the camera
- average the face normals onto the vertices for Gouraud shading
- shade by the dot product of the normal and a fixed light
- rasterise with barycentric weights, testing 1/z per pixel against the z buffer

The z buffer holds 1/z rather than z, so a bigger value means nearer and the
test is a plain greater than.

There is no near plane clipping, triangles with a corner closer than NEAR_Z are
just dropped. Walk far enough into a model and it disappears rather than
smearing across the screen.
