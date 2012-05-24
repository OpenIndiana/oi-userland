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
 * Copyright (c) 2011, 2012, Oracle and/or its affiliates. All rights reserved.
 */

package com.oracle.solaris.vp.panels.zconsole.client.text;

import java.io.IOException;
import java.util.logging.Level;
import javax.management.*;
import com.oracle.solaris.adr.Stability;
import com.oracle.solaris.rad.jmx.*;
import com.oracle.solaris.rad.zonesbridge.IOMXBean;
import com.oracle.solaris.vp.panel.common.ClientContext;
import com.oracle.solaris.vp.panel.common.api.panel.MBeanUtil;
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
	throws JMException, IncompatibleVersionException, IOException {

	super(id, context);

	MBeanServerConnection mbsc = context.getConnectionInfo().getConnector().
	    getMBeanServerConnection();

	ObjectName oName = MBeanUtil.makeObjectName(
	    "com.oracle.solaris.rad.zonesbridge", "IO");

	IOMXBean bean;
	try {
	    bean = RadJMX.newMXBeanProxy(mbsc, oName, IOMXBean.class,
		Stability.PRIVATE);
	} catch (IncompatibleVersionException e) {
	    String msg = "Incompatible client and server versions for: " +
		IOMXBean.class.getSimpleName();
	    getLog().log(Level.SEVERE, msg, e);
	    throw e;
	} catch (JMException e) {
	    // InstanceNotFoundException, IntrospectionException,
	    // or ReflectionException
	    String msg = "Error getting MBean information for: " + oName;
	    getLog().log(Level.SEVERE, msg, e);
	    throw e;
	} catch (IOException e) {
	    String msg = "Error contacting MBean server while creating " +
		"proxy for: " + IOMXBean.class.getSimpleName();
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
