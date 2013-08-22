WickEngine_DirectX
====

The Wick Engine library written for C++ and DirectX.

WickEngine_DirectX was my first attempt at a game engine. 
All the code is in the project's root directory. 
A debug build can be found in Debug, and a release build can be found in Release. 

WickEngine_DirectX has a variety of problems. In no particular order...
1. It duplicates some functionality already in the C++ standard library.
2. It's state system is too complex.
3. It's not cross platform because it uses DirectX. 
4. It's too difficult to determine where errors happen.
5. It duplicates some functionality already in the C++ language (aka the release() method).

I hope to fix all these problems and add a lot of new, advanced functionality to my next project, WickEngine. 