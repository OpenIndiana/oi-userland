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

import java.net.URL;
import java.util.logging.*;
import com.oracle.solaris.vp.client.common.*;
import com.oracle.solaris.vp.panel.common.*;
import com.oracle.solaris.vp.panel.common.action.ActionAbortedException;
import com.oracle.solaris.vp.panel.common.api.panel.CustomPanel;
import com.oracle.solaris.vp.panel.common.view.BusyIndicator;

public class AppPanelResourceManager extends PanelResourceManager {

    //
    // Instance data
    //

    private ClientContext context;

    //
    // Constructors
    //

    public AppPanelResourceManager(ClientContext context) {
	this.context = context;
    }

    //
    // PanelResourceManager methods
    //

    @Override
    protected URL[] downloadAll(ConnectionInfo info, CustomPanel panel)
	throws ActionAbortedException, PanelResourceException {

	BusyIndicator busy = context.getBusyIndicator();
	busy.setBusyIndicatorDisplayed(true);
	URL[] urls = super.downloadAll(info, panel);
	busy.setBusyIndicatorDisplayed(false);

	return urls;
    }

    @Override
    protected String getUserDir() {
    	return App.VP_USER_DIR;
    }

    @Override
    protected void showStatus(final String status) {
	Logger.getLogger(getClass().getName()).log(
	    Level.FINEST, status);
	context.getBusyIndicator().setMessage(status);
    }
}
