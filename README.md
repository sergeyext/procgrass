# Procedural Grass

This is OpenGL demo program which procedurally generates lots of geometry from a minimal amount of initial data. Five programmable shader stages available in OpenGL 4 are used.

Hardware requirements
---

 - OpenGL 4.1 compatible video board

Software requirements
---

 - Up-to-date video driver

 - Qt5 toolkit
 
 - C++11 compiler

Build and run
---

The demo may be build with a straightforward Qt5 building process. On Linux it may look like this:

```
git clone https://github.com/sergeyext/procgrass.git
cd procgrass/
mkdir build
cd build/
qmake ..
make
```

Note that some distributions still provide Qt4 as main Qt version, so qmake binary name for Qt5 may look like
`qmake-qt5` or any other distribution-dependent name.

All grass.* and *.glsl files from source directory must be placed into binary directory.

Links
---
Cellular and Classic noise functions are (C) [Stefan Gustavson](https://github.com/stegu/webgl-noise)

Step-by-step pipeline and math description in Russian: https://habrahabr.ru/post/314532/
