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

import java.awt.EventQueue;
import java.awt.event.*;
import java.beans.*;
import java.util.*;
import java.util.logging.*;
import javax.swing.*;
import javax.swing.border.Border;
import javax.swing.event.*;
import com.oracle.solaris.vp.panel.common.*;
import com.oracle.solaris.vp.panel.common.action.*;
import com.oracle.solaris.vp.panel.common.control.*;
import com.oracle.solaris.vp.panel.common.model.*;
import com.oracle.solaris.vp.panel.swing.view.*;
import com.oracle.solaris.vp.util.misc.*;
import com.oracle.solaris.vp.util.misc.finder.Finder;
import com.oracle.solaris.vp.util.swing.*;

@SuppressWarnings({"serial"})
public class PanelFrameControl<P extends PanelDescriptor>
    extends FrameControl<P, PanelFrame> implements HasIcons {

    //
    // Inner classes
    //

    private static class RequiredRoleLoginProperty
	extends LoginProperty<String> {

	//
	// Constructors
	//

	public RequiredRoleLoginProperty(String value, boolean editable) {
	    super(value, editable);
	}

	@Override
	public void validate(LoginRequest request, String... roles)
	    throws LoginPropertyException {

	    // Ensure at least one role is available
	    if (roles.length == 0) {
		String message = Finder.getString("login.err.role.none",
		    request.getHost().getValue(), request.getUser().getValue());

		DialogMessage dMessage = new DialogMessage(message,
		    JOptionPane.ERROR_MESSAGE);

		throw new LoginPropertyException(dMessage, true);
	    }
	}
    }

    //
    // Instance data
    //

    // Login popup menu.
    private JPopupMenu popupMenu;

    // Clear popup menu item.
    private JMenuItem clearMenuItem;

    // Login menu item count.
    private int loginItemCount = 0;

    // Login history size.
    private int loginSize = 6;

    private String title;

    private ConnectionListener connListener =
	new ConnectionListener() {
	    @Override
	    public void connectionChanged(ConnectionEvent event) {
		PanelFrameControl.this.connectionChanged();
		privilegedChanged();
		titleChanged();
	    }

	    @Override
	    public void connectionFailed(ConnectionEvent event) {
                // There's nothing particularly helpful we can do here except
                // wait for the repaired connection in connectionChanged
	    }
	};

    private PropertyChangeListener healthListener =
	new PropertyChangeListener() {
	    @Override
	    public void propertyChange(PropertyChangeEvent e) {
		healthChanged();
	    }
	};

    private PropertyChangeListener statusListener =
	new PropertyChangeListener() {
	    @Override
	    public void propertyChange(PropertyChangeEvent e) {
		statusChanged();
	    }
	};

    // Listener to recreate popup menu on login changes.
    private ChangeListener loginListener = new ChangeListener() {
	    @Override
	    public void stateChanged(ChangeEvent e) {
		createLoginItems();
	    }
	};

    // Listener to display popup menu on mouse navigation.
    private ActionListener loginActionListener =
	new ActionListener() {
	    @Override
	    public void actionPerformed(ActionEvent e) {
		if (!popupMenu.isVisible()) {
		    JButton button = getComponent().getAuthPanel().getButton();
		    popupMenu.show(button, 0, button.getHeight());
		} else {
		    popupMenu.setVisible(false);
		}
	    }
	};

    //
    // Constructors
    //

    public PanelFrameControl(String id, String name, P descriptor) {
	super(id, name, descriptor);
	popupMenu = createPopupMenu();
    }

    public PanelFrameControl(P descriptor) {
	this(descriptor.getId(), descriptor.getName(), descriptor);
    }

    //
    // HasIcons methods
    //

    @Override
    public List<? extends Icon> getIcons() {
	P descriptor = getPanelDescriptor();
	if (descriptor instanceof HasIcons) {
	    return ((HasIcons)descriptor).getIcons();
	}
	return null;
    }

    //
    // Control methods
    //

    @Override
    public void start(Navigator navigator, Map<String, String> parameters)
	throws NavigationAbortedException, InvalidParameterException,
	NavigationFailedException {

	super.start(navigator, parameters);

	ClientContext context = getClientContext();
	context.addConnectionListener(connListener);
	connectionChanged();

	PanelDescriptor descriptor = getPanelDescriptor();

	descriptor.addPropertyChangeListener(ManagedObject.PROPERTY_ENABLED,
	    healthListener);
	descriptor.addPropertyChangeListener(ManagedObject.PROPERTY_STATUS,
	    healthListener);
	healthChanged();

	descriptor.addPropertyChangeListener(
	    ManagedObject.PROPERTY_STATUS_TEXT, statusListener);
	statusChanged();

	JButton button = getComponent().getAuthPanel().getButton();
	button.addActionListener(loginActionListener);

	context.getLoginHistory().addChangeListener(loginListener);
	createLoginItems();
    }

    @Override
    public void stop(boolean isCancel) throws NavigationAbortedException {
	super.stop(isCancel);

	ClientContext context = getClientContext();
	context.removeConnectionListener(connListener);
	context.getLoginHistory().removeChangeListener(loginListener);

	PanelDescriptor descriptor = getPanelDescriptor();
	descriptor.removePropertyChangeListener(healthListener);
	descriptor.removePropertyChangeListener(statusListener);

	JButton button = getComponent().getAuthPanel().getButton();
	button.removeActionListener(loginActionListener);
    }

    //
    // SwingControl methods
    //

    @Override
    protected void configComponent(PanelFrame comp) {
	super.configComponent(comp);
	connectionChanged();
	titleChanged();
	privilegedChanged();
	healthChanged();
	statusChanged();
    }

    @Override
    protected PanelFrame createComponent() {
        PanelFrame frame = new PanelFrame(getClientContext().getRuntimeHints(),
	    getNavigator());

	ReplacingStackPanel mainPanel = frame.getMainPanel();
	mainPanel.setBorder(getDefaultBorder());

	setComponentStack(mainPanel);

	return frame;
    }

    //
    // WindowControl methods
    //

    @Override
    protected String getWindowTitle() {
	return title;
    }

    @Override
    protected void setWindowTitle(String title) {
	this.title = title;
	titleChanged();
    }

    @Override
    protected void windowClosing() {
	getNavigator().asyncExec(
	    new Runnable() {
		@Override
		public void run() {
		    try {
			getClientContext().closeInstance(false);
		    } catch (ActionAbortedException ignore) {
		    }
		}
	    });
    }

    //
    // PanelFrameControl methods
    //

    /**
     * Returns a {@code Border} to use on the {@link PanelFrame#getMainPanel
     * main panel} of the {@link PanelFrame}, or {@code null} to use no {@code
     * Border}.
     * </p>
     * This default implementation returns {@link GUIUtil#getEmptyBorder}.
     */
    protected Border getDefaultBorder() {
	return GUIUtil.getEmptyBorder();
    }

    /**
     * Gets a {@code PopupMenu} to display when the
     * login button is clicked.
     *
     * @return A {@code PopupMenu} menu.
     */
    protected JPopupMenu getPopupMenu() {
	return popupMenu;
    }

    /**
     * Creates a {@code PopupMenu} to display when the login button is clicked.
     * This popup menu does not include {@link #createLoginItem} objects.
     *
     * @return A {@code PopupMenu} menu.
     */
    protected JPopupMenu createPopupMenu() {
	JPopupMenu menu = new JPopupMenu();

	JMenuItem roleItem = createRoleItem();
	menu.add(roleItem);

	JMenuItem userItem = createUserItem();
	menu.add(userItem);

	JMenuItem adminItem = createAdminItem();
	menu.addSeparator();
	menu.add(adminItem);

	clearMenuItem = createClearItem();
	menu.addSeparator();
	menu.add(clearMenuItem);

	return menu;
    }

    /**
     * Creates an admin {@code MenuItem} object for use with the
     * {@link #getPopupMenu} popup menu.
     *
     * @return A {@code MenuItem} item.
     */
    protected JMenuItem createAdminItem() {
	JMenuItem loginItem = new JMenuItem(Finder.getString(
	    "login.popup.admin"));
	loginItem.addActionListener(
	    new ActionListener() {
		@Override
		public void actionPerformed(ActionEvent e) {
		    ClientContext context = getClientContext();
		    promptForLogin(context,
			createHostRequest(context.getConnectionInfo()));
		}
	    });
	return loginItem;
    }

    /**
     * Creates a clear {@code MenuItem} object for use with the
     * {@link #getPopupMenu} popup menu.
     *
     * @return A {@code MenuItem} item.
     */
    protected JMenuItem createClearItem() {
	JMenuItem item = new JMenuItem(Finder.getString("login.popup.clear"));
	item.addActionListener(
	    new ActionListener() {
		@Override
		public void actionPerformed(ActionEvent e) {
		    EventQueue.invokeLater(
			new Runnable() {
			    @Override
			    public void run() {
				getClientContext().getLoginHistory().
				    clearLogins();
			    }
			});
		}
	    });
	return item;
    }

    /**
     * Creates {@link #createLoginItem} objects for the {@link #getPopupMenu}
     * popup menu.
     */
    protected void createLoginItems() {
	ClientContext context = getClientContext();
	List<LoginInfo> logins = context.getLoginHistory().getLogins(loginSize);

	// Remove existing login menu items.
	while (loginItemCount > 0) {
	    popupMenu.remove(0);
	    loginItemCount--;
	}

	// Get current login info.
	ConnectionInfo info = getClientContext().getConnectionInfo();

	// Add logins.
	for (LoginInfo login : logins) {
	    // Skip current login.
	    if (info.matches(login)) {
		continue;
	    }

	    JMenuItem loginItem = createLoginItem(login);
	    popupMenu.insert(loginItem, loginItemCount++);
	}

	// Add separator and enable clear history menu item.
	if (loginItemCount > 0) {
	    popupMenu.insert(new JPopupMenu.Separator(), loginItemCount++);
	    clearMenuItem.setEnabled(true);
	} else {
	    clearMenuItem.setEnabled(false);
	}
    }

    /**
     * Creates a login {@code MenuItem} object for use with the
     * {@link #getPopupMenu} popup menu.
     *
     * @return A {@code MenuItem} item.
     */
    protected JMenuItem createLoginItem(final LoginInfo info) {
	JMenuItem loginItem = new JMenuItem(AuthPanel.toString(info, false));
	loginItem.addActionListener(
	    new ActionListener() {
		@Override
		public void actionPerformed(ActionEvent e) {
		    promptForLogin(getClientContext(),
			createStaticRequest(info));
		}
	    });
	return loginItem;
    }

    /**
     * Creates a role {@code MenuItem} object for use with the
     * {@link #getPopupMenu} popup menu.
     *
     * @return A {@code MenuItem} item.
     */
    protected JMenuItem createRoleItem() {
	JMenuItem item = new JMenuItem(Finder.getString("login.popup.role"));
	item.addActionListener(
	    new ActionListener() {
		@Override
		public void actionPerformed(ActionEvent e) {
		    ClientContext context = getClientContext();
		    promptForLogin(context,
			createRoleRequest(context.getConnectionInfo()));
		}
	    });
	return item;
    }

    /**
     * Creates a user {@code MenuItem} object for use with the
     * {@link #getPopupMenu} popup menu.
     *
     * @return A {@code MenuItem} item.
     */
    protected JMenuItem createUserItem() {
	JMenuItem item = new JMenuItem(Finder.getString("login.popup.user"));
	item.addActionListener(
	    new ActionListener() {
		@Override
		public void actionPerformed(ActionEvent e) {
		    ClientContext context = getClientContext();
		    promptForLogin(context,
			createUserRequest(context.getConnectionInfo()));
		}
	    });
	return item;
    }

    //
    // Private methods
    //

    private void connectionChanged() {
	getComponent().getAuthPanel().setConnectionInfo(
	    getClientContext().getConnectionInfo());
    }

    private void privilegedChanged() {
	getComponent().getAuthPanel().setPrivileged(
	    getPanelDescriptor().getHasFullPrivileges());
    }

    private void healthChanged() {
	boolean enabled = true;
	PanelDescriptor descriptor = getPanelDescriptor();
	ManagedObjectStatus status = descriptor.getStatus();
	if (descriptor instanceof Enableable) {
	    enabled = ((Enableable)descriptor).isEnabled();
	}

	Health health = Health.fromManagedObjectStatus(status, enabled);
	getComponent().setHealth(health);
    }

    private void statusChanged() {
	getComponent().setStatusText(getPanelDescriptor().getStatusText());
    }

    private void titleChanged() {
	String login = null;
	String resource = "window.title.defaultlogin";
	ConnectionInfo info = getClientContext().getConnectionInfo();

	// If not logged in with default host/user/role...
        if (info != null && !info.matches("localhost",
	    System.getProperty("user.name"), null, null, null, null)) {

	    login = AuthPanel.toString(info, true);
	    resource = "window.title.nondefaultlogin";
	}

	String frameTitle = Finder.getString(resource, title, login);
	getComponent().setTitle(frameTitle);
    }

    //
    // Static methods
    //

    private static LoginRequest createHostRequest(LoginInfo info) {
	boolean isZone = info.getZone() != null;

	LoginProperty<String> host =
	    new LoginProperty<String>(info.getHost(), true);
	LoginProperty<String> user =
	    new LoginProperty<String>(info.getUser(), true);
	LoginProperty<String> role =
	    new LoginProperty<String>(info.getRole(), true);
	LoginProperty<Boolean> zonePrompt =
	    new LoginProperty<Boolean>(isZone, true);
	LoginProperty<String> zone =
	    new LoginProperty<String>(info.getZone(), true);
	LoginProperty<String> zoneUser =
	    new LoginProperty<String>(info.getZoneUser(), true);
	LoginProperty<String> zoneRole =
	    new LoginProperty<String>(info.getZoneRole(), true);

        return new LoginRequest(host, user, role, zonePrompt, zone, zoneUser,
	    zoneRole);
    }

    private static LoginRequest createRoleRequest(LoginInfo info) {
	boolean isZone = info.getZone() != null;

	LoginProperty<String> host =
	    new LoginProperty<String>(info.getHost(), false);
	LoginProperty<String> user =
	    new LoginProperty<String>(info.getUser(), false);
	LoginProperty<String> role = isZone ?
	    new LoginProperty<String>(info.getRole(), false) :
	    new RequiredRoleLoginProperty(info.getRole(), true);
	LoginProperty<Boolean> zonePrompt =
	    new LoginProperty<Boolean>(isZone, false);
	LoginProperty<String> zone =
	    new LoginProperty<String>(info.getZone(), false);
	LoginProperty<String> zoneUser =
	    new LoginProperty<String>(info.getZoneUser(), false);
	LoginProperty<String> zoneRole = isZone ?
	    new RequiredRoleLoginProperty(info.getZoneRole(), true) :
	    new LoginProperty<String>(info.getZoneRole(), false);

	return new LoginRequest(host, user, role, zonePrompt, zone, zoneUser,
	    zoneRole);
    }

    private static LoginRequest createStaticRequest(LoginInfo info) {
	boolean isZone = info.getZone() != null;

	LoginProperty<String> host =
	    new LoginProperty<String>(info.getHost(), false);
	LoginProperty<String> user =
	    new LoginProperty<String>(info.getUser(), false);
	LoginProperty<String> role =
	    new LoginProperty<String>(info.getRole(), false);
	LoginProperty<Boolean> zonePrompt =
	    new LoginProperty<Boolean>(isZone, false);
	LoginProperty<String> zone =
	    new LoginProperty<String>(info.getZone(), false);
	LoginProperty<String> zoneUser =
	    new LoginProperty<String>(info.getZoneUser(), false);
	LoginProperty<String> zoneRole =
	    new LoginProperty<String>(info.getZoneRole(), false);

	host.setEditableOnError(true);
	user.setEditableOnError(true);
	role.setEditableOnError(true);
	zonePrompt.setEditableOnError(true);
	zone.setEditableOnError(true);
	zoneUser.setEditableOnError(true);
	zoneRole.setEditableOnError(true);

        return new LoginRequest(host, user, role, zonePrompt, zone, zoneUser,
	    zoneRole);
    }

    private static LoginRequest createUserRequest(LoginInfo info) {
	boolean isZone = info.getZone() != null;

	LoginProperty<String> host =
	    new LoginProperty<String>(info.getHost(), false);
	LoginProperty<String> user =
	    new LoginProperty<String>(info.getUser(), !isZone);
	LoginProperty<String> role =
	    new LoginProperty<String>(info.getRole(), !isZone);
	LoginProperty<Boolean> zonePrompt =
	    new LoginProperty<Boolean>(isZone, false);
	LoginProperty<String> zone =
	    new LoginProperty<String>(info.getZone(), false);
	LoginProperty<String> zoneUser =
	    new LoginProperty<String>(info.getZoneUser(), isZone);
	LoginProperty<String> zoneRole =
	    new LoginProperty<String>(info.getZoneRole(), isZone);

        return new LoginRequest(host, user, role, zonePrompt, zone, zoneUser,
	    zoneRole);
    }

    // Displays login panel per login request properties.
    private static void promptForLogin(final ClientContext context,
	    final LoginRequest request) {
	context.getNavigator().asyncExec(
	    new Runnable() {
		@Override
		public void run() {
		    try {
			ClientContext newContext = context.login(request,
			    false);

			// New ClientContext?
			if (newContext != context) {
			    // Duplicate path
			    List<Control> path =
				context.getNavigator().getPath();
			    Navigable[] array =
				path.toArray(new Navigable[path.size()]);
			    newContext.getNavigator().goToAsync(true, null,
				array);
			}
		    } catch (ActionAbortedException ignore) {
		    } catch (ActionFailedException ignore) {
		    } catch (Throwable e) {
			Logger.getLogger(getClass().getPackage().getName()).log(
			    Level.WARNING, "unable to log in as " +
				AuthPanel.toString(request, false), e);
		    }
		}
	    });
    }

    /**
     * Asynchronously (on the given {@link ClientContext}'s {@link Navigator}'s
     * navigation thread) prompts the user to log in, then navigates any
     * resulting new {@link ClientContext} to the current path of given {@link
     * ClientContext}, ignoring any errors.
     */
    public static void promptForLogin(ClientContext context) {
	promptForLogin(context, createHostRequest(context.getConnectionInfo()));
    }
}
