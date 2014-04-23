/** \mainpage the mainpage *\
#WICK GUIDE (READ THIS!)#
Wick is fully documented, but some elements of library do need some explaining. Here are some things you should know about wick before you use it.
#A. Struct Overview#

Wick uses structs to store information. Wick's structs represent "game objects", such as Images and Text. There are not very many of them, so I can give you an quick overview.

**Game**
One instance of Game should exist throughout the life of the entire program. As the name suggests, it represents the entire Game. 

**Pair**
A Pair is simply a Pair of double precision floating point numbers. Pairs represent coordinates, 2D vectors, 2D dimensions, and basically everything 2D.

**Color**
Color represents an RGBA color.

**Polygon**
A filled Polygon which can be drawn to the screen. A Polygon can be moved, scaled, rotated, and colored.

**Quad**
A filled rectangle which can be drawn to the screen. A Quad can be moved, scaled, rotated, and colored. 

**Texture**
A Texture is a texture loaded from either the file system of some buffer of unsigned chars. 

**Image**
An Image can be drawn to the screen. It derives its data from some Texture. Images can be moved, scaled, rotated, and colored.

**Bounds**
A Bounds is a bounding rectangle. It is usually used to define what part of a Texture and Image should use for drawing.

**Font**
A Font at a specific point size loaded from a file.

**Text**
A Text can be drawn to the screen. It derives its data from some string and a Font. A Text can be moved, scaled, rotated, and colored.

#B. Struct Initialization#
Pair and Bounds should be initialized manually.
`Pair a = {0,0};`
`Bounds b = {(Pair) {0,0}, (Pair) {64,64)}};` 

However, most structs really shouldn't be initialized manually. These structs use an "init" function. An init function always has the name init_structname, where struct name is the all-lowercase name of the struct. 

Thus, to initialize a color, for example:
Color target;
`init_color(&target, 0, 0, 0, 255);` 

The use of an init function ensures that more complex structs are initialized completely and correctly, and also allows for error reporting (which we'll discuss after another section).

#C. Memory management#
Some structs need to be freed once you're done with them. With Structs that need to be freed, you'll see a "free" function that coorosponds to the struct. Similar to the init function, free functions are named free_structname, which struct name is the all-lowercase name of the struct. For example:

`Texture texture;`
`/* initialize texture via init_texture */`
`/* do stuff involving texture */`
`free_texture(&texture);`

In this example, texture is allocated on the stack. Once free_texture is called, texture is still on the stack, but all the heap space given to elements of texture is gone. 

Alternatively, one can store a Texture (or any other struct) on the heap:

`Texture* texture = malloc(sizeof(Texture));`
`/* initialize texture via init_texture */`
`/* do stuff involving texture */`
`free_texture(texture);`
`free(texture);`

free_texture still only deallocates the heap space given to *elements* of texture. A final "free" is required to completely deallocate the texture.

#D. Modifying structs#
Most elements in a given struct can be modified directly. For example the following is totally safe:

`Image image;`
`/* initialize image via init_image */`
`image.location = (Pair) {50,50};`

However, some elements (which are undocumented) should not be modifed directly. The name of these elements starts with "p_", the p standing for "private". These elements either should never be modifed, or can be modified correctly only through a function. For example, the the p_dimensions element in Quad should not be modified directly. Instead, the following function should be used instead:

`int set_quad_dimensions(Quad* target, Pair dimensions)`

#E. Error reporting#
Many functions in wick return integer "error codes". Such functions return 0 on success and some code less than 0 on failure. These codes can be translated via:

`const char* translate_error_code(int code)`

If, for some reason, you don't have access to the error code, the last reported error code can be fetched via:

`int get_last_error()`

If a function fails, returning a negative integer, wick guarantees (unless otherwise noted) that no variables, pointers, or anything will be modified. 

#F. Units#
Wick uses the same units across all structs and functions.

**Screen coordinates** are measured in pixels from the lower left corner of the window.

**Coordinates in general** are measured in pixels.

**Rotation** is measured in radians from the positive x axis.

**Scale values** are measured with Pairs, where each element in the Pair is a multipier for the scale. For example, a scale value of(1,1) is original size, which a scale value of (0.5,0.5) is half size.

Some game objects, like Polygons and Quads, take vertices. These vertices are ***relative to the object**, meaning that they're measured in pixels relative to the object's location.
