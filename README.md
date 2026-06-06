*This project has been created as part of the 42 curriculum by rluis-ya and jcesar-s.*

# miniRT

## Description

miniRT is a foundational ray tracer engine written in C. The goal of the project is to generate a photorealistic scene by modeling light transport using the ray tracing technique. Ray tracing simulates the physical behavior of light by casting rays from a virtual camera through each pixel of an image plane and computing their interactions with scene objects. This technique produces highly accurate reflections, shadows, and lighting effects, offering a significant improvement in image fidelity over traditional rasterization methods at the cost of greater computational complexity.

> "This technique was first deployed in applications where taking relatively long time to render could be tolerated" — [Wikipedia](https://en.wikipedia.org/wiki/Ray_tracing_(graphics))

As hardware has become increasingly powerful with the creation of specialized units for linear algebra operations, ray tracing has become an industry standard for high-quality, realistic computer graphics. Most triple-A games and professional rendering pipelines now utilize this technique to render digital objects.

This project implements a CPU-based ray tracer capable of rendering spheres, planes, and cylinders with support for translations, rotations, multiple light sources, shadows, and camera positioning.

## Instructions

### Prerequisites

- A Unix-like operating system (Linux)
- GCC or Clang compiler
- X11 development libraries (for MiniLibX on Linux)
- GNU Make

### Compilation

To compile the project, run the following command from the repository root:

```bash
make
```

This will compile all source files and produce the executable named `miniRT` in the `build/` directory. The Makefile handles dependencies automatically and does not require a re-link step if object files are already up to date.

To clean compiled objects:

```bash
make clean
```

To remove all generated files including the executable:

```bash
make fclean
```

### Execution

Run the program with a single argument: the path to a valid scene file with the `.rt` extension.

```bash
./build/miniRT <scene.rt>
```

Example:

```bash
./build/miniRT review_files/basic_sphere.rt
```

A window will open displaying the rendered scene. You can interact with the window as follows:

- **ESC** — closes the program cleanly.
- **Red cross / close button** — closes the program cleanly.
- **Minimize / maximize / resize** — the window content remains consistent.

### Scene File Format

Scene files use the `.rt` extension and define the scene line by line:

| Element | Format | Example |
|---------|--------|---------|
| Ambient | `A ratio R,G,B` | `A 0.2 255,255,255` |
| Camera | `C x,y,z dx,dy,dz fov` | `C 0,0,-10 0,0,1 70` |
| Light | `L x,y,z brightness R,G,B` | `L -5,5,-5 0.7 255,255,255` |
| Sphere | `sp x,y,z diameter R,G,B` | `sp 0,0,0 4 255,0,0` |
| Plane | `pl x,y,z nx,ny,nz R,G,B` | `pl 0,0,0 0,0,1 0,255,0` |
| Cylinder | `cy x,y,z dx,dy,dz diameter height R,G,B` | `cy 0,0,0 0,1,0 3 10 0,0,255` |

The program will print an error and exit with code `2` if the file is misconfigured or does not end with `.rt`.

## Features

- **Basic shapes**: Sphere, plane, and cylinder rendering
- **Transformations**: Translation and rotation of scene objects
- **Multi-object scenes**: Support for intersecting and duplicate objects
- **Camera system**: Flexible positioning and orientation along any axis
- **Lighting**: Ambient and point light sources with brightness ratios
- **Shadows**: Accurate shadow casting from objects onto other surfaces
- **MLX window management**: Resizable, minimizable, and stable display window

## Technical Choices

- **Language**: C (compliant with the 42 norm)
- **Graphics library**: MiniLibX (42's lightweight X11 wrapper)
- **Math**: Custom linear algebra library for vectors, matrices, and transformations
- **Rendering**: CPU-based ray tracing with per-pixel color computation
- **Memory**: Manual allocation with careful cleanup on error paths

## Resources

### Classic References

- *Ray Tracing in One Weekend* — Peter Shirley (essential introductory series)
- *Physically Based Rendering: From Theory to Implementation* — Matt Pharr, Wenzel Jakob, Greg Humphreys
- [Wikipedia: Ray Tracing (graphics)](https://en.wikipedia.org/wiki/Ray_tracing_(graphics))
- [Scratchapixel: Ray Tracing](https://www.scratchapixel.com/lessons/3d-basic-rendering/introduction-to-ray-tracing.html)
- 42 Subject PDF — miniRT project specifications and evaluation criteria

### AI Usage

Artificial intelligence tools were used during this project for the following tasks:

- **Test suite generation**: AI was used to create a comprehensive set of `.rt` scene files and misconfiguration test cases to verify parser behavior, rendering output, and edge-case handling. The generated files cover all mandatory evaluation requirements (basic shapes, transformations, multi-object scenes, camera positioning, lighting, and shadows).
- **Documentation assistance**: AI was used to structure and draft this README.md file to ensure compliance with 42 curriculum standards.
- **Debugging guidance**: AI was consulted for interpreting MLX behavior, exit code handling, and bash scripting for automated test runners.

All core ray tracing algorithms, linear algebra implementations, and parser logic were written and debugged manually by the project author(s).
