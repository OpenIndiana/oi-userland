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

package com.oracle.solaris.vp.panels.browser.client.swing;

import java.beans.*;
import java.util.*;
import java.util.logging.Level;
import com.oracle.solaris.rad.ObjectException;
import com.oracle.solaris.vp.panel.common.*;
import com.oracle.solaris.vp.panel.common.api.panel.*;
import com.oracle.solaris.vp.panel.common.control.*;
import com.oracle.solaris.vp.panel.common.model.*;
import com.oracle.solaris.vp.panel.swing.control.PanelFrameControl;
import com.oracle.solaris.vp.panel.swing.model.SwingPanelDescriptor;
import com.oracle.solaris.vp.util.misc.finder.Finder;

/**
 * Panel descriptor for the panel browser panel
 */
public class BrowserPanelDescriptor
    extends AbstractPanelDescriptor<PanelManagedObject>
    implements SwingPanelDescriptor<PanelManagedObject> {

    //
    // Instance data
    //

    private BrowserControl control_;
    private DefaultControl topControl;
    private Map<String, PanelManagedObject> panels_ =
	new HashMap<String, PanelManagedObject>();
    private PanelMXBeanTracker panelBeanTracker;

    private PropertyChangeListener beanListener =
	new PropertyChangeListener() {
	    @Override
	    public void propertyChange(PropertyChangeEvent event) {
		beanChanged();
		if (event.getNewValue() != null) {
		    control_.newConnection();
		}
	    }
	};

    //
    // Constructors
    //

    public BrowserPanelDescriptor(String id, ClientContext context)
	throws TrackerException {

	super(id, context);

	panelBeanTracker = new PanelMXBeanTracker(getClientContext());
	panelBeanTracker.addPropertyChangeListener(
	    MXBeanTracker.PROPERTY_BEAN, beanListener);

	beanChanged();

	control_ = new BrowserControl(this);
	topControl = new PanelFrameControl<BrowserPanelDescriptor>(this);
	topControl.addChildren(control_);
    }

    //
    // ManagedObject methods
    //

    @Override
    public String getName() {
	return (Finder.getString("browser.name"));
    }

    //
    // PanelDescriptor methods
    //

    @Override
    public Control getControl() {
	return topControl;
    }

    //
    // BrowserPanelDescriptor methods
    //

    public PanelManagedObject getPanel(String name) {
	return (panels_.get(name));
    }

    private void beanChanged() {
	PanelMXBean bean = panelBeanTracker.getBean();

	panels_.clear();
	clearChildren();

	if (bean != null) {
	    try {
		for (String name : bean.getpanelNames()) {
		    try {
			CustomPanel custom = bean.getPanel(name, null);
			panels_.put(name, new PanelManagedObject(custom));
		    } catch (ObjectException e) {
			getLog().log(Level.SEVERE,
			    "could not load panel: " + name, e);
		    }
		}
	    } catch (ObjectException e) {
		getLog().log(Level.SEVERE, "could not get panel names", e);
	    }
	}

	List<PanelManagedObject> list =
	    new ArrayList<PanelManagedObject>(panels_.values());
	Collections.sort(list);
	addChildren(list.toArray(new PanelManagedObject[0]));

	int size = getChildren().size();
	setStatusText(Finder.getString("browser.status." + size, size));
    }
}
