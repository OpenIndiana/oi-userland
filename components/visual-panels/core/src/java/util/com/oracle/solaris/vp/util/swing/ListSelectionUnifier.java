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

package com.oracle.solaris.vp.util.swing;

import java.util.*;
import com.oracle.solaris.vp.util.swing.event.*;

/**
 * The {@code ListSelectionHandler} class unifies the selection of multiple
 * {@code ExtListSelectionModel}s, making them appear to operate as a
 * single list.
 * <p>
 * When a selection is set in any model, the selections in all other models are
 * cleared.  Adding to or removing from the selection in any model has no effect
 * on the other models.
 */
public class ListSelectionUnifier implements ExtListSelectionListener {
    //
    // Instance data
    //

    private List<ExtListSelectionModel> models =
	new ArrayList<ExtListSelectionModel>();

    //
    // ExtListSelectionListener methods
    //

    @Override
    public void selectionChanged(ExtListSelectionEvent e) {
	if (e.getType() == ExtListSelectionEvent.Type.SET) {
	    synchronized (models) {
		ExtListSelectionModel source = e.getSource();
		for (ExtListSelectionModel model : models) {
		    if (model != source) {
			model.clearSelection();
		    }
		}
	    }
	}
    }

    //
    // ListSelectionHandler methods
    //

    public void addModel(ExtListSelectionModel model) {
	synchronized (models) {
	    model.addExtListSelectionListener(this);
	    models.add(model);
	}
    }

    public void clearSelection() {
	synchronized (models) {
	    for (ExtListSelectionModel model : models) {
		model.clearSelection();
	    }
	}
    }

    public void removeModel(ExtListSelectionModel model) {
	synchronized (models) {
	    models.remove(model);
	    model.removeExtListSelectionListener(this);
	}
    }
}
