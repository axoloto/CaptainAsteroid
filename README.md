# Captain Asteroid

A minimalist 2D video game directly inspired by [Atari Asteroids](https://www.youtube.com/watch?v=WYSupJ5r2zo) (1978), and created in a week using Unity and its C++ plugin framework. 

**You are Captain Asteroid, destroy all the asteroids of the Universe to complete the mission!**

## Demo on Youtube
[![ytCaptainAsteroid](ytCaptainAsteroid.jpg)](https://www.youtube.com/watch?v=u3iGnAMILYUy "Video on Youtube")

## The Coding Challenge

To make it more challenging, this project had some specific constraints that had to be respected:
- Use Unity **only for the rendering part**, the physics engine must be on the C++ plugin side
- Design the application with a focus on optimization, the whole pipeline (simulation + render) must take less than **16.6ms** (60 FPS)
- Implement the physics engine using a **[data-oriented design](https://en.wikipedia.org/wiki/Data-oriented_design)** (DOD) to optimize memory access and performance
- Finish the whole project **in less than a week**

It was a very interesting week and it gave me the chance to learn a ton in a restricted amount of time given the facts that :
- I had never used Unity
- I had never implemented a DOD pipeline
- I had never programmed in C#
  


## Commands
| Key   |      Function      |
|----------|:-------------:|
| Left/Right |  Rotate to the Left / Right |
| Up/Down | Thrust / Brake |
| Space | Shoot Laser |


## I just want to play the game (and destroy some asteroids)
Download the Exe folder and launch CaptainAsteroid.exe

## I want to open the Unity project and tweak it
Download or `git clone` the whole repo and open it on Unity Hub

## I want to build the C++ plugin (advanced)

### Requirements

- [Gitbash](https://git-scm.com/downloads)
- [Python](https://www.python.org/) (>= 3.5) and [pip](https://pypi.org/project/pip/)
- [Conan](https://conan.io/)
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

## Some technical details and design thinking

### Build system and third-party libraries handling
I used CMake to handle the build of the C++ shared library (.dll) and send it automatically to the Unity Plugin folder, in order to increase the developement iteration rate and facilitate the testing. Unfortunately, I quickly realized that once loaded plugins are never unloaded from Unity, so despite the automation of most of the build pipeline, I still had to close and relaunch Unity software everytime a change was made on C++ side. 

Third-party libraries management has been a nightmare in C++ for quite some time, but things have changed recently thanks to open-source package managers like Conan. Conan gives us the chance to very simply download up-to-date third-party libraries and plug them into our applications without any pain. Even better, it is fully integrated into CMake framework, so we can retrieve those third-party libraries as classic packages with `find_package()`.

### C++ DOD physics pipeline
In the past years, I have been focused on GPUs programming so I was familiar with the concept of data-focused pipeline and the gain that we can have in terms of performance. Nevertheless I never heard before of Data-Oriented Design and it was a very nice discovery.After some investigation and testing, I decided to base my physics engine on the awesome [Alec Thomas's entityx](https://github.com/alecthomas/entityx) generic Entity Component System (ECS) library retrieved with Conan. Following DOD/ECS concepts, the physics engine is made of :
- Entities, the game entities (Space ship, asteroids, laser shots) made of aggregated components
- Components, entities property (life, laser, position..)
- Systems, pipeline nodes modifying components

At first, it was a bit challenging to forget about OOP, but I quickly saw the potential of the ECS/DOD design and the performance that we can gain from it. It was a very pleasant experience to implement the pipeline and add the differents components and systems while iteratively complexifying the gameplay and adding new features.

### Marshaling data from C++ to C# and Game Objects pooling
Having never programmed in C#, I was not aware of the marshaling process and how to connect managed memory (C#) and unmanaged one (C++). I decided to keep it simple and try to avoid any unnecessary and costly allocation/copy at each time iteration on managed side or unmanage one. Hence the buffers containing coordinates of the different game NPC entities are allocated once as global variables on managed side with a fixed size. Then, at each time step, I simply send their addresses on C++ side to fill it, asking C# side to pin the buffer memory during the filling operation. The C++ plugin fills the given buffers up to the number of existing entities and inform C# script how much of the buffer has been filled.

These coordinates buffers are then used to update the positions of the pooled game objects which have generated at initialization step on C# side. All game objects in the pools with an index higher than the number of existing entities are deactivated. By doing so, there is no generation of game objects at each time iteration.

Pros of this design:
- Simple and very fast
- No game object generation after initialization
- No buffer allocation/copy after initialization
- Buffers are allocated on managed side, no potential memory leaks

Cons:
- Simplistic, buffers and pools have a fixed size so you are limiting the number of potential game entities to a certain bound. I set it to 200 for each entities, knowing very well that the game is not playable past 100 asteroids so it is a reasonable tradeoff and the limit could be definitely lower.
- There is no id mapping between game objects on C# side and entities on C++ side, if I want to add some explosions in the game I will have to send their coordinates as any other entities because Unity doesn't know which asteroid has been destroyed or not.

### C# scripts implementation

Again, I had zero experience with C# so I might miss some good practices and I apologies for any disturbing design in the C# scripts.

I decided to create a Plugin Controller script doing the API with the native C++ side so I could call the API functions from different C# scripts connected to the multiple Game Objects (Space Ship, pools, UI...).

## References and Inspirations

- [CMake](https://cmake.org/)
- [Conan](https://conan.io/), an awesome open source package manager for C/C++
- [Entityx](https://github.com/alecthomas/entityx), a fast and efficient open source library implementing generic DOD framework
- [spdlog](https://github.com/gabime/spdlog), an open source logging library
- [Unity Talk about DOTS by Mike Geig](https://www.youtube.com/watch?v=BNMrevfB6Q0&list=PLX2vGYjWbI0S1wHRTyDiPtKLEPTWFi4cd&index=1), a very clear explanation about DOD and Unity's own implementation named Data-Oriented Technology Stack (DOTS)
- [Making Space Invaders with Unity](https://www.youtube.com/watch?v=cnfwNzpoIlA), a nice introduction to understand Unity framework and UI implementation
