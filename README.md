# morris
Morris is an implementation of the board game Nine Men's Morris in C. I used structs and pointers to build it. 

The task was to write a C99 program (called fitz) which allows the user to play a game(described later). This will require I/O from both the user and from files. 

## The Game
This game is based on the board game Nine Men’s Morris. 
The game consists of 2 stages: 

1. Placement Stage: Placement of pieces on the board
2. Movement Stage: Movement of the pieces on the board

In the first stage,  players will place pieces on the board according to the ordering in the placement file. 
For example a placement file containing: 
W
W
B 
B 
...
means that player 1 (white) will place two pieces on the board follow player 2 (black) will place there two pieces. . 

After the completion of the placement stage, players take turns moving their pieces on the board.

## Interaction

During the movement stage, players take turns moving their pieces on the board, left and right one space at a time. 
A valid move has two requirements:
The piece moves left, right, up, down from the current locations. 
The space to be moved to is unoccupied
When a player has three in a row (horizontally or vertically), they will be prompted to remove an opponent’s piece from the board.
When the opponent has only 2 pieces remaining, the player wins. 

## Invocation
	New Game
	./morris placementFile h h

	Save Game
	./morris saveFile
  




