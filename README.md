# deck-shuffle

#### How to build

##### OSX
`$ make shuffle` will create a binary called `shuffle`

#### How to use
`$ ./shuffle <decksize>` will return how many rounds it takes to shuffle unique deck of `decksize` cards.

#### Note
This repo contains implementation in C (faster) and in Haskell (shorter: 27 lines, slower). This repo also contains
pre-built binaries (`shuffle` is compiled C implementation, `shuffle_hs` is compiled Haskell version, both binaries
are built on OSX, so I can't say it will run on other arch).
