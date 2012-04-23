#
# Copyright 2009 Sun Microsystems, Inc.  All rights reserved.
# Use is subject to license terms.
#

#
# This file is sourced by interactive ksh93 shells before ${HOME}/.kshrc
#

# Enable "gmacs"+"multiline" editor mode if the user did not set an
# input mode yet (for example via ${EDITOR}, ${VISUAL} or any
# "set -o" flag)
if [[ "$(set +o)" != ~(Er)--(gmacs|emacs|vi)( .*|) ]] ; then
	set -o gmacs
	# enable multiline input mode
	set -o multiline
	# enable globstar mode (match subdirs with **/)
	set -o globstar
fi

# Set a default prompt (<username>@<hostname>:<path><"($|#) ">) if
# then variable does not exist in the environment.
#
# Algorithm:
# 1. Define "ellipsis", either Unicode #2026 for unicode locales
# and "..." otherwise
# ([[ "${LC_ALL}/${LANG}" = ~(Elr)(.*UTF-8/.*|/.*UTF-8) ]]
# ensures that the pattern matches the leftmost sequence
# containing *.UTF-8, allowing to match either LC_ALL or
# LANG when LC_ALL is not set)
# 2. If PWD is within HOME replace value of HOME with '~'
# If the PWD is longer than 30 charatcers shorten it to 30 chars
# print '#' for user "root" and '$' for normal users
# Notes:
# - printf "%*s\r%s" COLUMNS "") # is used at the beginning to
#   work around a bug in the "multiline" handling code which
#   causes the shell to override its own prompt when the edit
#   line overflows (this happens if the terminal cursor
#   position is not 0 when PS1 is printed).
# - PS1 will initially be empty until either...
#   a) ... someone sets the variable
#       or
#   b) ... the prompt is displayed for the first time (default is
#     '$ ' for normal users and '# ' for user "root")
# - The statement below will not work if someone sources /etc/ksh.kshrc
#   unless PS1 gets "unset" first.
# - Make sure to use absolute paths (e.g. /usr/bin/hostname) to make
#   sure PS1 works in cases where PATH does not contain /usr/bin/
if [[ "$(set)" != ~(E)PS1= && "${PS1}" == '' ]] ; then
	PS1='$(set +o xtrace +o errexit
                printf "%*s\r%s" COLUMNS ""
                printf "%s@%s:" "${LOGNAME}" "$(/usr/bin/hostname)"
		ellip="${
			[[ "${LC_ALL}/${LANG}" == ~(Elr)(.*UTF-8/.*|/.*UTF-8) ]] &&
				printf "\u[2026]\n" || print "..." ; }"
		p="${PWD/~(El)${HOME}/\~}"
		(( ${#p} > 30 )) &&
			print -r -n -- "${ellip}${p:${#p}-30:30}" ||
			print -r -n -- "${p}"
		[[ "${LOGNAME}" == "root" ]] && print -n "# " || print -n "\$ "
		)'
fi
