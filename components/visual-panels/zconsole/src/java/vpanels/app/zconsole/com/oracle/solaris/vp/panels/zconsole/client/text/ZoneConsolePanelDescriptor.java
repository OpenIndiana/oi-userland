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
 * Copyright (c) 2011, 2013, Oracle and/or its affiliates. All rights reserved.
 */

package com.oracle.solaris.vp.panels.zconsole.client.text;

import java.io.IOException;
import java.util.logging.Level;
import com.oracle.solaris.rad.client.RadException;
import com.oracle.solaris.rad.connect.Connection;
import com.oracle.solaris.rad.zonesbridge.IO;
import com.oracle.solaris.vp.panel.common.ClientContext;
import com.oracle.solaris.vp.panel.common.control.Control;
import com.oracle.solaris.vp.panel.common.model.*;

@SuppressWarnings({"serial"})
public class ZoneConsolePanelDescriptor
    extends AbstractPanelDescriptor<ManagedObject> {

    //
    // Instance data
    //

    private Control control;

    //
    // Constructors
    //

    public ZoneConsolePanelDescriptor(String id, ClientContext context)
	throws IOException {

	super(id, context);

	IO bean = null;
	try {
		Connection conn = context.getConnectionInfo().getConnection();
		bean = conn.getObject(new IO());
	} catch (RadException e) {
	    String msg = "Error getting object information for: " +
		IO.class.getSimpleName();
	    getLog().log(Level.SEVERE, msg, e);
	    throw e;
	} catch (IOException e) {
	    String msg = "Error contacting server while creating " +
		"proxy for: " + IO.class.getSimpleName();
	    getLog().log(Level.SEVERE, msg, e);
	    throw e;
	}

	control = new MainControl(this, bean);
    }

    //
    // PanelDescriptor methods
    //

    @Override
    public Control getControl() {
	return control;
    }
}
