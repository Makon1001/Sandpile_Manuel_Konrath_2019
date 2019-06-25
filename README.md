# Sandpile_Manuel_Konrath_2019

## The goal 
The goal of this project is to develop an hour-glass when looked from above. Let’s imagine a rectangular grid, with each square containing grains of sand. When there are at least four grains of sand in the same square, it becomes unstable. It will then distribute a grain of sand into each of the 4 neighboring squares, and its own number will decrease by 4. One collapse can lead to another, which will create a chain reaction.

The program will display the initial grid after n iterations of following sand (n>=0).
The grains of stand will always stay in the center of the grid (or as close as possible to the center, start- ing from the top-left corner).

## Parameters 
This project will take three parameters: a path to the file containing the initial grid, a string containing the characters used to represent the number of grains of sand in a cell and a number of iterations to apply on the supplied grid.
