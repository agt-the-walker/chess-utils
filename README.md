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

    $ vim ~/.netrc  # adapt accordingly
    machine omegachess.ru login <your login on http://omegachess.ru/>

    $ ./omegachess-pending
    2  # it's your move in two games
