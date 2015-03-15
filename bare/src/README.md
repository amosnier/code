# Source code

## Applications

Since the purpose of this project is mostly to explore hardware features, the
structure supports the easy creation of new applications (under `apps`).

## Samples

The structure also allows the easy building and testing of test applications
provided by ST in their STM32F4Cube package (under `samples`). For the latter,
the ideas is, for every test application to be built, to create a corresponding
directory under `samples`, that will hold symlinks to the source code, i.e. the
structure will point to the unmodified ST source code from the STM32F4Cube copy
in our file system, rather than copy/paste code to our own structure. This
mechanism is implemented in our generic application Makefile, that supports
pointing to source code files and header files located anywhere in the file
system.

## Shared code

Code shared between several applications is stored under `shared`. No concept of
library is used. Instead, every application using the concerned modules build
them. The advantage of this approach is to allow module configuration via
callback header files, whcih is very simple. The inconvienient is that module
building is performed multiple times, but that is not a problem at the current
volume of code.
