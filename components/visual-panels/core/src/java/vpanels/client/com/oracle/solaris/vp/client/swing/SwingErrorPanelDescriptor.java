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

import java.awt.Component;
import java.io.*;
import java.util.*;
import javax.swing.*;
import com.oracle.solaris.vp.client.common.ErrorPanelDescriptor;
import com.oracle.solaris.vp.panel.common.ClientContext;
import com.oracle.solaris.vp.panel.common.api.panel.CustomPanel;
import com.oracle.solaris.vp.panel.common.control.*;
import com.oracle.solaris.vp.panel.common.model.*;
import com.oracle.solaris.vp.panel.swing.control.*;
import com.oracle.solaris.vp.panel.swing.model.SwingPanelDescriptor;
import com.oracle.solaris.vp.util.misc.finder.Finder;

/**
 * Implementation of {@code ErrorPanelDescriptor} for the Swing client.
 * Displays a tab containing the provided throwable's stack trace for
 * each custom panel that failed.
 */
@SuppressWarnings({"serial"})
public class SwingErrorPanelDescriptor
    extends AbstractPanelDescriptor<ManagedObject>
    implements SwingPanelDescriptor<ManagedObject>,
    ErrorPanelDescriptor<ManagedObject> {

    //
    // Inner classes
    //

    static class ErrorTab extends SwingControl<PanelDescriptor, JScrollPane> {
	//
	// Instance data
	//

	private CustomPanel panel;
	private Throwable t;

	//
	// Constructors
	//

	public ErrorTab(CustomPanel panel, Throwable t, ClientContext context) {
	    super(panel.getName(), Finder.getString("errorpanel.tab.name",
		panel.getName()), context);

	    this.panel = panel;
	    this.t = t;
	}

	//
	// SwingControl methods
	//

	@Override
	public JScrollPane createComponent() {
	    JTextArea area = new JTextArea();
	    area.setEditable(false);
	    area.setColumns(80);

	    String header = Finder.getString("errorpanel.header",
		panel.getName());

	    StringWriter sw = new StringWriter();
	    PrintWriter pw = new PrintWriter(sw);
	    t.printStackTrace(pw);
	    pw.flush();

	    area.setText(header);
	    area.append("\n\n");
	    area.append(sw.toString());

	    return new JScrollPane(area);
	}
    }

    //
    // Instance data
    //

    private DefaultControl control;
    private List<Control> tabs = new LinkedList<Control>();

    //
    // Constructors
    //

    public SwingErrorPanelDescriptor(String name, ClientContext context) {
	super(name, context);
    }

    //
    // ManagedObject methods
    //

    @Override
    public String getName() {
	return Finder.getString("errorpanel.name", getId());
    }

    @Override
    public String getStatusText() {
	int number = tabs.size();
	return Finder.getString("errorpanel.status." + number, number);
    }

    @Override
    public ManagedObjectStatus getStatus() {
	return ManagedObjectStatus.ERROR;
    }

    //
    // PanelDescriptor methods
    //

    /**
     * Returns a {@link TabbedControl}.
     */
    @Override
    public Control getControl() {
	if (control == null) {
	    String id = "tabs";
	    String name = Finder.getString("errorpanel.tabs.name");
	    TabbedControl tControl =
		new TabbedControl<SwingErrorPanelDescriptor>(id, name, this);
	    tControl.addChildren(tabs.toArray(new ErrorTab[tabs.size()]));

	    control = new PanelFrameControl<SwingErrorPanelDescriptor>(this);
	    control.addChildren(tControl);
	}
	return control;
    }

    //
    // ErrorPanelDescriptor methods
    //

    @Override
    public void addError(CustomPanel panel, Throwable t) {
	tabs.add(new ErrorTab(panel, t, getClientContext()));
    }

    @Override
    public int getErrorCount() {
	return tabs.size();
    }
}
