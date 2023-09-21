
The graphics pipeline is a series of steps used to create a 2-D raster representation of a 3-D scene.

A raster is a 2-D rectangular grid of pixels. 

### Pixels and Frames 

A pixel has two properties: a colour and a position. 
Colour is expressed in RGB (Red-Green-Blue) components - typically 8 bits per component or 24 bits per pixel (or _true colour_). 
The position is expressed in terms of (x, y) coordinates. 

The number of colour-bits per pixel is called the _depth_ (or _precision_) of the display. The number of rows by columns of the rectangular grid is called the _resolution_ of the display, which can range from 640x480 (VGA), 800x600 (SVGA), 1024x768 (XGA) to 1920x1080 (FHD), or even higher.

### Frame Buffer and Refresh Rate

The colour values of the pixels are stored in a special part of graphics memory called _frame buffer_.
The GPU writes the color value into the frame buffer.

The display reads the color values from the frame buffer row-by-row, from left-to-right, top-to-bottom, and puts each of the values onto the screen. This is known as _raster-scan_.

The display refreshes its screen several dozen times per second, typically 60Hz for LCD monitors and higher for CRT tubes. This is known as the _refresh rate_.

A complete screen image is called a _frame_.

### Double Buffering and VSync

While the display is reading from the frame buffer to display the current frame, we might be updating its contents for the next frame (not necessarily in raster-scan manner). This would result in the so-called _tearing_, in which the screen shows parts of the old frame and parts of the new frame.

This could be resolved by using so-called _double buffering_. Instead of using a single frame buffer, modern GPU uses two of them: a _front buffer_ and a _back buffer_. The display reads from the front buffer, while we can write the next frame to the back buffer. When we finish, we signal to GPU to swap the front and back buffer (known as _buffer swap_ or _page flip_).

Double buffering alone does not solve the entire problem, as the buffer swap might occur at an inappropriate time, for example, while the display is in the middle of displaying the old frame. This is resolved via the so-called _vertical synchronization_ (or _VSync_) at the end of the raster-scan. When we signal to the GPU to do a buffer swap, the GPU will wait till the next VSync to perform the actual swap, after the entire current frame is displayed.

The most important point is: When the VSync buffer-swap is enabled, you cannot refresh the display faster than the refresh rate of the display! For the LCD/LED displays, the refresh rate is typically locked at 60Hz or 60 frames per second, or 16.7 milliseconds for each frame. Furthermore, if you application refreshes at a fixed rate, the resultant refresh rate is likely to be an integral factor of the display's refresh rate, i.e., 1/2, 1/3, 1/4, etc.

# 3-D Graphics Pipeline

![[3D Graphics Pipeline.png]]

The 3D graphics rendering pipeline consists of the following main stages:

1. Vertex Processing: Process and transform individual vertices.
2. Rasterization: Convert each primitive (connected vertices) into a set of fragments. A fragment can be treated as a pixel in 3D spaces, which is aligned with the pixel grid, with attributes such as position, color, normal and texture.
3. Fragment Processing: Process individual fragments.
4. Output Merging: Combine the fragments of all primitives (in 3D space) into 2D color-pixel for the display.