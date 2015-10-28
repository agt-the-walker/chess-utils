# Purpose

## omegachess-pending

Print the number of pending games (i.e. with your turn to move) on
http://omegachess.ru/.


# Requirements

* [Ruby](http://www.ruby-lang.org/en/) 2.0.0+
* [Nokogiri](https://rubygems.org/gems/nokogiri) gem
* [netrc](https://rubygems.org/gems/netrc) gem


# Usage

    $ vim ~/.netrc  # adapt accordingly
    machine omegachess.ru login <your login on http://omegachess.ru/>

    $ ./omegachess-pending
    2  # it's your move in two games
