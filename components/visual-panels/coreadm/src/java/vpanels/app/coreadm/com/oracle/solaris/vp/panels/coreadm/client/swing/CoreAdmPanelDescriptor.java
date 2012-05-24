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

package com.oracle.solaris.vp.panels.coreadm.client.swing;

import java.beans.*;
import java.io.IOException;
import java.util.*;
import javax.management.*;
import javax.swing.Icon;
import javax.swing.border.Border;
import com.oracle.solaris.adr.Stability;
import com.oracle.solaris.scf.common.ScfException;
import com.oracle.solaris.vp.panel.common.*;
import com.oracle.solaris.vp.panel.common.api.file.*;
import com.oracle.solaris.vp.panel.common.control.*;
import com.oracle.solaris.vp.panel.common.model.*;
import com.oracle.solaris.vp.panel.common.smf.*;
import com.oracle.solaris.vp.panel.swing.control.*;
import com.oracle.solaris.vp.panel.swing.model.SwingPanelDescriptor;
import com.oracle.solaris.vp.util.misc.SimpleHasId;
import com.oracle.solaris.vp.util.misc.finder.Finder;
import com.oracle.solaris.vp.util.swing.*;

@SuppressWarnings({"serial"})
public class CoreAdmPanelDescriptor
    extends ServicePanelDescriptor<CoreManagedObject>
    implements SwingPanelDescriptor<CoreManagedObject>, HasIcons {

    //
    // Static data
    //

    private static final String TMP_SERVICE = "system/vpanels-coreadm";
    private static final String SERVICE = "system/coreadm";
    private static final String INSTANCE = "default";

    private static String findSvc(ClientContext context) throws IOException
    {
	ObjectName tmpon;
	try {
	    tmpon = ServiceUtil.getServiceObjectName(TMP_SERVICE, null);
	} catch (MalformedObjectNameException ex) {
	    return (SERVICE);
	}

	return (context.getConnectionInfo().getConnector().
	    getMBeanServerConnection().isRegistered(tmpon) ?
	    TMP_SERVICE : SERVICE);
    }

    //
    // Instance data
    //

    private DefaultControl control;
    private CoreConfig coreConfig_ = new CoreConfig();
    private CoreAdmSettingsTab settingsTab_;
    private MXBeanTracker<FileBrowserMXBean> filesBeanTracker;

    private PropertyChangeListener filesBeanListener =
	new PropertyChangeListener() {
	    @Override
	    public void propertyChange(PropertyChangeEvent event) {
		updateCoreConfig();
	    }
	};

    //
    // Constructors
    //

    public CoreAdmPanelDescriptor(String id, ClientContext context)
	throws InstanceNotFoundException, IOException, TrackerException,
	ScfException, InvalidScfDataException, MissingScfDataException {

	super(id, context, findSvc(context), INSTANCE);

	filesBeanTracker = new MXBeanTracker<FileBrowserMXBean>(
	    FileBrowserUtil.OBJECT_NAME, FileBrowserMXBean.class,
	    Stability.PRIVATE, context);

        filesBeanTracker.addPropertyChangeListener(
	    MXBeanTracker.PROPERTY_BEAN, filesBeanListener);
	updateCoreConfig();

	setComparator(SimpleHasId.COMPARATOR);

        DefaultControl tControl = new TabbedControl<CoreAdmPanelDescriptor>(
	    "main", null, this) {
	    @Override
	    public String getHelpMapID() {
		return "coreadm-overview";
	    }
	};
	tControl.addChildren(new CoresTab(this),
	    settingsTab_ = new CoreAdmSettingsTab(this));

	control = new PanelFrameControl<CoreAdmPanelDescriptor>(this) {
	    @Override
	    protected Border getDefaultBorder() {
                return new ClippedBorder(super.getDefaultBorder(), true, false,
		    false, false);
	    }
	};
	control.addChildren(tControl);

	refresh(true);
    }

    //
    // HasIcons methods
    //

    @Override
    public List<? extends Icon> getIcons() {
	return CoreManagedObject.icons;
    }

    //
    // ManagedObject methods
    //

    /**
     * Stops monitoring the connection to the remote host.
     */
    @Override
    public void dispose() {
	filesBeanTracker.dispose();
	super.dispose();
    }

    @Override
    public String getName() {
	return Finder.getString("panel.coreadm.name");
    }

    //
    // PanelDescriptor methods
    //

    @Override
    public Control getControl() {
	return control;
    }

    //
    // ServicePanelDescriptor methods
    //

    @Override
    public void refresh(boolean force) throws ScfException,
	InvalidScfDataException, MissingScfDataException {

	super.refresh(force);
	setCoreConfig(new CoreConfig(getService()));

	/* XXX */
	settingsTab_.propertyChange(null);
    }

    /*
     * CoreAdmPanelDescriptor methods
     */

    CoreConfig getCoreConfig()
    {
	return (coreConfig_);
    }

    void setCoreConfig(CoreConfig newConfig)
    {
	CoreConfig oldConfig = coreConfig_;
	coreConfig_ = newConfig;
	refreshCores(oldConfig, coreConfig_);
    }

    void updateCoreConfig()
    {
	CoreConfig dummyConfig = new CoreConfig();
	refreshCores(dummyConfig, coreConfig_);
    }

    /*
     * Private methods
     */

    private void findCoresFile(List<CoreManagedObject> cores, String path,
	CoreUtil.PathElement[] elements, int index, FileSnapshot f)
    {
	if (f.isDirectory())
	    findCoresAux(cores, path, elements, index + 1);
	else if (index == elements.length - 1)
	    cores.add(new CoreManagedObject(this, path, f.getLength()));
    }

    private void findCoresAux(List<CoreManagedObject> cores, String stem,
	CoreUtil.PathElement[] elements, int index)
    {
	if (index == elements.length)
		return;

	CoreUtil.PathElement e = elements[index];
	try {
	    if (!e.isRegex_) {
		String name = stem + '/' + e.element_;
		findCoresFile(cores, name, elements, index,
		    filesBeanTracker.getBean().getFile(name));
	    } else {
		/*
		 * XXX: This doesn't handle %d and the fact it can
		 * match nested directories.
		 */
                List<FileSnapshot> ff =
		    filesBeanTracker.getBean().getFiles(stem);
		for (FileSnapshot f : ff) {
		    String base = f.getBaseName();
		    if (base.matches("^" + e.element_ + "$"))
			findCoresFile(cores, stem + '/' + base, elements,
			    index, f);
		}
	    }
	} catch (Exception xcp) {
	    /*
	     * Something failed.  (e.g. a NPE from trying to access
	     * an inaccessible directory).  Just move on.
	     */
	}
    }

    /**
     * Finds all cores that match the specified pattern.
     *
     * @param cores a list to which found cores will added
     * @param pattern the pattern against which file names will be matched
     */
    private void findCores(List<CoreManagedObject> cores, String pattern)
    {
	CoreUtil.PathElement[] elements = CoreUtil.pathToRegex(pattern);

	/*
	 * A global path starts with a /, and therefore an empty
	 * path element.
	 */
	assert (elements[0].element_.isEmpty());
	findCoresAux(cores, "", elements, 1);
    }

    /**
     * Update the list of core files if our new configuration has
     * different core file patterns.
     */
    private void refreshCores(CoreConfig oldconf, CoreConfig newconf)
    {
	/*
	 * XXX: We should really do this asynchronously.
	 * XXX: We should consider when we might want to force an update.
	 */
	String newgpat = newconf.getGlobalScope().getPattern();
	String newppat = newconf.getProcessScope().getPattern();

	if (newgpat.equals(oldconf.getGlobalScope().getPattern()) &&
	    newppat.equals(oldconf.getProcessScope().getPattern()))
		return;

	List<CoreManagedObject> cores = new LinkedList<CoreManagedObject>();

	if (newgpat.startsWith("/"))
		findCores(cores, newgpat);
	if (newppat.startsWith("/"))
		findCores(cores, newppat);

	clearChildren();
	addChildren(cores.toArray(new CoreManagedObject[0]));
    }
}
