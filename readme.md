# Exercise Generator

This is a tool for generating practice exercises for musical instruments. I'm creating it because I am trying to sight-read guitar, but I have been learning scales by patterns so I need something that fits within a scale but forces me to *read* the music rather than just picking the "position" from the key signature and starting note.

## Get the code

```
$ git clone https://github.com/guysherman/exercise-generator.git

```
## Get the library Dependencies

You'll need to install python, cpp-check and gtkmm-3.0 from your distribution's package repostitory. Note I compile with Clang 3.8, you should be fine with GCC 5+, but YMMV. Raise an issue/pr if you do have any problems.

## Get the external source-dependencies

At a the same level as where you cloned the `exercise-generator` repository (ie it should be a sibling, not a child):

```
$ git clone https://github.com/jdkoftinoff/jdksmidi.git
$ cd jdksmidi
$ ./configure
$ make

```
You *may* need to update the symlinks in the dep/jdksmidi directory, but you shouldn't because they are relative paths.

## Build

In the root of the exercise-generator repository

```
$ ./waf configure
$ ./waf

```
