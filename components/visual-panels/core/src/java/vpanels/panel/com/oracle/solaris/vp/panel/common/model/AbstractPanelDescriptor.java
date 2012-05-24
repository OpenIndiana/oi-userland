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
 * Copyright (c) 2010, 2012, Oracle and/or its affiliates. All rights reserved.
 */

package com.oracle.solaris.vp.panel.common.model;

import javax.help.*;
import com.oracle.solaris.vp.panel.common.*;
import com.oracle.solaris.vp.util.misc.finder.Finder;

public abstract class AbstractPanelDescriptor<C extends ManagedObject>
    extends AbstractManagedObject<C> implements PanelDescriptor<C> {

    //
    // Instance data
    //

    // Whether or not an attempt has been made to find this PanelDescriptor's
    // HelpSet; this object serves both as a flag and a mutex lock when looking
    // for the HelpSet (using "this" would be a bit heavyweight)
    private boolean[] helpSetSought = new boolean[1];
    private HelpSet helpSet;

    private ClientContext context;

    private ConnectionListener newHostListener =
	new ConnectionListener() {
	    @Override
	    public void connectionChanged(ConnectionEvent event) {
		ConnectionInfo oldInfo = event.getOldConnectionInfo();
		ConnectionInfo newInfo = event.getConnectionInfo();

		// Has the host changed?
		if (!oldInfo.matchesHost(newInfo.getHost())) {
		    // This Control no longer applies to the selected host
		    dispose();
		}
	    }

	    @Override
	    public void connectionFailed(ConnectionEvent event) {
                // There's nothing particularly helpful we can do here except
                // wait for the repaired connection in connectionChanged
	    }
	};

    //
    // Constructors
    //

    /**
     * Constructs an {@code AbstractPanelDescriptor} and adds a
     * {@link ConnectionListener} to destroy this {@link PanelDescriptor} when
     * the host in the given {@link ClientContext} changes.
     *
     * @param	    id
     *		    the unique id of this {@code AbstractPanelDescriptor}
     *
     * @param	    context
     *		    the client context linking this {@link PanelDescriptor} to
     *		    the application
     */
    public AbstractPanelDescriptor(String id, ClientContext context) {
	super(id);
	this.context = context;
	context.addConnectionListener(newHostListener);
    }

    //
    // ManagedObject methods
    //

    /**
     * Removes this {@code AbstractPanelDescriptor}'s {@link
     * ConnectionListener}, then calls the superclass implementation.
     */
    @Override
    public void dispose() {
	context.removeConnectionListener(newHostListener);
	super.dispose();
    }

    //
    // PanelDescriptor methods
    //

    @Override
    public ClientContext getClientContext() {
	return context;
    }

    /**
     * Default implementation that returns {@code true}.
     */
    @Override
    public boolean getHasFullPrivileges() {
	return true;
    }

    /**
     * Default implementation that uses this class's class loader to look for a
     * helpset named "help/app" relative to this class's package.
     *
     * @return	    a {@code Helpset}, or {@code null} if none could be found
     */
    @Override
    public HelpSet getHelpSet() {
	synchronized (helpSetSought) {
	    if (!helpSetSought[0]) {
		// Look for the HelpSet only once
		helpSetSought[0] = true;
		try {
		    String helpSetName = getClass().getPackage().getName().
			replaceAll("\\.", "/") + "/help/app";

		    ClassLoader loader = getClass().getClassLoader();
		    helpSet = Finder.getHelpSet(loader, helpSetName);
		} catch (HelpSetException ignore) {
		}
	    }
	}

	return helpSet;
    }
}
