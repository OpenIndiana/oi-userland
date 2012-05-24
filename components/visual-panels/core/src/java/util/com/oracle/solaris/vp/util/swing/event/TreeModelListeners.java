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

public class TreeModelListeners extends EventListeners<TreeModelListener>
    implements TreeModelListener {

    //
    // Static data
    //

    private static final EventDispatcher<TreeModelEvent, TreeModelListener>
	cDispatcher = new EventDispatcher<TreeModelEvent, TreeModelListener>() {
	    public void dispatch(TreeModelListener listener,
		TreeModelEvent event) {
		listener.treeNodesChanged(event);
	    }
	};

    private static final EventDispatcher<TreeModelEvent, TreeModelListener>
	iDispatcher = new EventDispatcher<TreeModelEvent, TreeModelListener>() {
	    public void dispatch(TreeModelListener listener,
		TreeModelEvent event) {
		listener.treeNodesInserted(event);
	    }
	};

    private static final EventDispatcher<TreeModelEvent, TreeModelListener>
	rDispatcher = new EventDispatcher<TreeModelEvent, TreeModelListener>() {
	    public void dispatch(TreeModelListener listener,
		TreeModelEvent event) {
		listener.treeNodesRemoved(event);
	    }
	};

    private static final EventDispatcher<TreeModelEvent, TreeModelListener>
	sDispatcher = new EventDispatcher<TreeModelEvent, TreeModelListener>() {
	    public void dispatch(TreeModelListener listener,
		TreeModelEvent event) {
		listener.treeStructureChanged(event);
	    }
	};

    //
    // TreeModelListener methods
    //

    @Override
    public void treeNodesChanged(TreeModelEvent event) {
	dispatch(cDispatcher, event);
    }

    @Override
    public void treeNodesInserted(TreeModelEvent event) {
	dispatch(iDispatcher, event);
    }

    @Override
    public void treeNodesRemoved(TreeModelEvent event) {
	dispatch(rDispatcher, event);
    }

    @Override
    public void treeStructureChanged(TreeModelEvent event) {
	dispatch(sDispatcher, event);
    }
}
