# Purpose

## omegachess-pending

Print the number of pending games (i.e. with your turn to move) on
http://omegachess.ru/. It accepts the following flags:
* `--genmon`: if there are pending games, print the number in red using
  [xfce4-genmon-plugin](http://goodies.xfce.org/projects/panel-plugins/xfce4-genmon-plugin)
  XML tags


# Requirements

* [Ruby](http://www.ruby-lang.org/en/) 2.0.0+
* [Nokogiri](https://rubygems.org/gems/nokogiri) gem
* [netrc](https://rubygems.org/gems/netrc) gem


# Usage

Please run the following command the first time:

    # replace "Agt" below by your http://omegachess.ru/ login
    $ echo 'machine omegachess.ru login Agt' >>~/.netrc

Then:

    $ ./omegachess-pending
    2  # i.e. it's your move in two games
