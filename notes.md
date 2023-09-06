rules
• The player’s goal is to collect every collectible present on the map, then escape chosing the shortest possible route.
• The player should be able to move in these 4 directions: up, down, left, right.
• The player should not be able to move into walls.
key events/control
• The W, A, S, and D keys must be used to move the main character.
more instruction
• At every move, the current number of movements must be displayed in the shell.
• You have to use a 2D view (top-down or profile).
• Your program has to display the image in a window.
• Pressing ESC must close the window and quit the program in a clean way.
• Clicking on the cross on the window’s frame must close the window and quit the program in a clean way.
• The use of the images of the MiniLibX is mandatory.
• If any misconfiguration of any kind is encountered in the file, the program must exit in a clean way, and return "Error\n" followed by an explicit error message of your choice.
map/parsing
The map can be composed of only these 5 characters:
    0 for an empty space,
    1 for a wall,
    C for a collectible,
    E for a map exit,
    P for the player’s starting position.
• The map must contain 1 exit, at least 1 collectible, and 1 starting position to be valid.
• The map must be rectangular, closed/surrounded by walls.

ex. map :
1111111111111
10010000000C1
1000011111001
1P0011E000001
1111111111111