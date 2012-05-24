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

package com.oracle.solaris.vp.panel.swing.control;

import java.awt.*;
import java.awt.event.*;
import java.io.IOException;
import java.util.*;
import java.util.List;
import javax.swing.*;
import com.oracle.solaris.vp.panel.common.*;
import com.oracle.solaris.vp.panel.common.action.ActionException;
import com.oracle.solaris.vp.panel.common.control.*;
import com.oracle.solaris.vp.panel.common.model.PanelDescriptor;
import com.oracle.solaris.vp.panel.common.view.*;
import com.oracle.solaris.vp.panel.swing.view.SwingBusyIndicator;
import com.oracle.solaris.vp.util.misc.finder.Finder;
import com.oracle.solaris.vp.util.misc.IconUtil;
import com.oracle.solaris.vp.util.swing.*;
import com.oracle.solaris.vp.util.swing.glass.*;

public class WindowControl<P extends PanelDescriptor, C extends Window>
    extends SwingControl<P, C> implements HasBusyIndicator {

    private static final String RAD_FMRI = "system/rad";

    //
    // Inner classes
    //

    private static class BusyGlassPaneIndicator extends BusyGlassPane
	implements SwingBusyIndicator {

	@Override
	public boolean isBusyIndicatorDisplayed() {
	    return isShowing();
	}

	@Override
	public void setBusyIndicatorDisplayed(final boolean displayed) {
	    GUIUtil.invokeAndWait(
		new Runnable() {
		    @Override
		    public void run() {
			getParent().setVisible(displayed);
		    }
		});
	}
    }

    //
    // Instance data
    //

    // The Control from which the window title is derived
    private Control titleControl;

    // The Control from which the window icons are derived
    private Control iconControl;

    private WindowListener windowClosingListener =
	new WindowAdapter() {
	    @Override
	    public void windowClosing(WindowEvent e) {
		WindowControl.this.windowClosing();
	    }
	};

    private BusyGlassPaneIndicator busy;

    // Listener to hide the visual "flicker" that could occur when
    // navigating between distant Controls within this window
    private NavigationListener noFlicker =
	new NavigationListener() {
	    @Override
	    public void navigationStarted(final NavigationStartEvent e) {
		setGlassPaneVisible(true);
	    }

	    @Override
	    public void navigationStopped(NavigationStopEvent e) {
		setGlassPaneVisible(false);
	    }

	    private void setGlassPaneVisible(final boolean visible) {
		final Window window = getComponent();
		if (window instanceof RootPaneContainer) {
		    GUIUtil.invokeAndWait(
			new Runnable() {
			    @Override
			    public void run() {
				((RootPaneContainer)window).getGlassPane().
				    setVisible(visible);
			    }
			});
		}
	    }
	};

    private ConnectionListener connListener =
	new ConnectionListener() {
	    @Override
	    public void connectionChanged(ConnectionEvent event) {
		busy.setBusyIndicatorDisplayed(false);
	    }

	    @Override
	    public void connectionFailed(ConnectionEvent event) {
		// Prevent interaction with GUI until connection is repaired
		busy.setMessage(Finder.getString("connection.failed.message",
		    event.getConnectionInfo().getHost(), RAD_FMRI));

		Action quit =
		    new AbstractAction(Finder.getString(
			"connection.failed.button.quit")) {

			@Override
			public void actionPerformed(ActionEvent event) {
			    getNavigator().asyncExec(
				new Runnable() {
				    @Override
				    public void run() {
					try {
					    getClientContext().closeInstance(
						true);
					} catch (ActionException ignore) {
					}
				    }
				});
			}
		    };

		Action reconnect =
		    new AbstractAction(Finder.getString(
			"connection.failed.button.reconnect")) {

			@Override
			public void actionPerformed(ActionEvent event) {
			    getNavigator().asyncExec(
				new Runnable() {
				    @Override
				    public void run() {
					try {
                                            getClientContext().login(null,
						false);
					} catch (ActionException ignore) {
					}
				    }
				});
			}
		    };

		busy.setActions(quit, reconnect);
		busy.setDelay(0);
		busy.setBusyIndicatorDisplayed(true);
	    }
	};

    //
    // Constructors
    //

    public WindowControl(String id, String name, P descriptor) {
	super(id, name, descriptor);
    }

    //
    // HasBusyIndicator methods
    //

    @Override
    public BusyIndicator getBusyIndicator() {
	return busy;
    }

    //
    // Control methods
    //

    @Override
    public void descendantStarted(Control[] path) {
	super.descendantStarted(path);

	Control control = path[path.length - 1];
	controlStarted(control);
    }

    @Override
    public void descendantStopped(Control[] path) {
	super.descendantStopped(path);

	Control control = path[path.length - 1];
	controlStopped(control);
    }

    @Override
    public Navigable[] getForwardingPath(boolean childStopped) {
	ensureChildrenCreated();

	if (childStopped) {
	    return new Navigable[] {Navigator.PARENT_NAVIGABLE};
	}

	if (children.size() > 0) {
	    // Automatically view first child
	    return new Navigable[] {children.get(0)};
	}

	return super.getForwardingPath(childStopped);
    }

    @Override
    public void start(Navigator navigator, Map<String, String> parameters)
	throws NavigationAbortedException, InvalidParameterException,
	NavigationFailedException {

	super.start(navigator, parameters);

	Window window = getComponent();
	window.addWindowListener(windowClosingListener);

	// Wait until the navigation is complete, then show the window (as long
	// as this Control is still started)
	getNavigator().asyncExec(
	    new Runnable() {
		@Override
		public void run() {
		    if (isStarted()) {
			ConnectionInfo info = getPanelDescriptor().
			    getClientContext().getConnectionInfo();

			try {
			    // Test connection.
			    info.getConnector().
				getMBeanServerConnection();
			} catch (IOException e) {
			    // Show indicator for broken connection.
			    connListener.connectionFailed(
				new ConnectionEvent(this, info));
			}

			// Use event thread in case setVisible blocks
			EventQueue.invokeLater(
			    new Runnable() {
				@Override
				public void run() {
				    setVisible();
				}
			    });
		    }
		}
	    });

	controlStarted(this);

	navigator.addNavigationListener(noFlicker);
	noFlicker.navigationStarted(null);

        getPanelDescriptor().getClientContext().addConnectionListener(
	    connListener);
    }

    @Override
    public void stop(boolean isCancel) throws NavigationAbortedException {
	Navigator navigator = getNavigator();
	super.stop(isCancel);

	Window window = getComponent();
	window.removeWindowListener(windowClosingListener);
	window.setVisible(false);

	controlStopped(this);

	noFlicker.navigationStopped(null);
	navigator.removeNavigationListener(noFlicker);

	getPanelDescriptor().getClientContext().removeConnectionListener(
	    connListener);
    }

    //
    // SwingControl methods
    //

    @Override
    protected void configComponent(C comp) {
	super.configComponent(comp);

	Window window = getComponent();
	if (window instanceof RootPaneContainer) {
	    LayeredGlassPane layered = new LayeredGlassPane();

	    busy = new BusyGlassPaneIndicator();
	    layered.add(busy);

	    ImageCaptureGlassPane capture = new ImageCaptureGlassPane();
	    layered.add(capture);

	    ((RootPaneContainer)window).setGlassPane(layered);
	}
    }

    //
    // WindowControl methods
    //

    /**
     * Gets the title of this {@code Window}, if supported.  This default
     * implementation returns {@code null}.
     *
     * @return	    the title, or {@code null} if this {@code WindowControl}'s
     *		    {@code Window} does not support a title
     */
    protected String getWindowTitle() {
	return null;
    }

    /**
     * Shows the window.  This method is called on the AWT event thread, after
     * navigation has completed.
     */
    protected void setVisible() {
	getComponent().setVisible(true);
    }

    /**
     * Sets the title of this {@code Window}, if supported.  This default
     * implementation does nothing.
     *
     * @param	    title
     *		    the title, or {@code null} if this {@code WindowControl}'s
     *		    {@code Window} does not support a title
     */
    protected void setWindowTitle(String title) {
    }

    /**
     * Called on the AWT event thread when the user closes the window directly.
     * This default implementation attempts to navigate upward one level in the
     * navigation stack.
     */
    protected void windowClosing() {
	getNavigator().goToAsync(false, this, Navigator.PARENT_NAVIGABLE);
    }

    //
    // Private methods
    //

    private void controlStarted(Control control) {
	String title = getWindowTitle();
	if (title == null || title.isEmpty()) {
	    String name = control.getName();
	    if (name != null) {
		titleControl = control;
		setWindowTitle(name);
	    }
	}

	Window window = getComponent();
	List<? extends Image> images = window.getIconImages();
	if (images == null || images.isEmpty()) {
	    if (control instanceof HasIcons) {
		List<? extends Icon> icons = ((HasIcons)control).getIcons();
		if (icons != null && !icons.isEmpty()) {
		    iconControl = control;
		    window.setIconImages(IconUtil.toImages(icons));
		}
	    }
	}
    }

    private void controlStopped(Control control) {
	if (titleControl == control) {
	    setWindowTitle(null);
	    titleControl = null;
	}

	if (iconControl == control) {
	    getComponent().setIconImages(null);
	    iconControl = null;
	}
    }
}
