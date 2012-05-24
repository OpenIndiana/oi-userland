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

package com.oracle.solaris.vp.client.common;

import java.awt.*;
import java.util.*;
import java.util.List;
import javax.management.*;
import javax.management.remote.JMXConnectionNotification;
import javax.swing.tree.*;
import javax.swing.WindowConstants;
import com.oracle.solaris.vp.panel.common.*;
import com.oracle.solaris.vp.util.misc.EnumerationIterator;
import com.oracle.solaris.vp.util.swing.*;
import com.oracle.solaris.vp.util.swing.tree.TypedTreeNode;

/**
 * The {@code ConnectionManager} class maintains a dependency tree of {@link
 * ConnectionInfo}s and {@link ConnectionListener}s.
 * <p/>
 * Dependencies between connections could be hard (connection {@code b} actively
 * uses connection {@code a} to communicate) or soft ({@code a} was created in
 * the process of creating {@code b}, and {@code a} should be maintained while
 * {@code b} is active in case the user wants to return to {@code a} at some
 * point without having to re-authenticate).
 * <p/>
 * Each connection in the tree is managed until it has no dependants (other
 * connections or listeners), at which point it is removed from the dependency
 * tree.  If there are no other references to it outside of this class, it will
 * be garbage collected (and thus closed).
 */
public class ConnectionManager {
    //
    // Inner classes
    //

    /**
     * Graphically display the dependency tree for debugging.
     */
    private class Visualizer {
	//
	// Instance data
	//

	private DefaultTreeModel model = new DefaultTreeModel(root);
	private ExtTree tree = new ExtTree(model);

	//
	// Constructors
	//

	public Visualizer() {
	    ExtFrame frame = new ExtFrame();
	    frame.setAutoResizeEnabled(true);
	    Container cont = frame.getContentPane();
	    cont.setLayout(new BorderLayout());
	    cont.add(tree, BorderLayout.CENTER);

	    frame.setLocationByPlatform(true);
	    frame.setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
	    frame.pack();
	    frame.setVisible(true);
	}

	//
	// Visualizer methods
	//

	public void update() {
	    EventQueue.invokeLater(
		new Runnable() {
		    @Override
		    public void run() {
			model.nodeStructureChanged(root);
			tree.setExpandedRecursive(true);
		    }
		});
	}
    }

    private class DependencyTreeNode<T> extends TypedTreeNode<T> {
	//
	// Constructors
	//

	public DependencyTreeNode(T userObject) {
	    super(userObject);
	}

	//
	// DefaultMutableTreeNode methods
	//

	@Override
	public void add(MutableTreeNode child) {
	    super.add(child);
	    DependencyTreeNode node = (DependencyTreeNode)child;
	    nodeMap.put(node.getUserObject(), node);
	    if (visualizer != null) {
		visualizer.update();
	    }
	}

	@Override
	public void remove(MutableTreeNode child) {
	    super.remove(child);
	    DependencyTreeNode node = (DependencyTreeNode)child;
	    nodeMap.remove(node.getUserObject());
	    if (visualizer != null) {
		visualizer.update();
	    }
	}

	//
	// DependencyTreeNode methods
	//

	@SuppressWarnings({"unchecked"})
	public Iterable<DependencyTreeNode> getChildren() {
	    return new EnumerationIterator<DependencyTreeNode>(children());
	}
    }

    private class ConnectionTreeNode
	extends DependencyTreeNode<ConnectionInfo> {

	//
	// Instance data
	//

	private boolean healthy = true;

	//
	// Constructors
	//

	public ConnectionTreeNode(ConnectionInfo info) {
	    super(info);
	}

	//
	// Object methods
	//

	@Override
	public String toString() {
	    return String.format("%s: %s (%s)", getUserObject().hashCode(),
		super.toString(), isHealthy() ? "healthy" : "unhealthy");
	}

	//
	// ConnectionTreeNode methods
	//

	public boolean isHealthy() {
	    return healthy;
	}

	public void setHealthy(boolean healthy) {
	    this.healthy = healthy;
	    if (visualizer != null) {
		visualizer.update();
	    }
	}
    }

    private class ListenerTreeNode
	extends DependencyTreeNode<ConnectionListener> {

	//
	// Constructors
	//

	public ListenerTreeNode(ConnectionListener listener) {
	    super(listener);
	}
    }

    //
    // Static data
    //

    private static NotificationFilter nFilter =
	new NotificationFilter() {
	    @Override
	    public boolean isNotificationEnabled(Notification notification) {
		return notification.getType().equals(
		    JMXConnectionNotification.FAILED);
	    }
	};

    //
    // Instance data
    //

    private DependencyTreeNode<?> root = new DependencyTreeNode<Object>(null);

    // Set to null unless debugging
    private Visualizer visualizer = null;

    private Map<Object, DependencyTreeNode> nodeMap =
	new HashMap<Object, DependencyTreeNode>();

    private NotificationListener nListener =
	new NotificationListener() {
	    @Override
	    public void handleNotification(Notification notification,
		Object handback) {

		if (nFilter.isNotificationEnabled(notification)) {
		    ConnectionTreeNode node = (ConnectionTreeNode)handback;
		    fireConnectionFailed(node);
		}
	    }
	};

    private ConnectionListListeners listeners =
        new ConnectionListListeners();

    //
    // ConnectionManager methods
    //

    /**
     * Adds a dependency chain of {@link ConnectionInfo}s and a {@link
     * ConnectionListener} to the dependency tree.  The first element of {@code
     * depChain} is a dependency of {@code listener}.  Each additional element
     * is a dependency of the previous element.
     * <p/>
     * {@code listener} will be notified when the first {@code ConnectionInfo}
     * in the chain {@link ConnectionListener#connectionFailed fails} or {@link
     * ConnectionListener#connectionChanged is replaced}.
     * <p/>
     * {@code listener} and {@code depChain} are merged into the tree if any
     * element thereof already exists in the tree.
     *
     * @param	    listener
     *		    a {@link ConnectionListener} utilizing the first
     *		    {@code ConnectionInfo} in {@code depChain}
     *
     * @param	    depChain
     *		    the {@link ConnectionInfo} dependency chain
     *
     * @throws	    IllegalStateException
     *		    if the given dependency chain conflicts with the existing
     *		    dependency tree
     */
    public synchronized void add(ConnectionListener listener,
	List<ConnectionInfo> depChain) {

	if (depChain.isEmpty()) {
	    return;
	}

	DependencyTreeNode parent = root;
	for (int last = depChain.size() - 1, i = last; i >= 0; i--) {
	    ConnectionInfo info = depChain.get(i);
	    DependencyTreeNode node = getNode(info);

	    if (node != null) {
                DependencyTreeNode oldParent =
		    (DependencyTreeNode)node.getParent();
		if (oldParent != parent) {
		    if (parent == root) {
			parent = oldParent;
		    } else if (oldParent != root) {
                        // If this connection already depends on a connection
                        // other than the next one in depChain...
			throw new IllegalStateException(String.format(
			    "\"%s\" should depend on \"%s\" but already " +
			    "depends on \"%s\"", info,
			    ((ConnectionTreeNode)parent).getUserObject(),
			    ((ConnectionTreeNode)oldParent).getUserObject()));
		    } else {
			if (parent.isNodeAncestor(node)) {
			    throw new IllegalStateException(String.format(
				"\"%s\" should depend on \"%s\" but " +
				"existing dependencies are reversed", info,
				((ConnectionTreeNode)parent).
				getUserObject()));
			}

			parent.add(node);
		    }
		}

		parent = node;
		continue;
	    }

	    node = new ConnectionTreeNode(info);

	    info.getConnector().addConnectionNotificationListener(
		nListener, nFilter, node);

	    parent.add(node);
	    fireAddEvent(info);
	    parent = node;

	    // Does this new connection replace one or more failed connections?
	    for (ConnectionTreeNode failed : getFailed()) {
		if (failed.getUserObject().matches(info)) {
		    ConnectionEvent event = null;

		    // Adopt failed node's dependants and notify them of change
		    for (TreeNode child : failed.getChildren()) {
			node.add((MutableTreeNode)child);

			if (child instanceof ListenerTreeNode) {
			    if (event == null) {
				event = new ConnectionEvent(
				    this, info, failed.getUserObject());
			    }

			    ((ListenerTreeNode)child).getUserObject().
				connectionChanged(event);
			}
		    }

		    remove(failed);
		}
	    }
	}

        // Listener could be at the end of multiple dependency chains.  Ensure
        // that it is listening to the first connection in depChain.
	ListenerTreeNode node = getChild(parent, listener);
	if (node == null) {
	    node = new ListenerTreeNode(listener);
	    parent.add(node);
	}

	fireSelectedEvent(depChain.get(0));
    }

    /**
     * Adds a {@code ConnectionListListener} to notification.
     */
    public synchronized void addConnectionListListener(
	ConnectionListListener listener) {

	listeners.add(listener);
    }

    /**
     * Gets a dependency chain of {@link ConnectionInfo}s, with the first
     * element healthy and matching the given connection parameters, or {@code
     * null} if no healthy matching {@code ConnectionInfo} exists.
     */
    public synchronized List<ConnectionInfo> getDepChain(String host,
        String user, String role, String zone, String zoneUser, String zoneRole)
    {
	for (DependencyTreeNode node : nodeMap.values()) {
	    if (node instanceof ConnectionTreeNode) {
		ConnectionTreeNode cNode = (ConnectionTreeNode)node;
		ConnectionInfo info = cNode.getUserObject();
                if (cNode.isHealthy() && info.matches(host, user, role, zone,
		    zoneUser, zoneRole)) {
		    List<ConnectionInfo> depChain =
			new LinkedList<ConnectionInfo>();

		    for (TreeNode n = node; n != root; n = n.getParent()) {
			depChain.add(((ConnectionTreeNode)n).getUserObject());
		    }

		    return depChain;
		}
	    }
	}
	return null;
    }

    /**
     * Removes {@code listener} as a listener to/dependency of {@code info}.
     * Any connection leaf nodes in the resulting dependency tree will be
     * removed from the tree.
     *
     * @param	    listener
     *		    a {@link ConnectionListener} that depends on {@code info}
     *
     * @param	    info
     *		    the {@link ConnectionInfo} in the dependency tree
     *
     * @throws	    IllegalArgumentException
     *		    if {@code listener} does not depend on {@code info}
     */
    public synchronized void remove(ConnectionListener listener,
	ConnectionInfo info) {

	DependencyTreeNode parent = getNode(info);
	if (parent == null) {
	    throw new IllegalArgumentException(String.format(
		"listener does not depend on \"%s\"", info));
	}

	ListenerTreeNode node = getChild(parent, listener);
	if (node == null) {
	    throw new IllegalArgumentException(String.format(
		"listener does not depend on \"%s\"", info));
	}

	remove(node);
    }

    /**
     * Removes a {@code ConnectionListListener} from notification.
     */
    public synchronized void removeConnectionListListener(
	ConnectionListListener listener) {

	listeners.remove(listener);
    }

    //
    // Private methods
    //

    private synchronized void fireAddEvent(ConnectionInfo info) {
        listeners.connectionAdded(new ConnectionEvent(this, info));
    }

    private synchronized void fireConnectionFailed(ConnectionTreeNode node) {
	node.setHealthy(false);
	ConnectionEvent event = null;

	// Forward to any ConnectionListener dependants
	for (TreeNode child : node.getChildren()) {
	    if (child instanceof ListenerTreeNode) {
		if (event == null) {
		    event = new ConnectionEvent(this, node.getUserObject());
		}
		ConnectionListener listener =
		    ((ListenerTreeNode)child).getUserObject();
		listener.connectionFailed(event);
	    }
	}
    }

    private synchronized void fireRemoveEvent(ConnectionInfo info) {
	listeners.connectionRemoved(new ConnectionEvent(this, info));
    }

    private synchronized void fireSelectedEvent(ConnectionInfo info) {
	listeners.connectionSelected(new ConnectionEvent(this, info));
    }

    /**
     * Returns the dependent child {@code ListenerTreeNode} of {@code node} for
     * the given {@code listener}, {@code null} if none is found.
     */
    private ListenerTreeNode getChild(DependencyTreeNode<?> parent,
	ConnectionListener listener) {

	for (DependencyTreeNode child : parent.getChildren()) {
	    if (child instanceof ListenerTreeNode &&
		child.getUserObject() == listener) {
		return (ListenerTreeNode)child;
	    }
	}

	return null;
    }

    private synchronized List<ConnectionTreeNode> getFailed() {
	List<ConnectionTreeNode> list = new LinkedList<ConnectionTreeNode>();
	for (DependencyTreeNode node : nodeMap.values()) {
	    if (node instanceof ConnectionTreeNode) {
		ConnectionTreeNode cNode = (ConnectionTreeNode)node;
		if (!cNode.isHealthy()) {
		    list.add(cNode);
		}
	    }
	}
	return list;
    }

    private synchronized DependencyTreeNode getNode(Object userObj) {
	for (Map.Entry<Object, DependencyTreeNode> entry : nodeMap.entrySet()) {
	    Object key = entry.getKey();
	    if (key == userObj) {
		return entry.getValue();
	    }
	}
	return null;
    }

    private synchronized void remove(DependencyTreeNode<?> node) {
	for (DependencyTreeNode child : node.getChildren()) {
	    remove(child);
	}

	if (node instanceof ConnectionTreeNode) {
	    ConnectionInfo info = ((ConnectionTreeNode)node).getUserObject();
	    try {
		info.getConnector().removeConnectionNotificationListener(
		    nListener);
	    } catch (ListenerNotFoundException ignore) {
	    }
	}

	DependencyTreeNode<?> parent = (DependencyTreeNode)node.getParent();
	parent.remove(node);

	if (node instanceof ConnectionTreeNode) {
	    ConnectionInfo info = ((ConnectionTreeNode)node).getUserObject();
	    fireRemoveEvent(info);
	}

	if (parent != root && parent.getChildCount() == 0) {
	    remove(parent);
	}
    }
}
