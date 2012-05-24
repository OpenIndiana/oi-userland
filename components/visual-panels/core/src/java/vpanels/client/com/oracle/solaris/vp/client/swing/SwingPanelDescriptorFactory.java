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

package com.oracle.solaris.vp.client.swing;

import java.util.logging.*;
import com.oracle.solaris.vp.client.common.*;
import com.oracle.solaris.vp.panel.common.ClientContext;
import com.oracle.solaris.vp.util.misc.finder.Finder;

/**
 * A subclass of {@code PanelDescriptorFactory} which provides Swing-specific
 * implementations of {@code getPanelDescriptor}.
 */
public class SwingPanelDescriptorFactory extends PanelDescriptorFactory {

    //
    // Constructors
    //

    public SwingPanelDescriptorFactory(ClientContext context,
	PanelResourceManager manager) {

	super(context, manager);
    }

    //
    // PanelDescriptorFactory methods
    //

    @Override
    protected ErrorPanelDescriptor getErrorPanelDescriptor(
	String name, ClientContext context) {

	return new SwingErrorPanelDescriptor(name, context);
    }

    //
    // Private methods
    //

    private void log(Throwable e, String resource, Object... args) {
	Logger.getLogger(getClass().getName()).log(
	    Level.WARNING, Finder.getString(resource, args), e);
    }
}
