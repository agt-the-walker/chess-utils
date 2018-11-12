[![Build Status](https://travis-ci.org/agt-the-walker/chess-utils.svg?branch=master)](https://travis-ci.org/agt-the-walker/chess-utils)


# crc-first-row

This program prints
[Capablanca Random Chess](http://brainking.com/en/GameRules?tp=75) positions
with optional restrictions. K = King, N = Knight, etc. Note that I didn't
bother filtering out Gothic Chess positions since the patent for Gothic Chess
expired long ago.


## Requirements

* [Boost Program Options](http://www.boost.org/doc/libs/1_57_0/doc/html/program_options.html)
* [GNU Compiler Collection (GCC)](http://www.gnu.org/software/gcc/), recent
  enough to support C++11
* [GNU Make](http://www.gnu.org/software/make/)


## Usage

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


# omegachess-pending

Print the number of pending games (i.e. with your turn to move) on
http://omegachess.ru/. It accepts the following flags:
* `--genmon`: if there are pending games, print the number in red using
  [xfce4-genmon-plugin](http://goodies.xfce.org/projects/panel-plugins/xfce4-genmon-plugin)
  XML tags


## Requirements

* [Ruby](http://www.ruby-lang.org/en/) 2.0.0+
* [Nokogiri](https://rubygems.org/gems/nokogiri) gem
* [netrc](https://rubygems.org/gems/netrc) gem


## Usage

Please run the following command the first time:

    # replace "Agt" below by your http://omegachess.ru/ login
    $ echo 'machine omegachess.ru login Agt' >>~/.netrc

Then:

    $ ./omegachess-pending
    2  # i.e. it's your move in two games
