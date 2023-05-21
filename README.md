# Pacman-Console-Application

This is a Pacman game console application created in C++, during a C++ course in The Academic College of Tel Aviv, Yaffo, 2022.

This game allows you to run custom screen files you can create yourself using the file format below.

# Command Arguments

The Steps and Result files are for run testing using command arguments as following: "pacman.exe -load|-save [-silent]"

In the -load mode there is NO menu, it will just run the loaded game as is from the Steps file, and compare the results to the Results file!
Can run with -silent to avoid printing to screen and just testing by the result file.

In the -save mode Steps and Result files are created for each Screen file you play (So you can load them later).

# Screen File Format:

'#' - Walls.

'%' - Empty space.

' ' - Empty space to be filled with breadcrumbs.

'&' - Legend location.

'$' - Ghost location (May add 0 - 4 ghosts).

'@' - Pacman location (Must add).

Empty spaces along the walls will be tunnels - must include empty space on the other side of the wall.

# Steps File Format:

-Each steps file will start with the line: "The game is with colors" / "The game is without colors" - indicating whether or not the game shall run with colours.

-The rest of the lines will have a number - identifying which entity is about to move, following the direction:

0: Pacman

1: Fruit

2: Ghost #1

3: Ghost #2

4: Ghost #3

5: Ghost #4

(Note: Number of ghosts may change)

A: Left

W: Up

S: Stay

X: Down

D: Right

-Special treatment:

Fruit - When a fruit appears, the line will read: "1 S X Y VALUE", indicating the fruit appears with the direction Stay,
its X and Y location values, and the digit value of the fruit.

# Result File Format:

There will be 2 possible types of lines in this file:

-lose: <Time Stamp> - indicating the point of time the pacman died on this screen.

-win: <Time Stamp> - indicating the point of time the pacman finished the screen successfully.
