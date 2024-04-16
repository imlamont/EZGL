# EZGL

A basic library for interfacing with OpenGL. Expaneded from the graphcis engine made in the UPenn course CIS 4600.

---

# Features

- `Drawable` - a class for handing VBOs of objects to be drawn by a shader
- `InstancedDrawable` - a child of `Drawable` for instanced rendering
- `ShaderProgram` - a class for compiling shader programs, handing vertex attribute pointers, and drawing the VBOs described by `Drawable`
- `Camera` - a class for easily creating a view and projection matrix from a given camera position and look vector