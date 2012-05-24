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

import java.util.List;
import javax.swing.*;
import com.oracle.solaris.scf.common.ScfException;
import com.oracle.solaris.vp.panel.common.model.*;
import com.oracle.solaris.vp.panel.common.smf.*;
import com.oracle.solaris.vp.util.misc.IconUtil;
import com.oracle.solaris.vp.util.misc.finder.Finder;
import com.oracle.solaris.vp.util.misc.property.*;
import com.oracle.solaris.vp.util.swing.HasIcon;

@SuppressWarnings({"serial"})
public class Module extends AbstractManagedObject<ManagedObject>
    implements HasIcon, Cloneable, SmfPropertyInfo {

    //
    // Static data
    //

    public static final String PROPERTY_FILE = "file";

    public static final String SMF_PROPERTY_PREFIX = "module-";

    protected static final List<ImageIcon> icons = Finder.getIcons(
	"images/modules-32.png",
	"images/modules-48.png",
	"images/modules-96.png");

    //
    // Instance data
    //

    private Modules parent;
    private String propertyName;

    private MutableProperty<String> nameProperty =
	new BasicMutableProperty<String>(PROPERTY_NAME);

    private MutableProperty<String> fileProperty =
	new BasicMutableProperty<String>(PROPERTY_FILE);

    // This is the property that does the actual work of persisting this
    // Module's data to the SMF repository
    private BasicSmfMutableProperty<String> smfProperty =
	new StringSmfProperty(null, this);

    //
    // Constructors
    //

    public Module(Modules parent) {
	this.parent = parent;

	nameProperty.setValue("");
	addProperties(nameProperty);

	fileProperty.setValue("");
	addProperties(fileProperty);

	// Synchronize the properties holding this Module's data with the
	// property responsible for persisting it to the SMF repository
	new ModulePropertySynchronizer(smfProperty, this, false);
    }

    public Module(Modules parent, String propertyName) throws ScfException {
	this(parent);
	this.propertyName = propertyName;
	refresh(true);
    }

    //
    // HasService methods
    //

    @Override
    public AggregatedRefreshService getService() {
	return parent.getApacheInfo().getService();
    }

    //
    // SmfPropertyGroupInfo methods
    //

    @Override
    public String getPropertyGroupName() throws ScfException {
	return parent.getApacheInfo().getPropertyGroupName();
    }

    //
    // SmfPropertyInfo methods
    //

    @Override
    public String getPropertyName() throws ScfException {
	if (propertyName == null) {
	    propertyName = ApacheUtil.getNextAvailablePropertyName(
		parent.getApacheInfo(), SMF_PROPERTY_PREFIX);
	}
	return propertyName;
    }

    //
    // Object methods
    //

    @Override
    public Module clone() {
	Module clone = new Module(getParent());
	for (MutableProperty<?> property : getProperties()) {
	    String name = property.getPropertyName();

	    @SuppressWarnings({"unchecked"})
	    MutableProperty<Object> oldProperty =
		(MutableProperty<Object>)property;

	    @SuppressWarnings({"unchecked"})
	    MutableProperty<Object> newProperty =
		(MutableProperty<Object>)clone.getProperty(name);

	    newProperty.setValue(oldProperty.getValue());
	}

	return clone;
    }

    //
    // ManagedObject methods
    //

    @Override
    public String getId() {
	return nameProperty.getValue();
    }

    @Override
    public String getName() {
	return getId();
    }

    //
    // HasIcon methods
    //

    @Override
    public Icon getIcon(int height) {
	return IconUtil.getClosestIcon(icons, height);
    }

    //
    // Module methods
    //

    public MutableProperty<String> getFileProperty() {
	return fileProperty;
    }

    public MutableProperty<String> getNameProperty() {
	return nameProperty;
    }

    public Modules getParent() {
	return parent;
    }

    public boolean isInRepo() {
	return propertyName != null;
    }

    public void refresh(boolean force) throws ScfException {
	smfProperty.updateFromRepo(force);
    }

    protected void removeFromRepo() throws ScfException {
	if (isInRepo()) {
	    smfProperty.removeFromRepo();
	}
    }

    public void saveToRepo() throws ScfException {
	ApacheUtil.saveToRepo(getService(),
	    new ScfRunnable() {
		@Override
		public void run() throws ScfException {
		    if (smfProperty.isChanged()) {
			smfProperty.saveToRepo();
		    }
		}
	    });
    }

    //
    // Static methods
    //

    public static boolean isValidName(String name) {
	return !name.isEmpty() && !name.matches(".*\\s.*");
    }
}
