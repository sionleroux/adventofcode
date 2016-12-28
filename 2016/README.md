The code for 2016 doesn't have Makefiles because it turns out make is
smart enough to imply how to build a binary `something` if there is a
source file `something.c`, so I just set Vim's "make program" to use
this implicit build and run it for me:

    :let &makeprg="make %:r && ./%:r"
