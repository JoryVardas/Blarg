# Blarg
Blarg is a simple Windows 3D modeling software. This project is from 2013 and is one of the first C++ projects I ever made, as such it is not the best in terms of code quality.

This project was my first foray into DirectX, rendering, and 3D geometry.

Under **Modeling/Tools** there are several functions to perform specific actions, though not all of them were implemented into the program.

## Requirements

- Visual Studio 2022
- Direct X SDK (2010) installed at the default installation location.

## Known Issues
- Save As window still has load button.
- Save As and Load windows lack indications of where to enter the name of the world to save as or load.
- Saving without first doing a Save As has unknown results.
- Selecting a face often selects the face furthest from the camera instead of closest.
- Selecting a mesh does not work.


## Controls
- <kbd>BACKSPACE</kbd> : Exit transform and create
- <kbd>SPACE</kbd> : Clear selected data
- <kbd>R</kbd> : Enter rotate transform
	- <kbd>DOWN ARROW</kbd> and <kbd>UP ARROW</kbd>: Rotate around x-axis
	- <kbd>LEFT ARROW</kbd> and <kbd>RIGHT ARROW</kbd>: Rotate around y-axis
	- <kbd>PAGE UP</kbd> and <kbd>PAGE DOWN</kbd>: Rotate around z-axis
- <kbd>S</kbd> : Enter scale transform
	- <kbd>DOWN ARROW</kbd> and <kbd>UP ARROW</kbd>: Scale along y-axis
	- <kbd>LEFT ARROW</kbd> and <kbd>RIGHT ARROW</kbd>: Scale along x-axis
	- <kbd>PAGE UP</kbd> and <kbd>PAGE DOWN</kbd>: Scale along z-axis
- <kbd>T</kbd> : Enter translate transform
	- <kbd>DOWN ARROW</kbd> and <kbd>UP ARROW</kbd>: Translate along y-axis
	- <kbd>LEFT ARROW</kbd> and <kbd>RIGHT ARROW</kbd>: Translate along x-axis
	- <kbd>PAGE UP</kbd> and <kbd>PAGE DOWN</kbd>: Translate along z-axis
- <kbd>CONTROL</kbd> + <kbd>S</kbd> : Save
- <kbd>CONTROL</kbd> + <kbd>SHIFT</kbd> + <kbd>S</kbd> : Save As
- <kbd>C</kbd> : Enter create
	- <kbd>1</kbd> : Create cube
	- <kbd>2</kbd> : Create sphere
	- <kbd>3</kbd> : Create torus
	- <kbd>4</kbd> : Create plane
- <kbd>CONTROL</kbd> + <kbd>1</kbd> : Select all objects
- <kbd>CONTROL</kbd> + <kbd>2</kbd> : Enter model select
- <kbd>CONTROL</kbd> + <kbd>3</kbd> : Enter face select
- <kbd>CONTROL</kbd> + <kbd>4</kbd> : Enter vertex select
- <kbd>5</kbd> : Edge split
- <kbd>6</kbd> : Fuse vertices
- <kbd>CONTROL</kbd> + <kbd>L</kbd> : Load
- <kbd>CONTROL</kbd> + <kbd>N</kbd> : Clear all objects
- <kbd>LEFT MOUSE BUTTON</kbd> : Select mesh | face | vertex