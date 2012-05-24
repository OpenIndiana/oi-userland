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

package com.oracle.solaris.vp.panels.sysmon.client.swing;

import java.awt.*;
import java.awt.event.MouseEvent;
import java.awt.image.BufferedImage;
import java.beans.*;
import java.util.*;
import java.util.List;
import javax.swing.Icon;
import com.oracle.solaris.vp.panel.common.ConnectionEvent;
import com.oracle.solaris.vp.panel.common.control.*;
import com.oracle.solaris.vp.panel.common.model.*;
import com.oracle.solaris.vp.panel.swing.control.*;
import com.oracle.solaris.vp.panel.swing.view.Health;
import com.oracle.solaris.vp.util.misc.IconUtil;
import com.oracle.solaris.vp.util.swing.*;

public class SysMonTrayControl extends SystemTrayControl<SysMonPanelDescriptor>
{
    //
    // Instance data
    //

    private Icon icon;

    private PropertyChangeListener statusListener =
	new PropertyChangeListener() {
	    @Override
	    public void propertyChange(PropertyChangeEvent e) {
		updateIcon();
	    }
	};

    private PropertyChangeListener statusTextListener =
	new PropertyChangeListener() {
	    @Override
	    public void propertyChange(PropertyChangeEvent e) {
		updateToolTip();
	    }
	};

    //
    // Constructors
    //

    public SysMonTrayControl(String id, String name,
	SysMonPanelDescriptor descriptor) {

	super(id, name, descriptor);
    }

    //
    // ConnectionListener methods
    //

    @Override
    public void connectionChanged(ConnectionEvent event) {
	super.connectionChanged(event);
	updateToolTip();
    }

    //
    // MouseListener methods
    //

    @Override
    public void mousePressed(MouseEvent e) {
	if (!GUIUtil.isModifierKeyPressed(e) && e.getButton() == 1) {
	    Navigator navigator = getNavigator();

	    // Are any children of this Control running?
	    List<Control> stack = navigator.getPath();
	    if (stack.get(stack.size() - 1) == this) {
		// No - start child (showing window)
		Navigable path = new SimpleNavigable(
		    FrameControl.ID, null);

                navigator.goToAsync(false, this, path);
	    } else {
		// Yes - stop child (hiding window)
                navigator.goToAsync(false, this);
	    }
	}
    }

    //
    // Control methods
    //

    @Override
    public void start(Navigator navigator, Map<String, String> parameters)
	throws NavigationAbortedException, InvalidParameterException,
	NavigationFailedException {

	super.start(navigator, parameters);

	SysMonPanelDescriptor descriptor = getPanelDescriptor();

	descriptor.addPropertyChangeListener(
	    ManagedObject.PROPERTY_STATUS, statusListener);
	updateIcon();

	descriptor.addPropertyChangeListener(
	    ManagedObject.PROPERTY_STATUS_TEXT, statusTextListener);
	updateToolTip();
    }

    @Override
    public void stop(boolean isCancel) throws NavigationAbortedException {
	super.stop(isCancel);

	SysMonPanelDescriptor descriptor = getPanelDescriptor();
	descriptor.removePropertyChangeListener(statusListener);
	descriptor.removePropertyChangeListener(statusTextListener);
    }

    //
    // DefaultControl methods
    //

    @Override
    protected void ensureChildrenCreated() {
	if (children.size() == 0) {
	    addChildren(new SysMonPopupControl(getPanelDescriptor()));
	}
    }

    //
    // SystemTrayControl methods
    //

    @Override
    protected TrayIcon createTrayIcon(SystemTray tray) {
	Dimension size = tray.getTrayIconSize();

	icon = IconUtil.ensureIconHeight(
            IconUtil.getClosestIcon(getPanelDescriptor().getIcons(),
            size.height), size.height);

	Image image = GraphicsUtil.iconToImage(icon, null);

	TrayIcon trayIcon = new TrayIcon(image);
	trayIcon.setImageAutoSize(false);

	return trayIcon;
    }

    @Override
    protected MenuItem createLoginItem() {
	// Skip login menu item per bug #15776.
	return null;
    }

    //
    // Private methods
    //

    public void updateIcon() {
	if (icon != null) {
	    PanelDescriptor descriptor = getPanelDescriptor();
	    ManagedObjectStatus status = descriptor.getStatus();
	    Health health = Health.fromManagedObjectStatus(status, true);

	    Icon newIcon = icon;
	    if (health != Health.HEALTHY) {
		int badgeHeight = icon.getIconHeight() / 2;
		Icon badge = health.getIcon(badgeHeight);
		badge = IconUtil.ensureIconHeight(badge, badgeHeight);
		newIcon = IconUtil.getBadgedIcon(icon, badge, 0, 0);
	    }

	    Image image = GraphicsUtil.iconToImage(newIcon, null);
	    getTrayIcon().setImage(image);
	}
    }

    public void updateToolTip() {
	TrayIcon trayIcon = getTrayIcon();
	if (trayIcon != null) {
	    trayIcon.setToolTip(getPanelDescriptor().getStatusText());
	}
    }
}
