#Libraries

The directory includes libraries linked with applications. Hopefully, we have
source code for all of them, and they are built in their respective sub-directory
with the help of their respective `Makefile`. The application `Makefiles` shall
invoke the necessary library `Makefiles` systematically, that will rebuild the
libraries only if necessary.
