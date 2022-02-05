# CaptainAsteroid

A minimalist 2D video game directly inspired by [Atari Asteroids](https://www.youtube.com/watch?v=WYSupJ5r2zo) (1978) created in a week using Unity and its C++ plugin framework.

The main constraints :
- Use Unity only for the rendering part, the physics engine must be on the C++ plugin side
- Design the application with a focus on optimization, the whole pipeline (simulation + render) must take less than **16.6ms** (60 FPS)
- Implement the physics engine using a [data-oriented design](https://en.wikipedia.org/wiki/Data-oriented_design) (DOD) to optimize memory access and performance
- Finish the whole project in less than a week

It was a very interesting week and it gave me the chance to learn a ton in a restricted amount of time given the facts that :
- I have never used Unity before
- I have never implemented a DOD pipeline before
- I have never programmed in C#

## Demo on Youtube
[![ytCaptainAsteroid](ytCaptainAsteroid.jpg)](https://www.youtube.com/watch?v=u3iGnAMILYUy "Video on Youtube")

## The Journey 


## Some technical details:
 
## I just want to play the game (and destroy some asteroids)
Download the Exe folder and launch CaptainAsteroid.exe

## I want to open the Unity project and tweak it
Download or `git clone` the whole repo and open it on Unity Hub

## I want to build the C++ plugin (advanced)

### Requirements

- [Gitbash](https://git-scm.com/downloads)
- [Python](https://www.python.org/) (>= 3.5) and [pip](https://pypi.org/project/pip/)
- [Conan](https://conan.io/), an awesome open source package manager for C/C++
- [CMake](https://cmake.org/download/)
- C++ compiler, tested with [MSVC 15/19](https://visualstudio.microsoft.com/vs/features/cplusplus/) only for now 

### Setup Conan

```bash
pip install conan
conan remote add conan-center https://conan.io/center/
```
### Build the C++ Plugin

```bash
git clone https://github.com/axoloto/CaptainAsteroid.git
cd CaptainAsteroid
./buildPlugin.sh
```

## References and Inspirations

- [CMake](https://cmake.org/)
- [Conan](https://conan.io/), an awesome open source package manager for C/C++
- [Entityx](https://github.com/alecthomas/entityx), a fast and efficient open source library implementing generic DOD framework
- [spdlog](https://github.com/gabime/spdlog), an open source logging library
- [Unity Talk about DOTS by Mike Geig](https://www.youtube.com/watch?v=BNMrevfB6Q0&list=PLX2vGYjWbI0S1wHRTyDiPtKLEPTWFi4cd&index=1), a very clear explanation about DOD and Unity's own implementation named Data-Oriented Technology Stack (DOTS)
- [Making Space Invaders with Unity](https://www.youtube.com/watch?v=cnfwNzpoIlA), a nice introduction to understand Unity framework and UI implementation
