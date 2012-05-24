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

import javax.swing.event.*;
import com.oracle.solaris.vp.util.misc.event.*;

public class ListDataListeners extends EventListeners<ListDataListener>
    implements ListDataListener {

    //
    // Static data
    //

    private static final EventDispatcher<ListDataEvent, ListDataListener>
	cDispatcher = new EventDispatcher<ListDataEvent, ListDataListener>() {
	    public void dispatch(ListDataListener listener,
		ListDataEvent event) {
		listener.contentsChanged(event);
	    }
	};

    private static final EventDispatcher<ListDataEvent, ListDataListener>
	aDispatcher = new EventDispatcher<ListDataEvent, ListDataListener>() {
	    public void dispatch(ListDataListener listener,
		ListDataEvent event) {
		listener.intervalAdded(event);
	    }
	};

    private static final EventDispatcher<ListDataEvent, ListDataListener>
	rDispatcher = new EventDispatcher<ListDataEvent, ListDataListener>() {
	    public void dispatch(ListDataListener listener,
		ListDataEvent event) {
		listener.intervalRemoved(event);
	    }
	};

    //
    // ListDataListener methods
    //

    @Override
    public void contentsChanged(ListDataEvent event) {
	dispatch(cDispatcher, event);
    }

    @Override
    public void intervalAdded(ListDataEvent event) {
	dispatch(aDispatcher, event);
    }

    @Override
    public void intervalRemoved(ListDataEvent event)  {
	dispatch(rDispatcher, event);
    }
}
