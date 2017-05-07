#
# CDDL HEADER START
#
# The contents of this file are subject to the terms of the
# Common Development and Distribution License (the "License").
# You may not use this file except in compliance with the License.
#
# You can obtain a copy of the license at usr/src/OPENSOLARIS.LICENSE
# or http://www.opensolaris.org/os/licensing.
# See the License for the specific language governing permissions
# and limitations under the License.
#
# When distributing Covered Code, include this CDDL HEADER in each
# file and include the License file at usr/src/OPENSOLARIS.LICENSE.
# If applicable, add the following below this CDDL HEADER, with the
# fields enclosed by brackets "[]" replaced with your own identifying
# information: Portions Copyright [yyyy] [name of copyright owner]
#
# CDDL HEADER END
#
#
# Copyright (c) 2008, 2010, Oracle and/or its affiliates. All rights reserved.
#
import gettext
from os import putenv, getenv


'''Set "_" to be the character that flags text that should be
extracted by xgettext for translation"
'''
_ = gettext.translation("ddutext", "/usr/share/locale",
                        fallback=True).gettext

'''Set the ESCDELAY environment variable, if it's not yet set
(n)curses will wait ESCDELAY milliseconds after receiving an
ESC key as input before processing the input. It defaults to 1000 ms
(1 sec), which would make Esc-# navigation horrendously slow, so
we default to 0 instead.
'''
ESCDELAY = getenv("ESCDELAY")
try:
    int(ESCDELAY)
except (TypeError, ValueError):
    putenv("ESCDELAY", "250")
del ESCDELAY
