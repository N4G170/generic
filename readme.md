# Generic demos program

This is a personal program in which I play around with ideas I get and learn how some things work, by making them (or reinventing the wheel).
I uploaded the code to github for convenience, but if anyone finds it useful, even as a bad example, good.

This program has suffered a lot of changes, reworks, rewrites, and more.
The last of which added, perhaps, the most interesting element, an ECS (entity-component-system) system, similar to the system used in unity3d.
The ECS system appeared when I was working on the sdl_gui project (a project that in this one and was moved into its own), and I started having new ideas on how to make sdl_gui
easier to use, and then I noticed I was moving to an ECS system.
The new system is not perfect, it needs more polish and features, but currently, it makes the creation of new demos a lot easier and cleaner.
With new new system, I scrapped my old parent-children transform system, as the new one is cleaner and faster.

The ECS system currently can render images, basic frame animations (based on images), apply masks, render on canvas(something, like viewports) and detect collisions (there is, also, the beginning of a basic particle emitter/system).

Currently the program has 6 demos.
    - The first is a simulation of creatures moving on a map, using A* pathfinding, with no corner cut and with different move costs. This demo uses the ECS.
    - The second is a "rain" demo, basically rain falls, there is wind, each drop when it hits the floor it disappear and a splash animation is run. The is also a mask applied to the scene to simulate the night and the use of a flashlight (can be disabled). This demo uses the ECS, the mask was created for this demo.
    - The third is the oldest demo in the project, a very basic snake, I don't even remember why I made it. Does not use the ECS, and I will keep it like that as a "souvenir"
    - The fourth, the solar system demo, the ECS was mainly created using this demo, it simulates a small solar system with planet, moons, a sun and comets flying around. Each planet and the sun have gravity that attracts comets to it. I really enjoyed making this simulation, and when I finish the vulkan renderer this will be the first thing I'll port to it.
    - The fifth generates a map with perlin noise. I made it because I was curious about the process. It needs to be converted to the ECS and requires a lot of cleaning.
    - The sixth contains the base for the basic particle emitter. Currently, as it is in testing, it "shoots" is a V with varying amplitude and direction.


## Running the program
If you are using one of the release builds, double click the .exe on windows or run in a terminal on linux.
The ui is entirely keyboard based, as the old gui was removed and moved to another project.
So, to use the program, just follow the text.


## Building the program

### If on Linux

First install all the dependencies:
    - SDL2
    - SDL2_image
    - SDL2_ttf
    - SDL2_mixer
    - lua
    - cmake (needed for "fast" build)
After that, open terminal window at the base of the project (the folder with this file) and run the commands:
    ```
    - mkdir build
    - cd build
    - cmake ..
    - make -j
    ```
If no errors appear, the build is complete and you can run the program with the command ./generic
I did not configure any install instructions, so if you want to move the build, copy the folder 'data' and the file 'generic' from the build folder.

NOTE: As cmake creates the executable as a shared object (I have yet to find why), you have to run the program through the terminal, rather than double click

### On windows

On windows, building the program is not that easier. As the cmake module used to find SDL2 does not work on windows, the build has to be made manually.

Inside the vs folder there is a Visual studio solution configured to build the program using the current folder structure.
If all goes well, all you have to do is open the solution, and build (only works for x64 builds).

If the solution does not work, or you use another build system, you have to add the files by hand to you project and take care of the dependencies.
For ease of building, you can find the needed dependencies inside the vs folder.
NOTE: I do not own any of the code from the dependencies. Their license allows them to be freely used and shared.

To run the program, you need the data folder next to the .exe as well as all of SDL2, SDL2_image, SDL2_ttf, SDL2_mixer dlls (you can find them in my release or download them from the SDL website).

NOTE: the windows builds does not use lua because the project fails to build. Has I have yet to find the solution and the current use of lua is not really needed, I created a preprocessor directive to, when on window, modify the function that uses lua.

## TODO

So much to do, first clean the perlin noise demo, then, document the ECS system and port it into my other project(sdl_gui mainly).
After that, integrate this project with my basic vulkan renderer(needs alot of work)?

If you find any bug of error, let me know.
