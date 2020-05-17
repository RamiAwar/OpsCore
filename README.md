# PumpkinBox

## What is it?
A desktop application development framework that allows for the development of C++ applications with a GUI and Renderer (Only OpenGL backend supported so far, but architecture leaves room for Vulkan, Metal, or DirectX extensions).

## What does it feature?
A complete Entity Component System that gives users a framework to design their simulations, games, applications with. Can support up to hundreds of thousands of dynamic entities at once on a single thread due to its data oriented architecture. Examples to be posted soon.

## How to setup for development
Note that this is only tested on Windows so far. Should work with older versions of Mac(since OpenGL is deprecated in favor of Metal now), and should work normally with Linux (probably with some minor adjustments to project configuration).

First, clone the repository *WITH* the git submodules **(necessary)**:

```git clone --recursive https://github.com/RamiAwar/PumpkinBox```

I'm using Premake, which generates project files automatically. This means that it sets up the project names, submodules, include paths, linking, etc... To generate visual studio project files, do the following:

- Grab a premake binary from here : [Link](https://premake.github.io/download.html)
- If you're on windows and want to generate visual studio project files, navigate to the folder using command prompt, modify `GenerateProject.batch` to use your premake5.exe, and then run `GenerateProject.batch`.


