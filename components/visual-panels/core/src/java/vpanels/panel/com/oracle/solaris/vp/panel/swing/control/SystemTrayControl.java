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

package com.oracle.solaris.vp.panel.swing.control;

import java.awt.*;
import java.awt.event.*;
import java.net.URL;
import java.util.Map;
import java.util.logging.Level;
import javax.help.HelpSet;
import com.oracle.solaris.vp.panel.common.*;
import com.oracle.solaris.vp.panel.common.action.ActionAbortedException;
import com.oracle.solaris.vp.panel.common.control.*;
import com.oracle.solaris.vp.panel.common.model.PanelDescriptor;
import com.oracle.solaris.vp.panel.swing.view.AuthPanel;
import com.oracle.solaris.vp.util.misc.finder.Finder;

public class SystemTrayControl<P extends PanelDescriptor>
    extends SwingControl<P, Component> implements ConnectionListener,
    ActionListener, MouseListener, MouseMotionListener {

    //
    // Instance data
    //

    private TrayIcon trayIcon;
    private PopupMenu popup;

    //
    // Constructors
    //

    public SystemTrayControl(String id, String name, ClientContext context) {
	super(id, name, context);
    }

    public SystemTrayControl(String id, String name, P descriptor) {
	super(id, name, descriptor);
    }

    //
    // ConnectionListener methods
    //

    @Override
    public void connectionChanged(ConnectionEvent event) {
	if (popup != null) {
	    String text = AuthPanel.toString(
		getClientContext().getConnectionInfo(), true);
	    popup.setLabel(text);
	}
    }

    @Override
    public void connectionFailed(ConnectionEvent event) {
        // There's nothing particularly helpful we can do here except wait for
        // the repaired connection in connectionChanged
    }

    //
    // ActionListener methods
    //

    /**
     * As a convenience, this class is added as an {@code ActionListener} to the
     * {@link #createTrayIcon created} {@code TrayIcon}.  This method provides a
     * default empty implementation.
     */
    @Override
    public void actionPerformed(ActionEvent e) {
    }

    //
    // MouseListener methods
    //

    /**
     * As a convenience, this class is added as an {@code MouseListener} to the
     * {@link #createTrayIcon created} {@code TrayIcon}.  This method provides a
     * default empty implementation.
     */
    @Override
    public void mouseClicked(MouseEvent e) {
    }

    /**
     * As a convenience, this class is added as an {@code MouseListener} to the
     * {@link #createTrayIcon created} {@code TrayIcon}.  This method provides a
     * default empty implementation.
     */
    @Override
    public void mousePressed(MouseEvent e) {
    }

    /**
     * As a convenience, this class is added as an {@code MouseListener} to the
     * {@link #createTrayIcon created} {@code TrayIcon}.  This method provides a
     * default empty implementation.
     */
    @Override
    public void mouseReleased(MouseEvent e) {
    }

    /**
     * As a convenience, this class is added as an {@code MouseListener} to the
     * {@link #createTrayIcon created} {@code TrayIcon}.  This method provides a
     * default empty implementation.
     */
    @Override
    public void mouseEntered(MouseEvent e) {
    }

    /**
     * As a convenience, this class is added as an {@code MouseListener} to the
     * {@link #createTrayIcon created} {@code TrayIcon}.  This method provides a
     * default empty implementation.
     */
    @Override
    public void mouseExited(MouseEvent e) {
    }

    //
    // MouseMotionListener methods
    //

    /**
     * As a convenience, this class is added as an {@code MouseMotionListener}
     * to the {@link #createTrayIcon created} {@code TrayIcon}.  This method
     * provides a default empty implementation.
     */
    @Override
    public void mouseDragged(MouseEvent e) {
    }

    /**
     * As a convenience, this class is added as an {@code MouseMotionListener}
     * to the {@link #createTrayIcon created} {@code TrayIcon}.  This method
     * provides a default empty implementation.
     */
    @Override
    public void mouseMoved(MouseEvent e) {
    }

    //
    // Control methods
    //

    /**
     * Calls the superclass implementation and {@link #getTrayIconCreate
     * creates} this {@code SystemTrayControl}'s {@code TrayIcon} if necessary.
     */
    @Override
    public void start(Navigator navigator, Map<String, String> parameters)
	throws NavigationAbortedException, InvalidParameterException,
	NavigationFailedException {

	super.start(navigator, parameters);

	SystemTray tray;

	try {
	    tray = SystemTray.getSystemTray();
	} catch (UnsupportedOperationException e) {
	    throw new NavigationAbortedException(e);
	}

	trayIcon = getTrayIconCreate(tray);

	try {
	    tray.add(trayIcon);

	// Shouldn't happen
	} catch (AWTException e) {
	    throw new NavigationAbortedException(e);
	}

	ClientContext context = getClientContext();
	context.addConnectionListener(this);
	connectionChanged(null);
    }

    @Override
    public void stop(boolean isCancel) throws NavigationAbortedException {
	super.stop(isCancel);

	ClientContext context = getClientContext();
	context.removeConnectionListener(this);

	try {
	    SystemTray.getSystemTray().remove(trayIcon);
	} catch (UnsupportedOperationException e) {
	    getLog().log(Level.WARNING, "system tray no longer accessible!", e);
	}
    }

    //
    // SystemTrayControl methods
    //

    /**
     * Configures the just-{@code #createTrayIcon created} {@code TrayIcon} for
     * this {@code SystemTrayControl}.	This method is called automatically just
     * after {@link #createTrayIcon}.
     * <p/>
     * Most subclasses can do all configuration in {@link #createTrayIcon}.
     * Only implementors that wish to provide a common configuration for all
     * {@code TrayIcon}s created by their subclasses need to implement this
     * method.
     * <p/>
     * Subclasses that override this method should call {@code
     * super.configTrayIcon(trayIcon)} to ensure that any present or future
     * functionality in any superclass implementation is executed.
     * <p/>
     * This default implementation adds a {@link #getPopupMenu popup menu} (if
     * non-null), then adds this class as an {@code ActionListener}, {@code
     * MouseListener}, and {@code MouseMotionListener} to the {@code TrayIcon}.
     *
     * @param	    trayIcon
     *		    the newly-created {@code TrayIcon}
     */
    protected void configTrayIcon(TrayIcon trayIcon) {
	PopupMenu popup = getPopupMenu();
	if (popup != null) {
	    trayIcon.setPopupMenu(popup);
	}

	trayIcon.addActionListener(this);
	trayIcon.addMouseListener(this);
	trayIcon.addMouseMotionListener(this);
    }

    /**
     * Creates the {@code TrayIcon} for this {@code SystemTrayControl}.
     * <p/>
     * This default implementation does nothing and returns {@code null}.
     *
     * @return	    the newly-created {@code TrayIcon}
     */
    protected TrayIcon createTrayIcon(SystemTray tray) {
	return null;
    }

    /**
     * Gets, creating if necessary, a {@code PopupMenu} to display when the
     * {@link #getTrayIcon system tray icon} is clicked. This popup menu shall
     * include {@link #createLoginItem login}, {@link #createHelpItem help},
     * and {@link #createExitItem exit}, menu items.
     *
     * @return	    a {@code PopupMenu}, or {@code null} to display no popop
     */
    protected PopupMenu getPopupMenu() {
	if (popup == null) {
	    popup = new PopupMenu();

	    MenuItem loginItem = createLoginItem();
	    MenuItem helpItem = createHelpItem();
	    MenuItem exitItem = createExitItem();

	    if (loginItem != null) {
		popup.add(loginItem);
	    }
	    if (helpItem != null) {
		popup.add(helpItem);
	    }
	    if (exitItem != null) {
		popup.add(exitItem);
	    }
	}
	return popup;
    }

    /**
     * Creates a login {@code MenuItem} object for use with the
     * {@link #getTrayIcon system tray icon} popup menu.
     *
     * @return	    a {@code MenuItem}, or {@code null} to display no item
     */
    protected MenuItem createLoginItem() {
	MenuItem loginItem = new MenuItem(Finder.getString("tray.popup.login"));
	loginItem.addActionListener(
	    new ActionListener() {
		@Override
		public void actionPerformed(ActionEvent e) {
		    PanelFrameControl.promptForLogin(getClientContext());
		}
	    });
	return loginItem;
    }

    /**
     * Creates a help {@code MenuItem} object for use with the
     * {@link #getTrayIcon system tray icon} popup menu.
     *
     * @return	    a {@code MenuItem}, or {@code null} to display no item
     */
    protected MenuItem createHelpItem() {
	MenuItem helpItem = null;
	HelpSet helpSet = getPanelDescriptor().getHelpSet();
	if (helpSet != null) {
	    final URL url = getHelpURL(helpSet);
	    if (url != null) {
		helpItem = new MenuItem(Finder.getString("tray.popup.help"));
		helpItem.addActionListener(
		    new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
			    ClientContext context = getClientContext();
			    context.getHelpBroker().setCurrentURL(url);
			    context.showHelp();
			}
		    });
	    }
	}
        return helpItem;
    }

    /**
     * Creates a exit {@code MenuItem} object for use with the
     * {@link #getTrayIcon system tray icon} popup menu.
     *
     * @return	    a {@code MenuItem}, or {@code null} to display no item
     */
    protected MenuItem createExitItem() {
	MenuItem exitItem = new MenuItem(Finder.getString("tray.popup.exit"));
	exitItem.addActionListener(
	    new ActionListener() {
		@Override
		public void actionPerformed(ActionEvent e) {
		    getNavigator().asyncExec(
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
	    });
	return exitItem;
    }

    /**
     * Gets the {@code TrayIcon} for this {@code SystemTrayControl}.
     *
     * @return	    a {@code TrayIcon}, or {@code null} if this {@code
     *		    SystemTrayControl} has no {@code TrayIcon}.
     *
     * @see	    #setTrayIcon
     */
    public TrayIcon getTrayIcon() {
	return trayIcon;
    }

    /**
     * Gets the {@code TrayIcon} for this {@code SystemTrayControl}, {@link
     * #createTrayIcon creating} it and {@code #setTrayIcon setting} it first if
     * necessary.
     * <p/>
     * This method is not thread-safe; external locking may be necessary to
     * ensure that {@link #createTrayIcon} is not called by multiple threads.
     *
     * @return	    a {@code TrayIcon}, or {@code null} if this {@code
     *		    SystemTrayControl} has no {@code TrayIcon}.
     */
    public TrayIcon getTrayIconCreate(SystemTray tray) {
	TrayIcon trayIcon = getTrayIcon();
	if (trayIcon == null) {
	    trayIcon = createTrayIcon(tray);
	    if (trayIcon != null) {
		setTrayIcon(trayIcon);
		configTrayIcon(trayIcon);
	    }
	}
	return trayIcon;
    }

    /**
     * Gets the {@code TrayIcon} for this {@code SystemTrayControl}.
     *
     * @param	    trayIcon
     *		    a {@code TrayIcon}, or {@code null} if this {@code
     *		    SystemTrayControl} has no {@code TrayIcon}.
     *
     * @see	    #getTrayIcon
     */
    protected void setTrayIcon(TrayIcon trayIcon) {
	this.trayIcon = trayIcon;
    }
}
