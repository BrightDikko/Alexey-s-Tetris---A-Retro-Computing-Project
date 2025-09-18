# Alexey's Tetris - A Retro Computing Project

## Group Members
- Amelie Boom (ABoom@nd.edu) & Bright Dikko (BDikko@nd.edu)

## Background & Overview

For this project, we decided to work on a game from the ‘80s / ‘90s as our computing artifact. After exploring classic titles on Retro Games (retrogames.cz) — an online museum of old video games, one that immediately stood out was Tetris. Not only is Tetris still recognizable and relevant today, but its creation story resonates strongly with the hacker ethos described in Steven Levy’s *Hackers: Heroes of the Computer Revolution*.

Tetris was invented in 1984 by Russian software engineer Alexey Pajitnov, who created the original version on an Elektronika 60 computer while working at the Dorodnitsyn Computing Centre of the Soviet Academy of Sciences in Moscow. Much like the hackers at MIT described by Levy, Pajitnov used an institutional computer system intended for research and “serious” work, to explore playful puzzle ideas in his free time. Computers in the Soviet Union were prohibitively expensive and rare, so Pajitnov built Tetris on the only machine available to him at work. The Elektronika 60 had no graphics capability, so Pajitnov cleverly used text characters to represent tetrominoes in that original version. Despite these limitations, the game quickly spread across Moscow and later internationally, marking one of the most important moments in computing and gaming history. By Levy’s work, Pajitnov was very much a “True Hacker”.

## Project Description

We propose to recreate Tetris as our retro computing artifact. While we do not own or have access to an Elektronika 60, we will implement the game in C++, a historically relevant language for developing games in that era. In fact, some later versions and variations of Tetris were built using C++.

For our MVP, we will preserve the text-based nature of Pajitnov’s original version, rendering the game grid and tetrominoes using text output to stay faithful to the roots of the original Tetris.

If time permits after completing the MVP, we will extend the project by adding a graphical interface using a graphics library such as Raylib. This would allow us to create a recognizable modern version of Tetris with a colored game board and falling blocks, while still keeping the core logic grounded in the original text-based implementation.

## How The Project Meets The Requirements

- This project is firmly rooted in computing history, as Tetris is one of the most iconic and influential video games ever created. It is interactive, requiring users to provide real-time input to rotate, move, and drop falling tetrominoes.
- The project is also designed to run in a resource-constrained environment. For example, the MVP will be text-based and rendered entirely in the console, demonstrating how early programmers worked within limitations. Additionally, we are choosing to implement the project in C++, a legacy and iconic language, rather than relying on more modern alternatives such as Python and PyGame.
- For version control, we will use Git and GitHub, accompanied by documentation in a README.md file. We will also maintain a CHANGELOG to track versioned releases, documenting progress from the MVP to any follow-up graphical version if time allows.

## Resources Required
Not Applicable
