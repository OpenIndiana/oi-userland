/*
 * CDDL HEADER START
 *
 * The contents of this file are subject to the terms of the
 * Common Development and Distribution License (the "License").
 * You may not use this file except in compliance with the License.
 *
 * You can obtain a copy of the license at usr/src/OPENSOLARIS.LICENSE
 * or http://www.opensolaris.org/os/licensing.
 * See the License for the specific language governing permissions
 * and limitations under the License.
 *
 * When distributing Covered Code, include this CDDL HEADER in each
 * file and include the License file at usr/src/OPENSOLARIS.LICENSE.
 * If applicable, add the following below this CDDL HEADER, with the
 * fields enclosed by brackets "[]" replaced with your own identifying
 * information: Portions Copyright [yyyy] [name of copyright owner]
 *
 * CDDL HEADER END
 */

/*
 * Copyright (c) 2009, 2012, Oracle and/or its affiliates. All rights reserved.
 */

package com.oracle.solaris.vp.util.swing.event;

import java.awt.event.*;
import com.oracle.solaris.vp.util.misc.event.*;

public class ActionListeners extends EventListeners<ActionListener>
    implements ActionListener {

    //
    // Static data
    //

    private static final EventDispatcher<ActionEvent, ActionListener>
	dispatcher = new EventDispatcher<ActionEvent, ActionListener>() {
	    public void dispatch(ActionListener listener, ActionEvent event) {
		listener.actionPerformed(event);
	    }
	};

    //
    // ActionListener methods
    //

    @Override
    public void actionPerformed(ActionEvent event) {
	dispatch(dispatcher, event);
    }
}
