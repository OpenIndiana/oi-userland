#
# Initialization of environment modules for ksh/bash shells.
#

MODULEHOME=/usr/lib/Modules/latest

case "$0" in
-sh)
	. ${MODULEHOME}/init/sh
	;;
-ksh | -ksh93 | -jsh)
	. ${MODULEHOME}/init/ksh
	;;
-zsh)
	. ${MODULEHOME}/init/zsh
	;;
-bash)
	. ${MODULEHOME}/init/bash
	;;
*)
	. ${MODULEHOME}/init/sh
	;;
esac

MANPATH='::'

export MANPATH

# Allow adding modules list in .modules
if [ -r $HOME/.modules ]; then
	. $HOME/.modules
fi

# Prepend user module path automatically
if [ -d $HOME/modules ]; then
	MODULEPATH=$HOME/modules:$MODULEPATH
        export MODULEPATH
fi
