# Welcome to Chess Bot v1

A simple CLI based chess game against a chess bot. The chess bot uses the minimax algorithm, which analyzes every possible move for a given depth, evaluates each of the board possibilities, and chooses the best one for its turn.

Due to the complexity of the chess, this algorithm slows down exponentially as the depth increases, so it's better to have a relatively smaller depth, such as 2, 4 or even 6.

Also the depth should be preferred as an even integer, since that way it'll also calculate the opponents ending move, resulting in a more balanced play style. An odd depth will play more aggressively, as it will not calculate the final move of the opponent (which can take back the piece, for example).

For the program itself, the board is represented with letters for the pieces, and 0's for the empty squares. The lowercase letters are white pieces, and the capital letters are black pieces. The letters correspond to the given pieces as:

```
p / P -> pawn
n / N -> knight
b / B -> bishop
r / R -> rook
q / Q -> queen
k / K -> king
```

The coordinates are provided with their chess coordinates, and the formatting is the starting square, followed by a space and the target square. An example for moving the pawn from its starting square to e4 would have the input as:

```
e2 e4
```

Here's an example run of the program:

```
Welcome to Chess!

What color would you like to play with (w/b, q for quit):w

Enter depth for the bot (an even integer recommended):4

8  R N B Q K B N R
7  P P P P P P P P
6  0 0 0 0 0 0 0 0
5  0 0 0 0 0 0 0 0
4  0 0 0 0 0 0 0 0
3  0 0 0 0 0 0 0 0
2  p p p p p p p p
1  r n b q k b n r
   a b c d e f g h

It's white's turn now.
Enter the coordinates of your move (q for exit):e2 e4

161 ms to think
425818 moves analysed
The bot played b8 to c6


8  R 0 B Q K B N R
7  P P P P P P P P
6  0 0 N 0 0 0 0 0
5  0 0 0 0 0 0 0 0
4  0 0 0 0 p 0 0 0
3  0 0 0 0 0 0 0 0
2  p p p p 0 p p p
1  r n b q k b n r
   a b c d e f g h

It's white's turn now.
Enter the coordinates of your move (q for exit):d2 d4

330 ms to think
783249 moves analysed
The bot played g8 to f6


8  R 0 B Q K B 0 R
7  P P P P P P P P
6  0 0 N 0 0 N 0 0
5  0 0 0 0 0 0 0 0
4  0 0 0 p p 0 0 0
3  0 0 0 0 0 0 0 0
2  p p p 0 0 p p p
1  r n b q k b n r
   a b c d e f g h

It's white's turn now.
Enter the coordinates of your move (q for exit):b1 c3

402 ms to think
954804 moves analysed
The bot played e7 to e5


8  R 0 B Q K B 0 R
7  P P P P 0 P P P
6  0 0 N 0 0 N 0 0
5  0 0 0 0 P 0 0 0
4  0 0 0 p p 0 0 0
3  0 0 n 0 0 0 0 0
2  p p p 0 0 p p p
1  r 0 b q k b n r
   a b c d e f g h

It's white's turn now.
Enter the coordinates of your move (q for exit):g1 f3

570 ms to think
1339281 moves analysed
The bot played e5 to d4


8  R 0 B Q K B 0 R
7  P P P P 0 P P P
6  0 0 N 0 0 N 0 0
5  0 0 0 0 0 0 0 0
4  0 0 0 P p 0 0 0
3  0 0 n 0 0 n 0 0
2  p p p 0 0 p p p
1  r 0 b q k b 0 r
   a b c d e f g h

It's white's turn now.
Enter the coordinates of your move (q for exit):q
```

