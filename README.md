# miniblocks

An extremely tiny, even "suckless" 2D building game in your terminal, which is highly hackable and can be configured and patched to add more gameplay and functionality.

This program is not really a "works out of the box" type of thing. You will have to do some reading, and follow the guide. However, it should hopefully be easy to follow along, as it is carefully constructed with easy to understand wording, and organized sections. The advantage of this model is that the game is very minimal, but is still very usable, and is configured just how you like it.

One last thing, this game is built using the `ncurses` library. This is a simple library for manipulating the terminal and creating pseudo-graphics or a TUI (terminal UI. Like GUI, graphics UI). However, **this does not exist on Windows**. To run the game on Windows, you'll have to use WSL (Windows Subsystem for Linux), or another program which can use a POSIX C compiler with the `ncurses` library set up.

## License

miniblocks Copyright (C) 2022 Hayden

> This program is free software: you can redistribute it and/or modify it under
> the terms of the GNU General Public License as published by the Free Software
> Foundation, either version 3 of the License, or (at your option) any later
> version.
>
> This program is distributed in the hope that it will be useful, but WITHOUT
> ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
> FOR A PARTICULAR PURPOSE. See the GNU General Public License for more
> details.
>
> You should have received a copy of the GNU General Public License along with
> this program. If not, see <https://www.gnu.org/licenses/>.

## Building

First of all, you'll need to download the game. To do this, you will have to "clone" it. To clone the repository for the game, use the following command:

```sh
git clone https://github.com/Hayden1204/miniblocks.git
```

Now, you've downloaded the source code. The game still needs to be compiled to be in a format where your computer can execute the instructions, so you can play the game.

To compile and run the game, you'll have to issue another set of commands. Issue the following commands:

```sh
gcc main.c -o minib -lncurses
./minib
```

The game should now be running. Great! If you want to learn the keybindings, head over to the **Playing** section below. There's only a couple, so it should be quite quick to learn.

The game only really ever needs to be compiled once. This is unless you patch or modify the game in one way or another. If you want to recompile the game, you can use the exact same commands as we've used to compile the game the first time around. Just scroll up, and use the second set of commands we've used previously again.

## Playing

To actually play the game, you'll need to know the default keybindings. The keybinds for the game are as follows:

1. `WASD`, or the arrow keys to move.
2. `IJKL` to place blocks.
3. `[` and `]` to scroll through blocks.
4. `CTRL-C` to quit.

If one of the keys found in the keybindings are not located on your keyboard, or they're located in a strange or uncomfortable place, then you can edit the source code to change them. We'll talk more about configuring the game in the **Configuration** section below. You can also use the arrow keys instead of the `WASD` layout, or add an additional set of keybindings, as we'll discuss shortly.

## Configuration

Configuration is done by editing the source code, which should be named `main.c`.

For example, if we would like to change the size of the map to a width of *48*, and a height of *20*, then we would need to edit the source code to do that. You can use a terminal text editor, like `nano` or `vim`. You can also use advanced GUI editors, like Gedit, Kate, or Mousepad. To change the size of the map, locate these lines, and edit the following like so:

```c
#define WIDTH 48
#define HEIGHT 20
```

The game will automatically handle everything else for you, so these should be the only two lines you'll need to edit to change the map dimensions.

Let's issue another example. If you would like to change the player "sprite" (a sprite is what I call the `X` that is your player), let's say we'll change it to `R`, we'll need to edit the following lines like so:

```c
#define PLAYER 'R'
```

The game will now draw the character `R` as the player sprite, instead of the default, which I've already mentioned is `X`.

Final example, let's show you something a bit more complex. If you would like to add an extra block to the selection, let's say we'll add a `$` block, then we'll need to change the array size of the block selection to *13*. If you don't understand what I've just said, then basically, we're expanding the maximum number of blocks in our game. Now, we'll append (add to the end) our `$` block to the array. To achieve all of this, edit the following lines like so:

```c
#define BLOCKS 13

// ...

char block[BLOCKS] = {' ', '#', '%', '*', '&', '+', '@', '[', ']', '~', '-', '=', '$'};
```

We have now located our `$` block at the end of the array. For reference, you should probably not place it as the first item in the array, since that would result in an ID of *0*, which will always be the *Air* block. In this example, we've set it as ID *12*, which is the last ID number in our array.

## Patching

miniblocks is described as an extremely tiny, maybe even "suckless" game. As such, to keep the code base small, only the core of the program is implemented. This means that comforting features, or interesting gameplay mechanics are purposely left out to make the code base simple. To make the game more enjoyable, you can add patches. These patches use "patch files". Patch files are simply files that have special instructions that are written to change parts of another file. In this case, that would be the source code.

For example, let's apply a very simple patch. The "non-solids" patch enables us to walk through certain blocks, like "doors". I like to think of the blocks `[` and `]` as doors in the game. However, because all blocks are treated as solid blocks, we can't walk through them. To enable us to walk through certain blocks, like the doors, we can apply this patch, like so:

```sh
patch < patches/minib-nonsolids.diff
```

Make sure you apply the patch in the main directory where the `main.c` file is located. This command will fail if you try to apply the patch inside of the `patches` folder. Once patching is complete, recompile the game, and run it. If you've forgotten how to do that, the instructions are back in the **Building** section, just scroll up and follow the commands to compile and run the game. Now, if you place a `[` or `]` block, and try to walk through it, you should be able to.

Sometimes, patches can fail. This is because the automatic patching program gets confused on where to put the new lines. Your first patch should not fail, if it does, there is something wrong with the patch, or you're using an outdated build of the game. After that, patches can conflict with one another, which means you'll have to manually edit the source code and add in the lines of code yourself. This may seem complicated, but once you get the hang of it, it's quite straight-forward.

If you want to create your own patches, that should be quite easy as well. First, we'll need to make a copy of our `main.c` source code file, so that our patch file "generator" can correctly generate the patch instructions for our unpatched version of the game. We'll call our patched source code file `patched.c`. To do this, issue the following command like so:

```sh
cp main.c patched.c
```

Lovely! Now we've got an exact copy of our source code, where we can put in all our patches. As said before, open the `patched.c` file (not the `main.c` file) with your preferred text editor, and make your changes. We
