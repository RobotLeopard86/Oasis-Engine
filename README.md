# Oasis Engine ![Logo](Logos/oasislogo_singular.png)  
### A C++ game engine.  

## About  
This project was originally built by following tutorials by [TheCherno on YouTube](https://youtube.com/@TheCherno). The source code for the engine built in the tutorials can be found [here](https://github.com/TheCherno/Hazel). I eventually plan to expand Oasis Engine with more features after I complete the tutorials. Unlike the Hazel Engine from the videos, the entire full engine will be available for free once complete. Currently the engine is still in development.  

## Planned Features  
* Full 2D support  
* Full 3D support  
* Level editor  
* C# scripting system  
* Python scripting system  
* Package manager  
* Windows, Mac, and Linux support  

## Platform Support  
Currently, Oasis Engine is only available on Windows. Support for other operating systems may come in the future. I do not intend to support mobile devices or consoles myself, though I would be more than happy to integrate support for those platforms from other contributors.  

## Contributing  
If you want to contribute to Oasis Engine, feel free to make a fork of it and make a pull request to merge into the main repository. You can also contribute by leaving feedback and reporting bugs.  

## Attribution  
If you find Oasis Engine useful and decide to make your own version, please give credit to myself and all other project contributors. It means a lot to know that hard work is being appreciated. This work is licensed under the Apache License 2.0, so make sure to respect the license.  

## Developing
Oasis Engine is developed using Visual Studio. The project currently uses Visual Studio Community 2022, but may be upgraded to newer versions in the future. If you use the Professional or Enterprise version of Visual Studio, please omit exclusive features from those editions. Please do not upgrade the project without my knowledge. If the project is upgraded, I will update this README to reflect the changes. To get started, make sure that the C++, .NET, and Python workloads are installed, then run genprojects.bat, and open Oasis-Engine.sln. There will be many projects in the solution, but the two primary ones are Oasis-Engine, which is the base engine, Oasis-Sandbox, which is a sandbox application for testing. The others are other libraries that have been forked to use Premake to keep a unified build system.

## Third Party Licenses  
Oasis Engine uses multiple third party libraries. As each has different licenses that must be respected, a copy of each is placed in the root directory, named by the library name, which is an exact copy of the license for the respective library.  

Enjoy!  
-RobotLeopard86
