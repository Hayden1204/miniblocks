# miniblocks

An extremely small "suckless" 2D map building game in your terminal, which is highly hackable and can be configured and patched to add more gameplay and functionality.

## License

Copyright 2022 Hayden

This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with this program. If not, see <https://www.gnu.org/licenses/>.

## Building

Clone this repository **using the following command:**

```sh
git clone https://github.com/Hayden1204/miniblocks.git
```

Then, to compile and run the game, **issue the following commands:**

```sh
gcc main.c -o minib -lncurses
./minib
```

Obviously, you'll only need to compile the game **once**. This is unless of course if you modify the source code, which means you **WILL** need to recompile the game for changes to take effect. You will also need to recompile if you add or remove a patch, as a patch just automatically modifies the source code for you.

## Playing

The default keybinds for the game **are as follows:**

1. `W`, `A`, `S`, `D`, or arrow keys to move.
2. `I`, `J`, `K`, `K` to place blocks.
3. `[` and `]` to switch between blocks.
4. *CTRL-C* to quit.

If one of the keys found in these keybindings are not found on your keyboard, or they're found in unusual places, then you can edit the source code to change them. You can also just use the arrow keys, instead of the `W`, `A`, `S`, `D` layout if that's easier, or add an additional set of keybindings.

## Configuration

Configuration is done by editing the source code, which should be named `main.c`.

For example, to change the map size to a width of 48, and a height of 20, **edit the following lines like so:**

```c
#define WIDTH 48
#define HEIGHT 20
```

The game will automatically handle the rest of the calculations for you, so these are the only two lines you would need to edit to change the map dimensions.

Another example, if you would like to change the player "sprite" if you will, let's say we'll change it to `R`, **edit the following lines like so:**

```c
#define PLAYER 'R'
```

The game will now start drawing the character `R` as the player sprite, instead of the default `X`.

Final example, if you would like to add an extra block to the selection, let's say we'll add a `$` block, then we'll need to change the array size of the block selection from 12 to 13, to fit one more block in. Then, we'll just append our `$` block to the end of the array. To achieve this, **edit the following lines like so:**

```c
#define BLOCKS 13

// ...

char block[BLOCKS] = {' ', '#', '%', '*', '&', '+', '@', '[', ']', '~', '-', '=', '$'};
```

We have now located our new `$` block at the end of the array. For reference, you should probably not add it as the first block, since that would make it ID 0, which will always be Air. Here, we've set it as ID 12, which is the last valid ID number in our array.

If you're confused on what `// ...` is, it's just a place holder for the lines of code that come after the `#define` statement and before the `char` declaration. I've put it as a comment, so that if a newbie is confused and adds it for some reason (of course, you don't need to), it won't frustrate them with any errors.

## Patching

Currently, there are **NO patches avaliable**. However, that is being worked on, and you should be able to apply some patches soon.

To apply a patch, **enter the following command like so**, replacing `name-of-patch.diff` with the name of the patch file:

```sh
patch -p1 < name-of-patch.diff
```

If you would like to create a patch, then you will need a copy of the original source code, and your modified source code. To create a patch, **issue the following command like so**, replacing `original.c` with the name of the original source code file, `patched.c` with the name of the patched source code file, and `patch.diff` with the name of your patch file to be written to:

```sh
diff -u original.c patched.c > patch.diff
```

Names of patches should follow the format `minib-patchName.diff`, replacing the `patchName` part of the file name with a shorthand name of your patch. For example, a colour patch for this game would be named `minib-colour.diff`.
