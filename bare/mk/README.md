#GNU make scripts

## Building an application
The most important of the scripts in this directory is `make_app.mk`. An
application should symlink it to its own `Makefile`. It then just has to provide
a `specs.mk` file in the same directory as the `Makefile`, that will define the
`BASE` variable, which contains the path to the base directory of this project
(`bare/`), as well as other variables that define include path, source files to
be compiled, and a name for the elf target. The structure supports both
directories where all source files (`.c` and `.S`) are compiled, and directories
where only some files (to be listed specifically) are compiled. See examples
under `src/`.

## Recursive make: making sub-directories
`dir_rules.mk` can be included in a `Makefile` that defines the variable `dir`
to a list of sub-directories of the current directories to be made by recursive
make. That method is used to make the whole project from the top `Makefile`
under `bare/`.
