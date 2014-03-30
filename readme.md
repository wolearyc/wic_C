wick readme
===========
Table of Contents
----------------- 

1. Summary
2. Directories and Files
3. Building wick
4. Licensing and Distribution
5. Credits

Summary
-------
Wick is a simple, object-oriented 2D game engine for Mac OSX written in C++ and distributed as a standalone static library. It is currently under development by Will  O'Leary. You can download files, read documentation, and submit bug reports at wick's [github repository](https://github.com/wolearyc/wick). 

Wick was built with a few design goals in mind:
* simplicity
* extendability
* effective and robust error reporting
* object-oriented-ness

Enjoy!

Directories and Files
---------------------

* license.md -- License. 
* readme.md -- Readme. 
* Makefile -- Makefile. 
* deps/ -- Dependency files.
    * lib/ -- Dependency libraries.
	* include/ -- Dependency header files.
* doc/ -- Doxygen documentation.
* include/ -- Header files.
* lib/ -- Dependency libraries.
* src/ -- Source files.
* bin/ -- Libraries [created on build].
    * debug/ -- Debug library (debug/libwick.a) [created on build].
    * release/ -- Release library (release/libwick.a) [created on build].
* obj/ -- Object files [created on build].
    * debug/ -- Debug objects [created on build].
    * release/ -- Release objects [created on build].
	
Building wick
-------------
Wick uses the standard "make" to build. No configure script is included, mostly because the makefile is so small and easy to modify. It should build on any system with g++, make, and binutils installed. 
From wick's root directory, the following make commands can be executed:

* $ make -- Builds wick as a static library.
* $ make all -- Functions identically to "$ make".
* $ make release -- Functions identically to "$ make".
* $ make debug -- Builds wick as a static library with debug symbols.
* $ make clean -- Removes all library and object files.

Using wick in your project
--------------------------
First, you'll need to include wick's header files.

1. Copy include/ and deps/ into your project.
2. In your project, delete deps/lib to save space. You won't be needing it.
3. Add include/ and deps/include as include paths. In g++, this can be done with "-I include/ -I deps/include", assuming include/ and deps/ are in your working directory.

Second, you'll need to link in the appropriate libraries and frameworks.

1. From wick's root directory, run $make.
2. Copy libwick.a from lib/release/ into your project. 
3. Link libwick.a to your project. In g++, this is done with "-lwick" assuming that libwick.a is in your working directory.
4. You'll also need to link in the Cocoa, Quartz, IOKit, and OpenGL frameworks. In gcc, this can be done with "framework Cocoa -framework Quartz -framework IOKit -framework OpenGL".

Lastly, you'll need to include "Wick.h" in all the code you write. Also, make sure you're compiling with the C++11. Then you should be good to go!

Licensing and Distribution
--------------------------
Wick is distrubuted under the GNU Lesser General Public License, Version 3. You must include license.md in all projects which use the entirety or sections of wick.

Credits
-------
Portions of this software are copyright © 2013 The FreeType Project.  All rights reserved. [Website.](http://www.freetype.org/)

Portions of this software use GLFW. Copyright © 2002-2006 Marcus Geelnard and Copyright © 2006-2011 Camilla Berglund. [Website.](http://www.glfw.org/index.html)

Portions of this software use the Simple OpenGL Image Library, which is in the public domain. [Website.](http://www.lonesock.net/soil.html)