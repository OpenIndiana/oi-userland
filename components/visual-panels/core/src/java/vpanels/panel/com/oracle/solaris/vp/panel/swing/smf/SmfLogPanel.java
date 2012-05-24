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

package com.oracle.solaris.vp.panel.swing.smf;

import java.awt.*;
import java.beans.*;
import java.io.IOException;
import javax.management.*;
import javax.swing.*;
import com.oracle.solaris.rad.jmx.RadNotification;
import com.oracle.solaris.scf.common.ScfException;
import com.oracle.solaris.vp.panel.common.api.smf_old.*;
import com.oracle.solaris.vp.panel.common.smf.*;
import com.oracle.solaris.vp.util.misc.finder.Finder;
import com.oracle.solaris.vp.util.swing.SettingsPanel;

@SuppressWarnings({"serial"})
public class SmfLogPanel extends SettingsPanel {
    //
    // Instance data
    //

    private JTextArea field;
    private ServiceTracker tracker;

    private PropertyChangeListener serviceListener =
	new PropertyChangeListener() {
	    @Override
	    public void propertyChange(PropertyChangeEvent event) {
		updateContentOnEventThread();
	    }
	};

    private NotificationListener notifyListener =
	new NotificationListener() {
	    @Override
	    public void handleNotification(Notification n, Object h) {
		final StateChange sc =
		    ((RadNotification)n).getPayload(StateChange.class);

		updateContentOnEventThread();
	    }
	};

    //
    // Constructors
    //

    public SmfLogPanel() {
	field = new JTextArea() {
	    @Override
	    public Dimension getPreferredScrollableViewportSize() {
		FontMetrics metrics = getFontMetrics(
		    getFont().deriveFont(Font.BOLD));
		Dimension d = super.getPreferredScrollableViewportSize();

		// Set scroll pane size (20 lines heigh, 20 characters wide)
		d.height = Math.min(20 * metrics.getHeight(), d.height);
		d.width = Math.min(20 * metrics.charWidth('e'), d.width);

		return d;
	    }
	};

	field.setEditable(false);
	field.setLineWrap(false);
	field.setBackground(Color.white);

	setContent(new JScrollPane(field), false, false);
    }

    //
    // SmfLogPanel methods
    //

    public void init(ServiceTracker tracker)
	throws InstanceNotFoundException, IOException {

	if (this.tracker != tracker) {
	    if (this.tracker != null) {
		this.tracker.removePropertyChangeListener(
		    ServiceTracker.PROPERTY_SERVICE, serviceListener);
                this.tracker.removeNotificationListener(notifyListener,
		    SmfUtil.NOTIFY_FILTER_STATE_CHANGE, null);
	    }

	    this.tracker = tracker;

	    if (tracker != null) {
		tracker.addPropertyChangeListener(
		    ServiceTracker.PROPERTY_SERVICE, serviceListener);
                tracker.addNotificationListener(notifyListener,
		    SmfUtil.NOTIFY_FILTER_STATE_CHANGE, null);
	    }

	    updateContentOnEventThread();
	}
    }

    //
    // Private methods
    //

    private void updateContent() {
	String content = null;
	ServiceMXBean service = tracker == null ? null : tracker.getService();

	if (tracker != null) {
	    try {
		// Limit to 1mb to not overwhelm network/memory
		LogInfo info = service.getLogInfo(1 << 20);
		byte[] bytes = info.getContents();
		content = new String(bytes);
		String resource = "service.log.contents";
		if (bytes.length < info.getSize()) {
		    resource += ".truncated";
		}
		content = Finder.getString(resource, info.getName(), content);
	    } catch (ScfException e) {
		content = Finder.getString("service.log.error.jmx");
	    }
	}

	field.setText(content);
        field.scrollRectToVisible(new Rectangle(0,
	    field.getPreferredSize().height));
    }

    private void updateContentOnEventThread() {
	EventQueue.invokeLater(
	    new Runnable() {
		@Override
		public void run() {
		    updateContent();
		}
	    });
    }
}
