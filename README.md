![Python workflow](https://github.com/agt-the-walker/chess-utils/actions/workflows/pythonapp.yml/badge.svg)
![C++ workflow](https://github.com/agt-the-walker/chess-utils/actions/workflows/cpp.yml/badge.svg)


# Table of contents

* [Utilities](#utilities)
* [On Chess variants](#on-chess-variants)


# Utilities


## crc-first-row

This program prints
[Capablanca Random Chess](https://brainking.com/en/GameRules?tp=75) positions
with optional restrictions. K = King, N = Knight, etc. Note that I didn't
bother filtering out Gothic Chess positions since the patent for Gothic Chess
expired long ago.


### Requirements

* [Boost Program Options](https://www.boost.org/doc/libs/1_85_0/doc/html/program_options.html)
* [GNU Compiler Collection (GCC)](https://www.gnu.org/software/gcc/), recent
  enough to support C++11
* [GNU Make](https://www.gnu.org/software/make/)


### Usage

    $ cd ~/src/git/chess-utils  # adapt accordingly

    $ make

    $ ./crc-first-row --help
    [shows usage]

    $ ./crc-first-row | wc -l
    21836  # https://brainking.com/en/GameRules?tp=75

    # restriction: no adjacent bishops
    $ ./crc-first-row --no-adjacent-bishops | wc -l
    12130  # not 12118 (Wikipedia)

    # example output
    $ ./crc-first-row --no-adjacent-bishops | shuf -n 3 | sort
    BNCBARKNRQ
    CBQRNKRNBA
    RABKNCRBQN

    # shows a few positions not listed with --no-adjacent-bishops
    $ diff <(./crc-first-row) <(./crc-first-row --no-adjacent-bishops) | \
      grep '^<' | cut -c3- | shuf -n 3 | sort
    BBRCKQNRAN
    CRNNKBBQAR
    NBBRKQACNR


## double-pawn-moves

This program prints the following statistics on provided FIDE Chess or Chess
960 games for the player who castled first:
* number of pawns still on starting squares when he castles
* number of double pawn moves before his opponent castles
* number of double pawn moves after his opponent castles

I wrote this following my post ("Agt the Walker") in the comment section of
https://en.chessbase.com/post/alphazero-kramnik-exploring-new-chess-variants,
about Awkward Castling (see also [Play by forum](#play-by-forum)).


### Requirements

* [Python](https://www.python.org/) 3.6+
* [python-chess](https://pypi.org/project/python-chess/) Python package


### Usage

Download `champshow9lx20.pgn` (for example) from
https://theweekinchess.com/chessnews/events/champions-showdown-9lx-2020,
then:

    $ stats=$(./double-pawn-moves <../chess/twic/champshow9lx20.pgn)

    # number of games in Champions Showdown 9LX 2020
    $ wc -l <<< $stats
    45

    # number of games without any castling moves (i.e. no statistics)
    $ grep -c '^$' <<< $stats
    2

    # statistics for games with one castling move
    #  1st column: number of pawns still on starting squares
    #              for castling player when he castles
    #  2nd column: number of double pawn moves after castling move
    #              for castling player
    $ awk 'NF == 2' <<< $stats
    4 3
    5 4
    6 3
    3 1
    6 1
    8 5
    5 2
    6 3
    4 3
    3 0

    # statistics for games with two castling moves
    #  1st column: number of pawns still on starting squares
    #              for first castling player when he castles
    #  2nd column: number of double pawn moves between both castling moves
    #              for first castling player
    #  3rd column: number of double pawn moves after second castling move
    #              for first castling player
    $ awk 'NF == 3' <<< $stats
    5 0 1
    5 1 1
    6 0 3
    7 1 1
    6 0 4
    4 0 3
    4 0 2
    5 0 2
    5 0 1
    6 0 0
    5 0 0
    6 1 1
    5 0 0
    5 0 2
    5 0 2
    6 0 1
    5 0 1
    4 0 1
    6 0 2
    3 0 0
    4 0 3
    3 0 0
    5 1 2
    8 0 2
    7 0 3
    6 0 1
    7 0 4
    6 0 0
    5 1 0
    5 1 0
    4 0 3
    4 0 2
    3 0 3


# On Chess variants


## Article

Some ideas described in
[On Shogi variants](https://github.com/agt-the-walker/shogi-utils#on-shogi-variants)
are also applicable to Chess, such as randomizing the starting position
(https://uschesschamps.com/2023-champions-showdown-chess-9lx/overview).

Also winning by legally moving one's king to specific square(s) looks promising
to reduce the high draw rate in top Chess
(https://en.chessbase.com/post/opinion-12-draws-not-really-exciting). This
includes [King of the Hill](https://lichess.org/variant/kingOfTheHill) but
there are more possibilities:
https://en.boardgamearena.com/forum/viewtopic.php?f=88&t=17273.

Since winning with the bare king might be a bit too much, we could amend this
additional winning condition like this:

> If your previous move legally got your King to one of the target squares
> (i.e. center squares for King of the Hill), it's your turn to play, you're
> not checkmated or stalemated and you don't have to move your King, then you
> win.

## Play by forum

I'd like to try:
* https://boardgamegeek.com/thread/1949867/chess960-king-hill-and-pie-rule
* https://boardgamegeek.com/thread/2094499/capablanca-random-chess-king-hill-and-pie-rule
* https://boardgamegeek.com/thread/2352280/chess960-awkward-castling-rule
