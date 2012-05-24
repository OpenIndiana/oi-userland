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
import com.oracle.solaris.rad.ObjectException;
import com.oracle.solaris.scf.common.ScfException;
import com.oracle.solaris.vp.panel.common.model.*;
import com.oracle.solaris.vp.panel.common.smf.*;
import com.oracle.solaris.vp.util.misc.*;
import com.oracle.solaris.vp.util.misc.finder.Finder;
import com.oracle.solaris.vp.util.misc.property.MutableProperty;
import com.oracle.solaris.vp.util.swing.HasIcon;

@SuppressWarnings({"serial"})
public class VirtualHost extends AbstractManagedObject<ManagedObject>
    implements HasIcon, Cloneable, Enableable, ApacheInfo {

    //
    // Static data
    //

    protected static final List<ImageIcon> ICONS_ENABLED = Finder.getIcons(
	"images/vhost-enabled-16.png",
	"images/vhost-enabled-24.png",
	"images/vhost-enabled-32.png");

    protected static final List<ImageIcon> ICONS_DISABLED = Finder.getIcons(
	"images/vhost-disabled-16.png",
	"images/vhost-disabled-24.png",
	"images/vhost-disabled-32.png");

    public static final String SMF_GROUP_PREFIX = "vhost-";

    public static final String PROPERTY_CUSTOM_ENABLED = "custom_conf";
    public static final String PROPERTY_CUSTOM_FILE = "custom_file";
    public static final String PROPERTY_DOCROOT = "docroot";
    public static final String PROPERTY_DOMAIN = "domain";
    public static final String PROPERTY_ENABLED = "enabled";
    public static final String PROPERTY_PORT = "port";
    public static final String PROPERTY_SERVE_HOME_DIRS = "serve_home_dir";
    public static final String PROPERTY_SSL_CERT = "sslcert";
    public static final String PROPERTY_SSL_ENABLED = "sslengine";
    public static final String PROPERTY_SSL_IP = "sslip";
    public static final String PROPERTY_SSL_KEY = "sslkey";
    public static final String PROPERTY_SSL_PORT = "sslport";

    //
    // Instance data
    //

    private ApachePanelDescriptor parent;
    private String group;
    private MimeTypes mimeTypes;

    private BasicSmfMutableProperty<Boolean> customEnabledProperty =
	new BooleanSmfProperty(PROPERTY_CUSTOM_ENABLED, this);

    private BasicSmfMutableProperty<String> customFileProperty =
	new StringSmfProperty(PROPERTY_CUSTOM_FILE, this);

    private BasicSmfMutableProperty<String> docRootProperty =
	new StringSmfProperty(PROPERTY_DOCROOT, this);

    private BasicSmfMutableProperty<String> domainProperty =
	new StringSmfProperty(PROPERTY_DOMAIN, this);

    private BasicSmfMutableProperty<Boolean> enabledProperty =
	new BooleanSmfProperty(PROPERTY_ENABLED, this);

    private BasicSmfMutableProperty<Integer> portProperty =
	new CountSmfProperty(PROPERTY_PORT, this);

    private BasicSmfMutableProperty<Boolean> serveHomeDirsProperty =
	new BooleanSmfProperty(PROPERTY_SERVE_HOME_DIRS, this);

    private BasicSmfMutableProperty<String> sslCertProperty =
	new StringSmfProperty(PROPERTY_SSL_CERT, this);

    private BasicSmfMutableProperty<Boolean> sslEnabledProperty =
	new BooleanSmfProperty(PROPERTY_SSL_ENABLED, this);

    private BasicSmfMutableProperty<String> sslIpProperty =
	new StringSmfProperty(PROPERTY_SSL_IP, this);

    private BasicSmfMutableProperty<String> sslKeyProperty =
	new StringSmfProperty(PROPERTY_SSL_KEY, this);

    private BasicSmfMutableProperty<Integer> sslPortProperty =
	new CountSmfProperty(PROPERTY_SSL_PORT, this);

    //
    // Constructors
    //

    public VirtualHost(ApachePanelDescriptor parent) {
	this.parent = parent;

	customEnabledProperty.setFirstValue(false);
	addProperties(customEnabledProperty);

	customFileProperty.setFirstValue("");
	addProperties(customFileProperty);

	docRootProperty.setFirstValue("");
	addProperties(docRootProperty);

	domainProperty.setFirstValue("");
	addProperties(domainProperty);

	enabledProperty.setFirstValue(false);
	addProperties(enabledProperty);

	portProperty.setFirstValue(80);
	addProperties(portProperty);

	serveHomeDirsProperty.setFirstValue(false);
	addProperties(serveHomeDirsProperty);

	sslCertProperty.setFirstValue("");
	addProperties(sslCertProperty);

	sslEnabledProperty.setFirstValue(false);
	addProperties(sslEnabledProperty);

	String ip = "";
	try {
	    ip = getParent().getClientContext().getConnectionInfo().
		getInetAddresses()[0].getHostAddress();
	} catch (Throwable ignore) {
	}

	sslIpProperty.setFirstValue(ip);
	addProperties(sslIpProperty);

	sslKeyProperty.setFirstValue("");
	addProperties(sslKeyProperty);

	sslPortProperty.setFirstValue(443);
	addProperties(sslPortProperty);

	ChangeableAggregator aggregator = getChangeableAggregator();

	addChildren(mimeTypes = new MimeTypes(this));
	aggregator.addChangeables(mimeTypes.getChangeableAggregator());
    }

    public VirtualHost(ApachePanelDescriptor parent, String group)
	throws ScfException {

	this(parent);
	this.group = group;
	refresh(true);
    }

    //
    // ManagedObject methods
    //

    @Override
    public String getId() {
	return getPropertyGroupName();
    }

    @Override
    public String getName() {
	return domainProperty.getFirstValue();
    }

    @Override
    public String getStatusText() {
	return docRootProperty.getFirstValue();
    }

    //
    // HasIcon methods
    //

    @Override
    public Icon getIcon(int height) {
	return IconUtil.getClosestIcon(isEnabled() ?
	    ICONS_ENABLED : ICONS_DISABLED, height);
    }

    //
    // HasService methods
    //

    @Override
    public AggregatedRefreshService getService() {
	return parent.getService();
    }

    //
    // SmfPropertyGroupInfo methods
    //

    @Override
    public String getPropertyGroupName() {
	if (group == null) {
	    group = parent.getVirtualHostNamePool().get();
	}

	return group;
    }

    //
    // SmfPropertyInfo methods
    //

    @Override
    public String getPropertyName() {
	// Use the default property names
	return null;
    }

    //
    // ApacheInfo methods
    //

    @Override
    public ApachePanelDescriptor getPanelDescriptor() {
	return getParent();
    }

    //
    // Enableable methods
    //

    @Override
    public boolean isEnabled() {
	return enabledProperty.getFirstValue();
    }

    //
    // Object methods
    //

    @Override
    public VirtualHost clone() {
	VirtualHost clone = new VirtualHost(getParent());
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
    // VirtualHost methods
    //

    public BasicSmfMutableProperty<Boolean> getCustomEnabledProperty() {
	return customEnabledProperty;
    }

    public BasicSmfMutableProperty<String> getCustomFileProperty() {
	return customFileProperty;
    }

    public BasicSmfMutableProperty<String> getDocRootProperty() {
	return docRootProperty;
    }

    public BasicSmfMutableProperty<String> getDomainProperty() {
	return domainProperty;
    }

    public BasicSmfMutableProperty<Boolean> getEnabledProperty() {
	return enabledProperty;
    }

    public MimeTypes getMimeTypes() {
	return mimeTypes;
    }

    public ApachePanelDescriptor getParent() {
	return parent;
    }

    public BasicSmfMutableProperty<Integer> getPortProperty() {
	return portProperty;
    }

    public BasicSmfMutableProperty<Boolean> getServeHomeDirsProperty() {
	return serveHomeDirsProperty;
    }

    public BasicSmfMutableProperty<String> getSslCertProperty() {
	return sslCertProperty;
    }

    public BasicSmfMutableProperty<Boolean> getSslEnabledProperty() {
	return sslEnabledProperty;
    }

    public BasicSmfMutableProperty<String> getSslIpProperty() {
	return sslIpProperty;
    }

    public BasicSmfMutableProperty<String> getSslKeyProperty() {
	return sslKeyProperty;
    }

    public BasicSmfMutableProperty<Integer> getSslPortProperty() {
	return sslPortProperty;
    }

    public boolean isInRepo() {
	return group != null;
    }

    public void refresh(boolean force) throws ScfException {
	for (MutableProperty<?> property : getProperties()) {
	    if (property instanceof SmfMutableProperty) {
		((SmfMutableProperty)property).updateFromRepo(force);
	    }
	}

	mimeTypes.refresh(force);
    }

    protected void removeFromRepo() throws ScfException {
	if (group != null) {
	    ServiceMXBean service = getService();
	    service.deletePropertyGroup(group);
	    service.refresh();
	    parent.getVirtualHostNamePool().put(group);
	}
    }

    public void saveToRepo() throws ScfException {
	ApacheUtil.saveToRepo(getService(),
	    new ScfRunnable() {
		@Override
		public void run() throws ScfException {
		    for (MutableProperty property : getProperties()) {
			if (property.isChanged()) {
			    if (property instanceof SmfMutableProperty) {
				((SmfMutableProperty)property).saveToRepo();
			    } else {
				property.save();
			    }
			}
		    }

		    mimeTypes.saveToRepo();
		}
	    });
    }

    protected void validate() throws VirtualHostGeneralValidationException,
	VirtualHostSSLValidationException {

	validateDomain();
	validateCustomFile();
	validateDocRoot();
	validateSSLIP();
	validateSSLCert();
	validateSSLKey();
    }

    //
    // Private methods
    //

    private void validateCustomFile()
	throws VirtualHostGeneralValidationException {

	if (customEnabledProperty.getFirstValue() &&
	   (customEnabledProperty.isChanged() ||
	    customFileProperty.isChanged()) &&
	    customFileProperty.getFirstValue().isEmpty()) {
	    throw new VirtualHostGeneralValidationException(getId(),
		Finder.getString("vhost.general.error.customfile.empty"));
	}
    }

    private void validateDomain() throws VirtualHostGeneralValidationException {
	boolean domainChanged = domainProperty.isChanged();
	String domain = domainProperty.getFirstValue();

	if (domainChanged) {
	    validateDomainName(domain, getId());
	}

	// Only one virtual host for a given domain may be enabled
        if (isEnabled() && (enabledProperty.isChanged() || domainChanged)) {
	    for (VirtualHost peer : parent.getChildren()) {
		if (peer != this && peer.isEnabled() &&
		    ObjectUtil.equals(domain,
			peer.getDomainProperty().getFirstValue())) {

		    throw new VirtualHostGeneralValidationException(getId(),
			Finder.getString(
			"vhost.general.error.domain.duplicate", domain));
		}
	    }
	}
    }

    private void validateDocRoot()
	throws VirtualHostGeneralValidationException {

	if (docRootProperty.isChanged() &&
	    docRootProperty.getFirstValue().isEmpty()) {
	    throw new VirtualHostGeneralValidationException(getId(),
		Finder.getString("vhost.general.error.docroot.empty"));
	}
    }

    private void validateSSLCert()
	throws VirtualHostSSLValidationException {

	if (sslEnabledProperty.getFirstValue() &&
           (sslEnabledProperty.isChanged() || sslCertProperty.isChanged()) &&
	    sslCertProperty.getFirstValue().isEmpty()) {
	    throw new VirtualHostSSLValidationException(getId(),
		Finder.getString("vhost.ssl.error.cert.empty"));
	}
    }

    private void validateSSLIP()
	throws VirtualHostSSLValidationException {

	if (sslEnabledProperty.getFirstValue() &&
           (sslEnabledProperty.isChanged() || sslIpProperty.isChanged())) {

	    String sslIP = sslIpProperty.getFirstValue();
	    if (sslIP.isEmpty()) {
		throw new VirtualHostSSLValidationException(getId(),
		    Finder.getString("vhost.ssl.error.ip.empty"));
	    }

	    try {
                boolean isLocalAddress =
		    parent.getNetworkMXBean().isLocalAddress(sslIP);

		if (!isLocalAddress) {
		    throw new VirtualHostSSLValidationException(getId(),
			Finder.getString("vhost.ssl.error.ip.invalid", sslIP));
		}
	    } catch (ObjectException e) {
		throw new VirtualHostSSLValidationException(getId(),
		    Finder.getString("vhost.ssl.error.ip.syserror", e));
	    }
	}
    }

    private void validateSSLKey()
	throws VirtualHostSSLValidationException {

	if (sslEnabledProperty.getFirstValue() &&
           (sslEnabledProperty.isChanged() || sslKeyProperty.isChanged()) &&
	    sslKeyProperty.getFirstValue().isEmpty()) {
	    throw new VirtualHostSSLValidationException(getId(),
		Finder.getString("vhost.ssl.error.key.empty"));
	}
    }

    //
    // Static methods
    //

    public static void validateDomainName(String domain, String id)
	throws VirtualHostGeneralValidationException {

	if (domain.isEmpty()) {
	    throw new VirtualHostGeneralValidationException(id,
		Finder.getString("vhost.general.error.domain.empty"));
	}

	if (!domain.matches("[\\w\\.\\-]+")) {
	    throw new VirtualHostGeneralValidationException(id,
		Finder.getString("vhost.general.error.domain.invalid",
		domain));
	}
    }
}
