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

import java.awt.Window;
import java.io.IOException;
import java.util.Map;
import java.util.logging.Level;
import javax.help.HelpSet;
import com.oracle.solaris.rad.ObjectException;
import com.oracle.solaris.rad.jmx.IncompatibleVersionException;
import com.oracle.solaris.vp.client.common.*;
import com.oracle.solaris.vp.panel.common.*;
import com.oracle.solaris.vp.panel.common.action.ActionAbortedException;
import com.oracle.solaris.vp.panel.common.api.panel.*;
import com.oracle.solaris.vp.panel.common.control.*;
import com.oracle.solaris.vp.panel.common.model.PanelDescriptor;
import com.oracle.solaris.vp.panel.swing.control.SwingNavigator;
import com.oracle.solaris.vp.util.misc.finder.Finder;
import com.oracle.solaris.vp.util.swing.GUIUtil;

public class AppRootControl extends DefaultControl<PanelDescriptor> {
    //
    // Static data
    //

    public static final String ID = "vp";

    //
    // Instance data
    //

    private PanelDescriptorFactory factory;
    private HelpSet helpSet;
    private PanelMXBeanTracker panelBeanTracker;

    //
    // Constructors
    //

    public AppRootControl(ClientContext context) {
	super(ID, null, context);

	PanelResourceManager manager = new AppPanelResourceManager(context);
	factory = new SwingPanelDescriptorFactory(context, manager);
    }

    //
    // Control methods
    //

    @Override
    public void childStarted(Control control) {
	super.childStarted(control);

	PanelDescriptor descriptor = getChildPanelDescriptor();
	helpSet = descriptor == null ? null : descriptor.getHelpSet();
	if (helpSet != null) {
	    getClientContext().getHelpBroker().getHelpSet().add(helpSet);
	}
    }

    @Override
    public void childStopped(Control control) {
	super.childStopped(control);

	if (helpSet != null) {
	    getClientContext().getHelpBroker().getHelpSet().remove(helpSet);
	}
    }

    @Override
    public Control getChildControl(String id) {
	Control child = super.getChildControl(id);
	if (child == null) {
	    ClientContext context = getClientContext();

	    try {
		CustomPanel panel = panelBeanTracker.getBean().getPanel(
		    id, null);
		if (panel != null) {
		    child = factory.getPanelDescriptor(panel).getControl();
		    addChildren(child);
		}

	    } catch (ActionAbortedException e) {
		// No need to display this error
		getLog().log(Level.SEVERE, "download cancelled", e);

	    } catch (PanelResourceException e) {
		showError(e.getMessage(), e.getCause());

	    // Assume invalid panel name
	    } catch (ObjectException e) {
	    }
	}

	return child;
    }

    @Override
    public void start(Navigator navigator, Map<String, String> parameters)
	throws NavigationAbortedException, InvalidParameterException,
	NavigationFailedException {

	super.start(navigator, parameters);

	try {
	    panelBeanTracker = new PanelMXBeanTracker(getClientContext());

	} catch (TrackerException e) {
	    String message = null;
	    Throwable cause = e.getCause();

	    if (cause instanceof IncompatibleVersionException) {
		IncompatibleVersionException ive =
		    (IncompatibleVersionException)cause;

		message = Finder.getString("panelproxy.error.version",
		    ive.getClientVersion(), ive.getServerVersion(),
		    ive.getInterfaceClass().getSimpleName());
	    } else if (cause instanceof IOException) {
		message = Finder.getString("panelproxy.error.io");
	    } else {
		message = Finder.getString("panelproxy.error.general");
	    }

	    throw new NavigationFailedException(message, cause);
	}
    }

    @Override
    public void stop(boolean isCancel) throws NavigationAbortedException {
	super.stop(isCancel);
	panelBeanTracker.dispose();
	panelBeanTracker = null;
    }

    //
    // AppRootControl methods
    //

    protected void showError(final String message,
        final Throwable cause) {
        getLog().log(Level.SEVERE, message, cause);

        // May be null
        final Window window = SwingNavigator.getFirstWindow(
            getClientContext().getNavigator());

        GUIUtil.invokeAndWait(
            new Runnable() {
                @Override
                public void run() {
                    GUIUtil.showError(window, null, message);
                }
            });
    }

    //
    // Private methods
    //

    private PanelDescriptor getChildPanelDescriptor() {
	Control child = getRunningChild();
	if (child != null && child instanceof DefaultControl) {
	    return ((DefaultControl)child).getPanelDescriptor();
	}
	return null;
    }
}
