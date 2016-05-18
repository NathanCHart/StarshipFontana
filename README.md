# Starship Fontana #

This is an example C++ application using the SDL library.
It tries to be as nicely C++11 as possible but do keep in
mind that SDL is written in C and, at some stage, you have
to interface with it.

## Story ##
The evil b’Kuhn has stolen the code to Earth’s defence system.
With this code he can, at any time, defeat the entire human race.
Only one woman is brave enough to go after b’Kuhn. Will she be
Earth’s hero? Puzzle your way though the universe in the company
of Commander Fontana in **Starship Fontana**.

## Installation ##
You will have to have the SDL development libraries installed on
your system.  The easiest way to compile is to use a command-line

```bash
$ g++ -c -std=c++11 src/*.cpp
$ g++ -o starship *.o -lSDL2 -lSDL2_image
```

which will produce an executable file called "starship" in the
top-level directory.  To execute this file do the following

`$ ./starship`
 
from the top-level directory.  The game will expect to find the
`assets` directory under its current working directory.

## Credits ##
The sprites in this game come directly from 
[SpriteLib](http://www.widgetworx.com/widgetworx/portfolio/spritelib.html) and are used
under the terms of the [CPL 1.0](http://opensource.org/licenses/cpl1.0.php).
Further Sprite usage was through [Kenney] (http://www.kenney.nl/assets) and [OpenGameArt] (http://www.opengameart.org)

## Comments to the examiner##

I have built my code through the step by step process provided on the assessment tips document, after creating the basic functions of enabling the player to move in all four directions, adding collision to walls and aliens (by stating that if the player is moving left by a factor of 5, if he hits the wall he will move right by a factor of 5, therefore making the overall movement speed 0, this works in all 4 directions,) changing most of the sprites using online free to use spritesheets and adding an end game state, I added some extra features.

Firstly, I moved the aliens up to the top of the screen, and made a random number generator between 0 and 3 which changes every frame, and linked each number to a direction. In the generator, I realised the most generated number was 2, therefore I linked 2 with the action of going south, and 0 and 1 to go east and west respectively, therefore the aliens witll gradually move south and shift randomly between left and right. I also applied this same system to give the aliens a weapon, which each frame has a 1 in 1000 chance of shooting, which the player will have to dodge in order to avoid a game over state. I also have 3 other game over states, one when the aliens reach the bottom, one when the player hits the alien and one victory state when the player clears all aliens from the screen.

Also, I chose to place my walls on both the x and y axis of the edges of the screen, this enabled me to have a greater control over where the player and aliens were positioned.

Finally, I added a score system so that a player has a reason to play the game, and also increase replayability/
