# Wolf3d
Raycasting engine based off the famous game Wolfenstein3d, written in C and using the SDL2 library. This is a team project made as part of the cursus at 42.

<img src="http://g.recordit.co/d65M5YYt67.gif" width='400' height='300'/>
<img src="http://g.recordit.co/Pi5wUDUfbL.gif" width='400' height='300'/>
<img src="http://g.recordit.co/3tTQj3yigK.gif" width='400' height='300'/>


## Description

The goal of this project is to create a raycasting engine from scratch. The project is heavily inspired by the game Wolfenstein3D and the textures used are in direct reference to the game. 

The game responds to keyboard and mouse input and places the player in a labyrinth that is defined in the file passed as argument. The player must wander in the labyrinth and find the end which will trigger the win screen.
Sounds and musics are implemented through SDL_mixer.

Main features:
* Raycasting engine with basic shading
* Skybox
* Collisions (can 'slide' on walls if an axis is blockde)
* Can look around, sprint ('shift'), open doors ('e')
* Map of level ('m')
* Basic animation (fire gun)
* Basic UI (only aesthetic)
* Different zones for different set of textures
* Real-time, 60 fps on our CPU

## Usage
`./wolf3d <map file>`

Map file must follow a strict syntax detailed in the format_map file.

## Installation
First you have to install the SDL Library, the following command will download the sources and install it:<br/>
`make sdl`

Once installed you can compile the project:<br/>
`make`

In case there is any problem during the download and installation of SDL2, you can use:<br/>
`make sdlclean`<br/>
`make sdl`
