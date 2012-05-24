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

package com.oracle.solaris.vp.panel.common.smf;

import java.util.*;
import javax.swing.*;
import com.oracle.solaris.scf.common.ScfException;
import com.oracle.solaris.vp.panel.common.api.smf_old.*;
import com.oracle.solaris.vp.panel.common.model.AbstractManagedObject;
import com.oracle.solaris.vp.util.misc.*;
import com.oracle.solaris.vp.util.misc.finder.Finder;
import com.oracle.solaris.vp.util.swing.HasIcon;

public class PropertyGroupManagedObject
    extends AbstractManagedObject<PropertyManagedObject> implements HasIcon {

    //
    // Static data
    //

    protected static final List<ImageIcon> icons = Finder.getIcons(
	"images/propertygroup-16.png",
	"images/propertygroup-22.png",
	"images/propertygroup-24.png",
	"images/propertygroup-32.png",
	"images/propertygroup-48.png",
	"images/propertygroup-256.png");

    public static final String ID = "propertygroup";

    public static final Comparator<Object> COMPARATOR =
	new Comparator<Object>() {
	    @Override
	    public int compare(Object o1, Object o2) {
		if (o1 == null) {
		    return o2 == null ? 0 : -1;
		}

		if (o2 == null) {
		    return 1;
		}

		SmfMutableProperty prop1 =
		    o1 instanceof PropertyManagedObject ?
                    ((PropertyManagedObject)o1).getProperty() :
		    o1 instanceof SmfMutableProperty ?
                    (SmfMutableProperty)o1 : null;

		SmfMutableProperty prop2 =
		    o2 instanceof PropertyManagedObject ?
                    ((PropertyManagedObject)o2).getProperty() :
		    o2 instanceof SmfMutableProperty ?
                    (SmfMutableProperty)o2 : null;

                int cmpVal = ObjectUtil.compare(prop1.getPropertyName(),
		    prop2.getPropertyName());

		if (cmpVal != 0) {
		    return cmpVal;
		}

		Class<?> class1 = prop1.getClass();
		Class<?> class2 = prop2.getClass();

		if (!class1.equals(class2)) {
		    if (class1.isAssignableFrom(class2)) {
			return -1;
		    }
		    if (class2.isAssignableFrom(class1)) {
			return 1;
		    }
		}

		return 0;
	    }
	};

    //
    // Instance data
    //

    private PropertyGroupsManagedObject parent;
    private PropertyGroup group;

    //
    // Constructors
    //

    PropertyGroupManagedObject(PropertyGroupsManagedObject parent,
	PropertyGroup group) throws ScfException {

	super(group.getName());

	this.parent = parent;
	this.group = group;

	setComparator(COMPARATOR);
	refresh(true);
    }

    //
    // HasIcon methods
    //

    @Override
    public Icon getIcon(int height) {
	return IconUtil.getClosestIcon(icons, height);
    }

    //
    // PropertyGroupManagedObject methods
    //

    public PropertyManagedObject getChild(SmfMutableProperty property) {
	synchronized (children) {
	    int index = Collections.binarySearch(
		getChildren(), property, COMPARATOR);

	    if (index >= 0) {
		return children.get(index);
	    }

	    return null;
	}
    }

    public PropertyGroup getPropertyGroup() {
	return group;
    }

    public void refresh(boolean force) throws ScfException {
	ServiceTracker tracker = parent.getServiceTracker();
	ServiceMXBean service = tracker.getService();
	if (service == null) {
	    return;
	}

	String pgName = group.getName();

	synchronized (children) {
	    List<PropertyManagedObject> toRemove =
		new LinkedList<PropertyManagedObject>(children);

	    for (String pName : service.getPropertyNames(pgName)) {
		String locale = Locale.getDefault().getLanguage();
		Template templ = getPropertyTemplate(service, pgName, pName,
		    locale);

		if (templ != null &&
		    templ.getVisibility() == PropertyVisibility.HIDDEN) {
		    continue;
		}

		SmfPropertyInfo info = new SimpleSmfPropertyInfo(tracker,
		    pgName, null);

		BasicSmfMutableProperty property = null;

		if (templ != null) {
		    List<String> allowed = templ.getAllowed();
		    if (allowed != null && allowed.size() > 0) {
			property = new ChoiceSmfProperty(pName, info, allowed);
		    }
		}

		PropertyType type = service.getPropertyType(pgName, pName);
		if (property == null) {
		    switch (type) {
		    case BOOLEAN:
			property = new BooleanSmfProperty(pName, info);
			break;

		    case COUNT:
		    case INTEGER:
			property = new IntegerSmfProperty(pName, info);
			break;

		    default:
			property = new StringSmfProperty(pName, info);
		    }
		}
		property.setType(type);

		PropertyManagedObject child = getChild(property);
		if (child == null) {
		    child = new PropertyManagedObject(this, property);
		    addChildren(child);
		} else {
		    toRemove.remove(child);
		    child.refresh(force);
		}
	    }

	    // Minimize IntervalEvents by removing en masse
	    if (!toRemove.isEmpty()) {
		removeChildren(toRemove.toArray(
		    new PropertyManagedObject[toRemove.size()]));
	    }
	}
    }

    //
    // Static methods
    //

    private static Template getPropertyTemplate(ServiceMXBean service,
	String pgName, String pName, String locale) throws ScfException {

	Template templ = null;
	try {
	    templ = service.getPropertyTemplate(pgName, pName, locale);
	} catch (ScfException e) {
	    if (e.getError() != SmfErrorCode.NOT_FOUND) {
		throw e;
	    }
	}
	return templ;
    }
}
