WickEngine_DirectX
====

The Wick Engine library written for C++ and DirectX.

WickEngine_DirectX was my first attempt at a game engine. 
All the code is in the project's root directory. 
A debug build can be found in Debug, and a release build can be found in Release. Builds are static libraries (.a files).

WickEngine_DirectX has a variety of problems. In no particular order...
1. It duplicates some functionality already in the C++ standard library.
2. It's state system is too complex.
3. It's not cross platform because it uses DirectX. 
4. It's too difficult to determine where errors happen.
5. It duplicates some functionality already in the C++ language (aka the release() method replaces destructors).
6. It has some unnessesary complexities. For example, the Graphics and Input classes could be combined into a "SystemInterface" class.
7. Some classes really don't need to be classes. For example, Input does not necessarly need to be a class.

I hope to fix all these problems, simplify, and add a lot of new, advanced functionality to my next project, WickEngine. 