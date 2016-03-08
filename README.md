Desdemona
=========

Computer play Othello good.

Usage
-----

The simplest way to compile Desdemona is

    $ make testgame desdemona

To use the resulting `desdemona` executable,

    $ testgame [black] [white]

Where `[black]` is the name of the black player and `[white]` is the name of
the white player.  These may be any of `simpleplayer`, which plays randomly;
`desdemona`, a new AI under development; `betterplayer`, which searches a game
tree to depth 3; and `human`, which allows a human to play one or both sides.

Documentation
-------------

Documentation on the C++ portion of Othello's codebase may be found [here][doc].

[doc]: http://ikuehne.github.io/Desdemona/annotated.html
