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

package com.oracle.solaris.vp.panels.apache.client.swing;

import java.util.*;
import javax.swing.Icon;
import com.oracle.solaris.scf.common.ScfException;
import com.oracle.solaris.vp.panel.common.model.*;
import com.oracle.solaris.vp.panel.common.smf.*;
import com.oracle.solaris.vp.panel.common.view.PanelIconUtil;
import com.oracle.solaris.vp.util.misc.*;
import com.oracle.solaris.vp.util.misc.finder.Finder;
import com.oracle.solaris.vp.util.misc.property.*;
import com.oracle.solaris.vp.util.swing.HasIcon;

@SuppressWarnings({"serial"})
public class MimeTypes extends AbstractManagedObject<MimeType>
    implements HasIcon {

    //
    // Static data
    //

    public static final String ID = "mimetypes";
    public static final String NAME = Finder.getString("mimetypes.title");
    public static final String PROPERTY_ADDED = "added MIME types";
    public static final String PROPERTY_REMOVED = "removed MIME types";

    //
    // Instance data
    //

    private ApacheInfo info;
    private SimpleHasId tmpHasId = new SimpleHasId();

    private BasicMutableProperty<Integer> addedProperty =
	new IntegerProperty(PROPERTY_ADDED);

    private BasicMutableProperty<Integer> removedProperty =
	new IntegerProperty(PROPERTY_REMOVED);

    private List<MimeType> removed = new ArrayList<MimeType>();

    //
    // Constructors
    //

    public MimeTypes(ApacheInfo info) {
	super(ID);
	this.info = info;

	addedProperty.update(0, true);
	addProperties(addedProperty);

	removedProperty.update(0, true);
	addProperties(removedProperty);

	setComparator(SimpleHasId.COMPARATOR);
    }

    //
    // HasIcon methods
    //

    @Override
    public Icon getIcon(int height) {
	return PanelIconUtil.getClosestMimeIcon(null, null, height);
    }

    //
    // ManagedObject methods
    //

    @Override
    public String getName() {
	return NAME;
    }

    //
    // AbstractManagedObject methods
    //

    @Override
    public void addChildren(MimeType... toAdd) {
	super.addChildren(toAdd);

	ChangeableAggregator aggregator = getChangeableAggregator();
	for (MimeType mimeType : toAdd) {
	    if (!mimeType.isInRepo()) {
		addedProperty.setValue(addedProperty.getValue() + 1);
	    }
	    aggregator.addChangeables(mimeType.getChangeableAggregator());
	}
    }

    @Override
    public void removeChildren(MimeType... toRemove) {
	super.removeChildren(toRemove);

	ChangeableAggregator aggregator = getChangeableAggregator();
	for (MimeType mimeType : toRemove) {
	    if (!mimeType.isInRepo()) {
		addedProperty.setValue(addedProperty.getValue() - 1);
	    }
	    aggregator.removeChangeable(mimeType.getChangeableAggregator());
	}
    }

    //
    // MimeTypes methods
    //

    public ApacheInfo getApacheInfo() {
	return info;
    }

    public MimeType getMimeType(String id) {
	synchronized (children) {
	    tmpHasId.setId(id);
	    int index = Collections.binarySearch(
		getChildren(), tmpHasId, SimpleHasId.COMPARATOR);

	    if (index >= 0) {
		return children.get(index);
	    }

	    return null;
	}
    }

    public MimeType getMimeType(String type, String subtype) {
	String id = MimeType.toId(type, subtype);
	return getMimeType(id);
    }

    public void refresh(boolean force) throws ScfException {
	ServiceMXBean service = info.getPanelDescriptor().getService();
	String group = info.getPropertyGroupName();

	// Build list of names of MIME type properties
	List<String> properties = new ArrayList<String>();
	for (String property : service.getPropertyNames(group)) {
	    if (property.startsWith(MimeType.SMF_PROPERTY_PREFIX)) {
		properties.add(property);
	    }
	}
	Collections.sort(properties);

	// Remove names of properties that are pending removal on client
	for (Iterator<MimeType> i = removed.iterator(); i.hasNext();) {
	    MimeType mimeType = i.next();
	    String property = mimeType.getPropertyName();
	    if (properties.remove(property)) {
		// Pending removal on client, still exists on server
	    } else {
		// Pending removal on client, but already removed on server
		i.remove();
		int n = removed.size();
		assert n == removedProperty.getValue() - 1;
		removedProperty.setValue(n);
	    }
	}

	// Remove names of properties already created on the client
	List<MimeType> children = new ArrayList<MimeType>(getChildren());
	for (MimeType mimeType : children) {
	    if (mimeType.isInRepo()) {
		String property = mimeType.getPropertyName();
		if (properties.remove(property)) {
		    // Exists on server, already exists on client
		    mimeType.refresh(force);
		} else {
		    // Deleted on server, now must be deleted on client
		    removeChildren(mimeType);
		}
	    }
	}

	// The list now contains only properties that have been created on the
	// server but don't yet exist on the client
	for (String property : properties) {
	    MimeType mimeType = new MimeType(this, property);
	    addChildren(mimeType);
	}
    }

    public void scheduleRemove(MimeType... mimeTypes) {
	for (MimeType mimeType : mimeTypes) {
	    if (getChildren().contains(mimeType)) {
		removeChildren(mimeType);

		if (mimeType.isInRepo()) {
		    removed.add(mimeType);
		    int n = removed.size();
		    assert n == removedProperty.getValue() + 1;
		    removedProperty.setValue(n);
		}
	    }
	}
    }

    public void saveToRepo() throws ScfException {
	ApacheUtil.saveToRepo(info.getService(),
	    new ScfRunnable() {
		@Override
		public void run() throws ScfException {
		    for (MimeType mimeType : getChildren()) {
			mimeType.saveToRepo();
		    }
		    addedProperty.setValue(0);

		    for (Iterator<MimeType> i = removed.iterator();
			i.hasNext();) {

			MimeType mimeType = i.next();
			mimeType.removeFromRepo();
			i.remove();
			int n = removed.size();
			assert n == removedProperty.getValue() - 1;
			removedProperty.setValue(n);
		    }

		    for (MutableProperty<?> property : getProperties()) {
			if (property.isChanged()) {
			    if (property instanceof SmfMutableProperty) {
				((SmfMutableProperty)property).saveToRepo();
			    } else {
				property.save();
			    }
			}
		    }
		}
	    });
    }
}
