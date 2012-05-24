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

package com.oracle.solaris.vp.panels.firewall.client.swing;

import java.util.*;
import com.oracle.solaris.vp.panel.common.smf.*;
import com.oracle.solaris.scf.common.ScfException;
import com.oracle.solaris.vp.panels.firewall.client.swing.AccessPolicy.Type;
import com.oracle.solaris.vp.panels.firewall.client.swing.AccessPolicy.Type;

public class SimpleAccessPolicy implements AccessPolicy {


    // Firewall policy is stored in SMF property groups
    // firewall_config stores active policy
    // firewall_context stores static firewall information.
    //
    // The following sets of strings are
    // - firewall_config pg and its properties
    // - possible policy values
    //
    // Note that policy configuration only modifies properties in
    // firewall_config property group.
    //
    public static final String FW_CONFIG_PG = "firewall_config";
    public static final String POLICY_PROP = "policy";
    public static final String APPLY_TO_PROP = "apply_to";
    public static final String EXCEPTIONS_PROP = "exceptions";
    public static final String CUSTOM_FILE_PROP = "custom_policy_file";
    public static final String OPEN_PORT_PROP = "open_ports";

    //
    // Instance data
    //

    private Type type_;
    private String customFile_;

    private List<String> aList_ = new ArrayList<String>();
    private List<String> roAList_ = Collections.unmodifiableList(aList_);

    private List<String> eList_ = new ArrayList<String>();
    private List<String> roEList_ = Collections.unmodifiableList(eList_);

    private List<String> pList_ = new ArrayList<String>();
    private List<String> roPList_ = Collections.unmodifiableList(pList_);

    private SimpleSmfPropertyGroupInfo pgInfo_;
    private BasicSmfMutableProperty<String> policy_;
    private BasicSmfMutableProperty<String> apply_;
    private BasicSmfMutableProperty<String> exceptions_;
    private BasicSmfMutableProperty<String> ports_;
    private BasicSmfMutableProperty<String> file_;

    //
    // Constructors
    //

    public SimpleAccessPolicy(Type type, String customFile,
	List<String> aList, List<String> eList, List<String> portList) {
	init(type, customFile, aList, eList, portList);
    }

    public SimpleAccessPolicy(Type type) {
	this(type, null, null, null, null);
    }

    public SimpleAccessPolicy(Type type, List<String> pList) {
	this(type, null, null, null, pList);
    }

    public SimpleAccessPolicy(Type type, List<String> aList,
	List<String> eList) {
	this(type, null, aList, eList, null);
    }

    public SimpleAccessPolicy(Type type, String customFile,
	List<String> aList, List<String> eList) {
	this(type, customFile, aList, eList, null);
    }

    public SimpleAccessPolicy(SimpleSmfPropertyGroupInfo pgInfo)
	throws ScfException {

	setPgInfo(pgInfo);
	initFromRepo();
    }

    //
    // AccessPolicy methods
    //

    public List<String> getApplyToList() {
	return roAList_;
    }

    public List<String> getExceptionsList() {
	return roEList_;
    }

    public List<String> getOpenPortList() {
	return roPList_;
    }

    public String getCustomFile() {
	return customFile_;
    }

    public Type getType() {
	return type_;
    }

    //
    // SimpleAccessPolicy methods
    //

    public void setType(Type type) {
	type_ = type;
    }

    public void setPortList(List<String> portList) {
	pList_.clear();
	pList_.addAll(portList);
    }

    public List<String> getSavedApplyToList() {
	return (pgInfo_ == null ? null :
	    AccessPolicyUtil.cleanList(apply_.getSavedValue()));
    }

    public List<String> getSavedExceptionsList() {
	return (pgInfo_ == null ? null :
	    AccessPolicyUtil.cleanList(exceptions_.getSavedValue()));
    }

    public List<String> getSavedOpenPortList() {
	return (pgInfo_ == null ? null :
	    AccessPolicyUtil.cleanList(ports_.getSavedValue()));
    }

    public String getSavedCustomFile() {
	return (pgInfo_ == null ? null : file_.getFirstSavedValue());
    }

    public Type getSavedType() {
	return (pgInfo_ == null ? null :
	    AccessPolicyUtil.toType(policy_.getFirstSavedValue()));
    }

    public void setPgInfo(SimpleSmfPropertyGroupInfo pgInfo) {
	pgInfo_ = pgInfo;

	try {
	    policy_ = new StringSmfProperty(POLICY_PROP,
		new SimpleSmfPropertyInfo(pgInfo_.getService(),
		pgInfo_.getPropertyGroupName(), POLICY_PROP));

	    apply_ = new StringSmfProperty(APPLY_TO_PROP,
		new SimpleSmfPropertyInfo(pgInfo_.getService(),
		pgInfo_.getPropertyGroupName(), APPLY_TO_PROP));

	    exceptions_ = new StringSmfProperty(EXCEPTIONS_PROP,
		new SimpleSmfPropertyInfo(pgInfo_.getService(),
		pgInfo_.getPropertyGroupName(), EXCEPTIONS_PROP));

	    ports_ = new StringSmfProperty(OPEN_PORT_PROP,
		new SimpleSmfPropertyInfo(pgInfo_.getService(),
		pgInfo_.getPropertyGroupName(), OPEN_PORT_PROP));

	    file_ = new StringSmfProperty(CUSTOM_FILE_PROP,
		new SimpleSmfPropertyInfo(pgInfo_.getService(),
		pgInfo_.getPropertyGroupName(), CUSTOM_FILE_PROP));
	} catch (ScfException e) {}
    }

    public void setRepoValue() throws ScfException {
	if (pgInfo_ == null)
	    return;

	AggregatedRefreshService service =
	(AggregatedRefreshService) pgInfo_.getService();

	ScfRunnable r = new ScfRunnable() {
	    @Override
	    public void run() throws ScfException {
		policy_.setFirstValue(AccessPolicyUtil.toPropValue(type_));
		policy_.saveToRepo();

		List<String> list;
		switch (type_) {
		case CUSTOM:
		    file_.setFirstValue(customFile_);
		    file_.saveToRepo();
		    break;

		case ALLOW:
		case DENY:
		    if (apply_.getExistsInRepo()) {
			if (roAList_.size() > 0) {
			    apply_.setValue(new ArrayList<String>(roAList_));
			} else {
			    apply_.setFirstValue("");
			}

			apply_.saveToRepo();
		    }

		    if (exceptions_.getExistsInRepo()) {
			if (roEList_.size() > 0) {
			    exceptions_.setValue(
				new ArrayList<String>(roEList_));
			} else {
			    exceptions_.setFirstValue("");
			}

			exceptions_.saveToRepo();
		    }
		    break;

		case USE_GLOBAL:
		case NONE:
		default:
		    break;
		}

		//
		// Commit changes for open port list
		//
		if (ports_.getExistsInRepo()) {
		    if (roPList_.size() > 0) {
			ports_.setValue(new ArrayList<String>(roPList_));
		    } else {
			ports_.setFirstValue("");
		    }

		    ports_.saveToRepo();
		}
	    }
	}; // End of runnable

	synchronized (service) {
	    boolean needLock = !service.isPaused();
	    if (needLock) {
		service.pause();
	    }

	    boolean success = false;
	    try {
		// Throws ScfException
		r.run();
		success = true;
	    } finally {
		if (needLock) {
		    if (success) {
			// Throws ScfException
			service.unpause();
		    } else {
			// Unlock, refresh if needed, ignore any exceptions
			// since we are already in the midst of throwing one
			try {
			    service.unpause();
			} catch (Throwable ignore) {
			}
		    }
		}
	    }
	}
    }

    public void initFromRepo() throws ScfException {
	Type type;
	List<String> aList = null;
	List<String> eList = null;
	List<String> pList = null;
	String cFile = null;

	policy_.updateFromRepo(true);
	apply_.updateFromRepo(true);
	exceptions_.updateFromRepo(true);

	type = AccessPolicyUtil.toType(policy_.getFirstSavedValue());
	aList = AccessPolicyUtil.cleanList(apply_.getSavedValue());
	eList = AccessPolicyUtil.cleanList(exceptions_.getSavedValue());

	if (ports_.getExistsInRepo()) {
	    ports_.updateFromRepo(true);
	    pList = AccessPolicyUtil.cleanList(ports_.getSavedValue());
	}

	if (file_.getExistsInRepo()) {
	    file_.updateFromRepo(true);
	    cFile = file_.getFirstSavedValue();
	}

	init(type, cFile, aList, eList, pList);
    }

    public void update(Type type, String customFile,
	List<String> aList, List<String> eList, List<String> pList) {
	init(type, customFile, aList, eList, pList);
    }

    //
    // Private methods
    //

    private void init(Type type, String customFile,
	List<String> aList, List<String> eList, List<String> portList) {

	type_ = type;
	customFile_ = customFile;

	if (aList != null) {
	    aList_.clear();
	    aList_.addAll(aList);
	}

	if (eList != null) {
	    eList_.clear();
	    eList_.addAll(eList);
	}

	if (portList != null) {
	    pList_.clear();
	    pList_.addAll(portList);
	}
    }
}
