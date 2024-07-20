#  Wordle Solver

This is a new desk accessory for the Apple IIgs which solves Wordle puzzles for you.  Rather than being the game, this can be used to solve the puzzle for you by telling you the best guesses (hopefully).

![Wordle Solver Screenshot](/wordlesolvenda.png "Wordle Solver Screenshot")

It will give you its first guess of a five letter word.  Then, you should click on each letter to set each to the correct colour:
* If the letter is in the correct position, then mark that letter green.
* If the letter exists in the word somewhere else but is in the wrong position, then mark that letter yellow.
* If the letter does not exist in the word at all, mark that letter white.

Note that if the letter appears multiple times in the solution, then it is possible to have multiple letters marked as correct or correct and in the wrong position.  If the guess has more
letters of that type in it, then one should be marked as wrong.

[Download a disk image](https://github.com/jeremysrand/wordlesolvenda/releases/download/1.0/wordlesolve_100.2mg)

[Download a SHK archive](https://github.com/jeremysrand/wordlesolvenda/releases/download/1.0/wordlesolve100.shk)

Also, this solver does seem to be able to solve puzzles in [WordleGS](https://github.com/dmalec/Wordle.GS) by Dan Malec.  However, you must continually switch between the solver by opening
it from the Apple menu and then back to the puzzle by clicking on the desktop background.  It is a bit awkward but it works.

This code is based on [Wordle Solver CDA](https://github.com/jeremysrand/wordlesolve) which I implemented first.  I took the algorithm from that and wrapped it in a new UI for my
HackFest entry at KansasFest 2024.
