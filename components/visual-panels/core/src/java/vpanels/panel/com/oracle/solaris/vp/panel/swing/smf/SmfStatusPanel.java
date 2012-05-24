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
import java.awt.event.*;
import java.beans.*;
import java.io.IOException;
import java.util.*;
import java.util.logging.*;
import javax.management.*;
import javax.swing.*;
import com.oracle.solaris.rad.jmx.RadNotification;
import com.oracle.solaris.scf.common.ScfException;
import com.oracle.solaris.vp.panel.common.api.smf_old.*;
import com.oracle.solaris.vp.panel.common.smf.*;
import com.oracle.solaris.vp.util.misc.ArrayUtil;
import com.oracle.solaris.vp.util.misc.finder.Finder;
import com.oracle.solaris.vp.util.swing.*;
import com.oracle.solaris.vp.util.swing.layout.*;

@SuppressWarnings({"serial"})
public class SmfStatusPanel extends SettingsPanel {
    //
    // Inner classes
    //

    static class TaskComponent {
	private Component component_;
	private HyperlinkLabel label_;

	TaskComponent(Component c, HyperlinkLabel l) {
	    component_ = c;
	    label_ = l;
	}

	Component getComponent() {
	    return component_;
	}

	HyperlinkLabel getLabel() {
	    return label_;
	}
    }

    //
    // Instance data
    //

    private ServiceTracker tracker;

    private JLabel statusLabel;
    private JTextArea statusArea;
    private JTextArea recArea;
    private JLabel tasksLabel;
    private JPanel taskPanel;

    private TaskComponent clearMaint;
    private TaskComponent clearDegraded;
    private TaskComponent degrade;
    private TaskComponent disable;
    private TaskComponent enable;
    private TaskComponent maintain;
    private TaskComponent refresh;
    private TaskComponent restart;

    private JLabel nameLabel;
    private JTextArea fmriArea;

    private JLabel descLabel;
    private JTextArea descArea;

    private PropertyChangeListener serviceListener =
	new PropertyChangeListener() {
	    @Override
	    public void propertyChange(PropertyChangeEvent event) {
		serviceChanged();
	    }
	};

    private NotificationListener notifyListener =
	new NotificationListener() {
	    @Override
	    public void handleNotification(Notification n, Object h) {
		final StateChange sc =
		    ((RadNotification)n).getPayload(StateChange.class);

		EventQueue.invokeLater(
		    new Runnable() {
			@Override
			public void run() {
			    setServiceState(sc.getState(),
				sc.getNextState(), sc.getAuxState(),
				sc.getStateTime());
			}
		    });
	    }
	};

    //
    // Constructors
    //

    public SmfStatusPanel() {
	JPanel panel = createForm();
	setContent(panel, false, false);
    }

    //
    // SmfStatusPanel methods
    //

    protected JPanel createForm() {
	nameLabel = createSectionLabel("");
	fmriArea = createTextArea();

	descLabel = createSectionLabel(
	    Finder.getString("service.status.label.description"));
	descArea = createTextArea();

	statusLabel = createSectionLabel(
	    Finder.getString("service.status.label.status"));
	statusArea = createTextArea();
	recArea = createTextArea();

	tasksLabel = createSectionLabel(
	    Finder.getString("service.status.label.tasks"));

	clearMaint = createClearMaintTaskComponent();
	clearDegraded = createClearDegradedTaskComponent();
	degrade = createDegradeTaskComponent();
	disable = createDisableTaskComponent();
	enable = createEnableTaskComponent();
	maintain = createMaintainTaskComponent();
	refresh = createRefreshTaskComponent();
	restart = createRestartTaskComponent();

	taskPanel = new JPanel(
	    new UniformLayout(UniformLayout.Orientation.VERTICAL));
	taskPanel.setOpaque(false);
	taskPanel.add(clearMaint.getComponent());
	taskPanel.add(clearDegraded.getComponent());
	taskPanel.add(enable.getComponent());
	taskPanel.add(disable.getComponent());
	taskPanel.add(refresh.getComponent());
	taskPanel.add(restart.getComponent());
	taskPanel.add(maintain.getComponent());
	taskPanel.add(degrade.getComponent());

	JPanel panel = new JPanel();
	panel.setOpaque(false);
	panel.setLayout(new ColumnLayout());
	ColumnLayoutConstraint c = new ColumnLayoutConstraint(
	    HorizontalAnchor.FILL, GUIUtil.getGap());
	panel.add(nameLabel, c);
	panel.add(fmriArea, c);
	panel.add(descLabel, c);
	panel.add(descArea, c);
	panel.add(statusLabel, c);
	panel.add(statusArea, c);
	panel.add(recArea, c);
	panel.add(tasksLabel, c);
	panel.add(taskPanel, c);

	return panel;
    }

    public HyperlinkLabel getClearDegradedLink() {
        return clearDegraded.getLabel();
    }

    public HyperlinkLabel getClearMaintLink() {
	return clearMaint.getLabel();
    }

    public HyperlinkLabel getDegradeLink() {
        return degrade.getLabel();
    }

    public HyperlinkLabel getDisableLink() {
        return disable.getLabel();
    }

    public HyperlinkLabel getEnableLink() {
        return enable.getLabel();
    }

    public HyperlinkLabel getMaintainLink() {
        return maintain.getLabel();
    }

    public HyperlinkLabel getRefreshLink() {
        return refresh.getLabel();
    }

    public HyperlinkLabel getRestartLink() {
        return restart.getLabel();
    }

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

	    serviceChanged();
	}
    }

    //
    // Private methods
    //

    private TaskComponent createTaskComponent(String taskRes, String tipRes,
	final Runnable task) {

	HyperlinkLabel link = new HyperlinkLabel(Finder.getString(taskRes));
	link.addActionListener(
	    new ActionListener() {
		@Override
		public void actionPerformed(ActionEvent e) {
		    task.run();
		}
	    });

	if (tipRes == null) {
	    return new TaskComponent(link, link);
	}

	String tip = Finder.getString(tipRes);
	if (tip == null) {
	    return new TaskComponent(link, link);
	}

	InfoLabel info = new InfoLabel(tip);
	JPanel panel = new JPanel(new RowLayout());
	RowLayoutConstraint r = new RowLayoutConstraint(
	    VerticalAnchor.CENTER, GUIUtil.getHalfGap(), 1f);
	panel.setOpaque(false);
	panel.add(link, r);
	panel.add(info, r.setWeight(0f));

	return new TaskComponent(panel, link);
    }

    abstract class SCFRunnable implements Runnable {
        public void run() {
	    try {
		runScf();
	    } catch (ScfException t) {
		if (t.getError() == SmfErrorCode.PERMISSION_DENIED) {
		    GUIUtil.showError(SmfStatusPanel.this, null,
			Finder.getString("error.scf.permission"));
		} else {
		    Logger.getLogger(getClass().getPackage().getName()).log(
			Level.SEVERE, Finder.getString("error.scf.general"), t);
		}
	    }
	}

	abstract protected void runScf() throws ScfException;
    }

    private TaskComponent createClearMaintTaskComponent() {
	return createTaskComponent(
	    "service.task.long.clear.maint",
	    "service.task.tip.clear.maint",
	    new SCFRunnable() {
		@Override
		protected void runScf() throws ScfException {
		    tracker.getService().clear();
		}
	    });
    }

    private TaskComponent createClearDegradedTaskComponent() {
	return createTaskComponent(
	    "service.task.long.clear.degraded",
	    "service.task.tip.clear.degraded",
	    new SCFRunnable() {
		@Override
		protected void runScf() throws ScfException {
		    tracker.getService().clear();
		}
	    });
    }

    private TaskComponent createDegradeTaskComponent() {
	return createTaskComponent(
	    "service.task.long.degrade",
	    "service.task.tip.degrade",
	    new SCFRunnable() {
		@Override
		protected void runScf() throws ScfException {
		    tracker.getService().degrade(true);
		}
	    });
    }

    private TaskComponent createDisableTaskComponent() {
	return createTaskComponent(
	    "service.task.long.disable",
	    "service.task.tip.disable",
	    new SCFRunnable() {
		@Override
		protected void runScf() throws ScfException {
		    tracker.getService().setPersistentlyEnabled(false);
		}
	    });
    }

    private TaskComponent createEnableTaskComponent() {
	return createTaskComponent(
	    "service.task.long.enable",
	    "service.task.tip.enable",
	    new SCFRunnable() {
		@Override
		protected void runScf() throws ScfException {
		    tracker.getService().setPersistentlyEnabled(true);
		}
	    });
    }

    private TaskComponent createMaintainTaskComponent() {
	return createTaskComponent(
	    "service.task.long.maintain",
	    "service.task.tip.maintain",
	    new SCFRunnable() {
		@Override
		protected void runScf() throws ScfException {
		    tracker.getService().maintain(true);
		}
	    });
    }

    private TaskComponent createRefreshTaskComponent() {
	return createTaskComponent(
	    "service.task.long.refresh",
	    "service.task.tip.refresh",
	    new SCFRunnable() {
		@Override
		protected void runScf() throws ScfException {
		    tracker.getService().refresh();
		}
	    });
    }

    private TaskComponent createRestartTaskComponent() {
	return createTaskComponent(
	    "service.task.long.restart",
	    "service.task.tip.restart",
	    new SCFRunnable() {
		@Override
		protected void runScf() throws ScfException {
		    tracker.getService().restart();
		}
	    });
    }

    private JLabel createSectionLabel(String text) {
	JLabel label = new JLabel(text);
	decorateTitle(label);

	return label;
    }

    private JTextArea createTextArea() {
	return new FlowTextArea();
    }

    private void serviceChanged() {
	ServiceMXBean service = tracker == null ? null : tracker.getService();

	Logger log = Logger.getLogger(getClass().getPackage().getName());

	boolean isInst = false;
	if (service != null) {
	    try {
		isInst = service.isInstance();
	    } catch (ScfException e) {
		log.log(Level.SEVERE, Finder.getString("error.scf.general"), e);
	    }
	}

	SmfState state = null;
	SmfState nextState = null;
	String auxState = null;
	Date sTime = null;

	if (isInst) {
	    try {
		state = service.getState();
		nextState = service.getNextState();
		auxState = service.getAuxiliaryState();
		sTime = service.getSTime();
	    } catch (ScfException t) {
		log.log(Level.SEVERE, Finder.getString("error.scf.general"), t);
	    }
	}

	// Can handle null state
	setServiceState(state, nextState, auxState, sTime);
	statusLabel.setVisible(isInst);
	statusArea.setVisible(isInst);

	String name = null;
	String fmri = null;
	String description = null;

	if (service != null) {
	    try {
		String value = service.getCommonName(
		    Locale.getDefault().getLanguage());
		String resource = isInst ?
		    "service.status.label.name.instance" :
		    "service.status.label.name.service";
		if (value == null) {
		    resource += ".null";
		}
		name = Finder.getString(resource, value);
		fmri = service.getFmri();

		description = service.getDescription(
		    Locale.getDefault().getLanguage());
	    } catch (ScfException e) {
		log.log(Level.SEVERE, Finder.getString("error.scf.general"), e);
	    }
	}

	nameLabel.setText(name);
	fmriArea.setText(fmri);

	if (description == null) {
	    description = Finder.getString(
		"service.status.label.description.unknown");
	}
	description = description.trim().replaceAll("\\s+", " ");
	descArea.setText(description);
    }

    private void setServiceState(SmfState state, SmfState nextState,
	String auxState, Date sTime) {

	// Can handle null state
	statusArea.setText(ServiceUtil.getStateDetails(
	    state, nextState, auxState, sTime));

	// Can handle null state
	String rec = ServiceUtil.getRecommendation(state);
	if (rec == null) {
	    recArea.setVisible(false);
	} else {
	    recArea.setVisible(true);
	    recArea.setText(rec);
	}

	TaskComponent[] tasks = {};

	// No tasks if in transition
	if (state != null &&
	    (nextState == null || nextState == SmfState.NONE)) {

	    switch (state) {
		case MAINT:
		    tasks = new TaskComponent[] {clearMaint, disable};
		break;

		case OFFLINE:
		    tasks = new TaskComponent[] {
			disable, restart, maintain, degrade};
		break;

		case DISABLED:
		    tasks = new TaskComponent[] {enable};
		break;

		case ONLINE:
		    tasks = new TaskComponent[] {
			disable, refresh, restart, maintain, degrade};
		break;

		case DEGRADED:
		    tasks = new TaskComponent[] {clearDegraded, disable};
		break;
	    }
	}

	setTasks(tasks);
    }

    private void setTasks(TaskComponent... taskcomps) {
	Component[] comps = new Component[taskcomps.length];
	for (int i = 0; i < taskcomps.length; i++)
	    comps[i] = taskcomps[i].getComponent();

	for (Component c : taskPanel.getComponents()) {
	    c.setVisible(ArrayUtil.contains(comps, c));
	}

	tasksLabel.setVisible(comps.length != 0);
    }
}
