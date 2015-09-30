# ~/.profile: executed by the command interpreter for login shells.
# This file is not read by bash(1), if ~/.bash_profile or ~/.bash_login
# exists.
# see /usr/share/doc/bash/examples/startup-files for examples.
# the files are located in the bash-doc package.

# the default umask is set in /etc/profile; for setting the umask
# for ssh logins, install and configure the libpam-umask package.
#umask 022

# if running bash
if [ -n "$BASH_VERSION" ]; then
    # include .bashrc if it exists
    if [ -f "$HOME/.bashrc" ]; then
	. "$HOME/.bashrc"
    fi
fi

# set PATH so it includes user's private bin if it exists
if [ -d "$HOME/bin" ] ; then
    PATH="$HOME/bin:$PATH"
fi

# if [ -d "$HOME/nand2tetris/tools" ] ; then
#     PATH="$HOME/nand2tetris/tools:$PATH"
# fi

if [ -d "$HOME/Qt/Tools/QtCreator/bin" ] ; then
    PATH="$HOME/Qt/Tools/QtCreator/bin:$PATH"
fi

if [ -d "$HOME/cmake-3.3.2-Linux-x86_64/bin" ] ; then
    PATH="$HOME/cmake-3.3.2-Linux-x86_64/bin:$PATH"
fi

export EDITOR=emacs
