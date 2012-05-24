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

package com.oracle.solaris.vp.panel.common.model;

import java.beans.PropertyChangeListener;
import java.util.*;
import com.oracle.solaris.vp.util.misc.event.*;

/**
 * Simple, efficient implementation of an empty ManagedObject.
 */
public class EmptyManagedObject<T extends ManagedObject>
    implements ManagedObject<T>
{
    private String id_ = "empty";
    private String name_ = id_;
    private String desc_ = id_;
    private IntervalListeners iListeners_ = new IntervalListeners();
    private PropertyChangeListeners pListeners_ =
	new PropertyChangeListeners();

    public EmptyManagedObject() {
    }

    public EmptyManagedObject(String id, String name, String desc) {
	id_ = id;
	name_ = name;
	desc_ = desc;
    }

    @Override
    public void dispose() {
    }

    @Override
    public String getId() {
	return (id_);
    }

    @Override
    public void addPropertyChangeListener(PropertyChangeListener l) {
	pListeners_.add(l);
    }

    @Override
    public void addPropertyChangeListener(String property,
	PropertyChangeListener l) {

	pListeners_.add(property, l);
    }

    @Override
    public String getDescription() {
	return (desc_);
    }

    @Override
    public List<T> getChildren() {
	return (Collections.emptyList());
    }

    @Override
    public Object getChildrenLock() {
	return (this);
    }

    @Override
    public String getName() {
	return (name_);
    }

    @Override
    public ManagedObjectStatus getStatus() {
	return (ManagedObjectStatus.HEALTHY);
    }

    @Override
    public String getStatusText() {
	return (null);
    }

    @Override
    public boolean removePropertyChangeListener(PropertyChangeListener l) {
	return (pListeners_.remove(l));
    }

    @Override
    public boolean removePropertyChangeListener(String property,
	PropertyChangeListener l) {

	return (pListeners_.remove(property, l));
    }

    @Override
    public void addIntervalListener(IntervalListener l) {
	iListeners_.add(l);
    }

    @Override
    public boolean removeIntervalListener(IntervalListener l) {
	return (iListeners_.remove(l));
    }
}
