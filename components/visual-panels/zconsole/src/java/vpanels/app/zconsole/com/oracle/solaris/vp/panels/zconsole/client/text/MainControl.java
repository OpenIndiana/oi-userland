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

import java.util.Map;
import java.util.logging.Level;
import com.oracle.solaris.rad.ObjectException;
import com.oracle.solaris.rad.zonesbridge.IOMXBean;
import com.oracle.solaris.vp.panel.common.ConnectionInfo;
import com.oracle.solaris.vp.panel.common.control.*;
import com.oracle.solaris.vp.util.misc.TermUtil;
import com.oracle.solaris.vp.util.misc.finder.Finder;

public class MainControl extends DefaultControl<ZoneConsolePanelDescriptor> {
    //
    // Static data
    //

    public static final String PARAM_ZONE = "zone";
    public static final String PARAM_ESCAPE = "escape";
    public static final String PARAM_NOEXT = "noext";

    //
    // Instance data
    //

    private String zone;
    private long token;
    private IOMXBean bean;
    private BeanToStdout beanToStdout;
    private StdinToBean stdinToBean;

    //
    // Constructors
    //

    public MainControl(ZoneConsolePanelDescriptor descriptor,
	IOMXBean bean) {

	super(descriptor.getId(), descriptor.getName(), descriptor);
	this.bean = bean;
    }

    //
    // Control methods
    //

    @Override
    public void start(Navigator navigator, Map<String, String> parameters)
	throws NavigationAbortedException, InvalidParameterException,
	NavigationFailedException {

	byte escape = StdinToBean._ESCAPE;
	try {
	    escape = getParameter(parameters, PARAM_ESCAPE).getBytes()[0];
	// MissingParameterException, ArrayIndexOutOfBoundsException
	} catch (Throwable ignore) {
	}

	boolean noext = false;
	try {
            noext = Boolean.parseBoolean(getParameter(parameters,
		PARAM_NOEXT));
	// MissingParameterException, ArrayIndexOutOfBoundsException
	} catch (Throwable ignore) {
	}

	String zone = getParameter(parameters, PARAM_ZONE);

	try {
	    token = bean.openConsole(zone);
	} catch (SecurityException e) {
	    ConnectionInfo info = getClientContext().getConnectionInfo();
	    String user = info.getRole();
	    if (user == null) {
		user = info.getUser();
	    }
            throw new NavigationFailedException(Finder.getString(
		"error.security", user, info.getHost(), zone), e);
	} catch (ObjectException e) {
	    ConnectionInfo info = getClientContext().getConnectionInfo();
	    String user = info.getRole();
	    if (user == null) {
		user = info.getUser();
	    }
            throw new NavigationFailedException(Finder.getString(
		"error.general", user, info.getHost(), zone), e);
	}

	try {
	    TermUtil.setRawTty();
	} catch (Throwable e) {
	    closeBean();
            throw new NavigationFailedException(
		Finder.getString("error.tty"), e);
	}

	this.zone = zone;

	beanToStdout = new BeanToStdout(bean, token) {
	    @Override
	    public void done(boolean success) {
		doQuit();
	    }
	};
	new Thread(beanToStdout).start();

	stdinToBean = new StdinToBean(bean, token, escape, noext) {
	    @Override
	    public void done(boolean success) {
		doQuit();
	    }
	};
	new Thread(stdinToBean).start();

	super.start(navigator, parameters);
    }

    @Override
    public void stop(boolean isCancel) throws NavigationAbortedException {
	closeBean();
	try {
	    TermUtil.resetTty();
	} catch (Throwable e) {
	    getLog().log(Level.SEVERE, "unable to restore terminal settings",
		e);
	}

	zone = null;

	stdinToBean.interrupt();
	stdinToBean = null;
	beanToStdout = null;

	super.stop(isCancel);
    }

    //
    // Private methods
    //

    private void closeBean() {
	try {
	    bean.close(token);
	} catch (ObjectException e) {
	    getLog().log(Level.SEVERE, "unable to close console connection", e);
	}
    }
}
