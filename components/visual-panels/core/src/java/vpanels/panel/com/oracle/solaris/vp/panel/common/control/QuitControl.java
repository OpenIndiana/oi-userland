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

package com.oracle.solaris.vp.panel.common.control;

import java.util.Map;
import com.oracle.solaris.vp.panel.common.ClientContext;
import com.oracle.solaris.vp.panel.common.action.ActionAbortedException;
import com.oracle.solaris.vp.panel.common.model.PanelDescriptor;

/**
 * The {@code QuitControl} class is a convenience {@link Control} that shuts
 * down the running client instance when navigated to.
 */
public class QuitControl<P extends PanelDescriptor> extends DefaultControl<P> {
    //
    // Static data
    //

    public static final String ID = "quit";

    //
    // Constructors
    //

    public QuitControl(ClientContext context) {
	super(ID, null, context);
    }

    public QuitControl(P descriptor) {
	super(ID, null, descriptor);
    }

    //
    // Control methods
    //

    @Override
    public boolean isBrowsable() {
	// This Control should not be visible to the user
	return false;
    }

    /**
     * Unconditionally calls {@link ClientContext#closeInstance}.
     */
    @Override
    public void start(Navigator navigator, Map<String, String> parameters)
	throws NavigationAbortedException, InvalidParameterException,
	NavigationFailedException {

	super.start(navigator, parameters);

        // schedule this on the navigation thread so that it runs after this
        // navigation completes
	navigator.asyncExec(
	    new Runnable() {
		@Override
		public void run() {
		    try {
			getClientContext().closeInstance(true);
		    } catch (ActionAbortedException ignore) {
		    }
		}
	    });
    }
}
