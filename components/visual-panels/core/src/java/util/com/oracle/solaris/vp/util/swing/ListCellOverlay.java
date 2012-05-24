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

package com.oracle.solaris.vp.util.swing;

import java.awt.*;
import java.awt.event.*;
import java.beans.*;
import java.util.*;
import java.util.List;
import javax.swing.*;
import javax.swing.Timer;
import javax.swing.event.*;
import com.oracle.solaris.vp.util.misc.CollectionUtil;

/**
 * The {@code ListCellOverlay} class provides an overlay over each cell in a
 * {@code JList}.  This overlay extends the cell to its preferred size so that
 * the user can see the entire contents of a cell that is partially hidden
 * within a scroll pane or is sized smaller than its preferred size.
 * <br/>
 * This class assumes that the {@code JList} is contained within a {@code
 * JScrollPane}; the overlay is styled to complement that scroll pane.
 * <br/>
 * The {@link #getOverlayComponent overlay component} or the {@link
 * #getOverlayScrollPane scroll pane} that contains it may be changed visually
 * (custom borders, background color, etc.) to affect the look of the overlay.
 */
public class ListCellOverlay {
    //
    // Enums
    //

    public enum Style {
	SINGLE_POPUP, MULTI_POPUP
    }

    //
    // Inner classes
    //

    private static abstract class CellPanel extends JPanel {
	//
	// Instance data
	//

	private CellRendererPane rPane = new CellRendererPane();

	//
	// Constructors
	//

	public CellPanel() {
	    setLayout(null);
	    add(rPane);
	}

	//
	// Component methods
	//

	@Override
	public Dimension getPreferredSize() {
	    Dimension d = getRendererComponentPreferredSize();
	    Insets insets = getInsets();
	    d.width += insets.left + insets.right;
	    d.height += insets.top + insets.bottom;

	    return d;
	}

	//
	// JComponent methods
	//

	@Override
	public void paintComponent(Graphics g) {
	    super.paintComponent(g);

	    Component comp = getRendererComponent();

	    Insets insets = getInsets();
	    int x = insets.left;
	    int y = insets.top;
	    int width = getWidth() - insets.left - insets.right;
	    int height = getHeight() - insets.top - insets.bottom;

	    rPane.paintComponent(g, comp, this, x, y, width, height, true);
	}

	//
	// CellPanel methods
	//

	public abstract Component getRendererComponent();

	public Dimension getRendererComponentPreferredSize() {
	    return getRendererComponent().getPreferredSize();
	}
    }

    private class SimpleCellPanel extends CellPanel {
	//
	// Instance data
	//

	private Component comp;

	//
	// Constructors
	//

	public SimpleCellPanel(Component comp) {
	    this.comp = comp;

	    MouseAdapter listener =
		new MouseAdapter() {
		    //
		    // MouseListener methods
		    //

		    @Override
		    public void mouseClicked(MouseEvent e) {
			GUIUtil.propagate(e, list);
		    }

		    @Override
		    public void mouseExited(MouseEvent e) {
			configurePopups(e);
		    }

		    @Override
		    public void mousePressed(MouseEvent e) {
			GUIUtil.propagate(e, list);
		    }

		    @Override
		    public void mouseReleased(MouseEvent e) {
			GUIUtil.propagate(e, list);
		    }

		    //
		    // MouseMotionListener methods
		    //

		    @Override
		    public void mouseDragged(MouseEvent e) {
			GUIUtil.propagate(e, list);
		    }

		    @Override
		    public void mouseMoved(MouseEvent e) {
			GUIUtil.propagate(e, list);
		    }

		    //
		    // MouseWheelListener methods
		    //

		    @Override
		    public void mouseWheelMoved(MouseWheelEvent e) {
			if (listScroll != null) {
			    GUIUtil.propagate(e, listScroll);
			}
		    }
		};

	    addMouseListener(listener);
	    addMouseMotionListener(listener);
	    addMouseWheelListener(listener);
	}

	//
	// CellPanel methods
	//

	@Override
	public Component getRendererComponent() {
	    return comp;
	}
    }

    //
    // Static data
    //

    /**
     * The initial delay after hovering over the list before an overlay appears.
     */
    public static final int DELAY = 0;

    //
    // Instance data
    //

    // Set to true to paint each overlay rectangle with a solid color
    private boolean debug = false;

    private JList list;
    private JScrollPane listScroll;

    private CellPanel panel;
    private JScrollPane panelScroll;
    private Map<Popup, CellPanel> popups = new HashMap<Popup, CellPanel>();
    private Timer timer;

    private int index = -1;
    private boolean enabled = true;
    private Style style = Style.MULTI_POPUP;

    private ListDataListener listModelListener =
	new ListDataListener() {
	    @Override
	    public void contentsChanged(ListDataEvent e) {
		repaintPopups();
	    }

	    @Override
	    public void intervalAdded(ListDataEvent e) {
		repaintPopups();
	    }

	    @Override
	    public void intervalRemoved(ListDataEvent e) {
		hidePopups();
	    }
	};

    //
    // Constructors
    //

    public ListCellOverlay(final JList list) {
	this.list = list;

	panel = new CellPanel() {
	    @Override
	    public Component getRendererComponent() {
		Object value = list.getModel().getElementAt(index);
		boolean isSelected = list.isSelectedIndex(index);
		boolean hasFocus = list.hasFocus() &&
		    (index == list.getLeadSelectionIndex());

		return list.getCellRenderer().getListCellRendererComponent(
		    list, value, index, isSelected, hasFocus);
	    }

	    @Override
	    public Dimension getRendererComponentPreferredSize() {
		Dimension d = super.getRendererComponentPreferredSize();

		Rectangle r = list.getCellBounds(index, index);
		d.width = Math.max(d.width, r.width);
		d.height = Math.max(d.height, r.height);

		return d;
	    }
	};

	panel.setOpaque(true);
	panel.setBackground(list.getBackground());

	panelScroll = new JScrollPane();

	timer = new Timer(DELAY,
	    new ActionListener() {
		@Override
		public void actionPerformed(ActionEvent e) {
		    for (Popup popup : popups.keySet()) {
			popup.show();
		    }
		}
	    });
	timer.setRepeats(false);

	HierarchyListener listener =
	    new HierarchyListener() {
		@Override
		public void hierarchyChanged(HierarchyEvent e) {
		    listScroll = (JScrollPane)SwingUtilities.getAncestorOfClass(
			JScrollPane.class, list);
		}
	    };
	list.addHierarchyListener(listener);

	// Initialize
	listener.hierarchyChanged(null);

	list.addHierarchyBoundsListener(
	    new HierarchyBoundsListener() {
		@Override
		public void ancestorMoved(HierarchyEvent e) {
		    hidePopups();
		}

		@Override
		public void ancestorResized(HierarchyEvent e) {
		    hidePopups();
		}
	    });

	list.addComponentListener(
	    new ComponentAdapter() {
		@Override
		public void componentMoved(ComponentEvent e) {
		    hidePopups();
		}

		@Override
		public void componentResized(ComponentEvent e) {
		    hidePopups();
		}
	    });

	list.addMouseMotionListener(
	    new MouseMotionAdapter() {
		@Override
		public void mouseMoved(MouseEvent e) {
		    configurePopups(e);
		}
	    });

	list.addMouseListener(
	    new MouseAdapter() {
		@Override
		public void mouseExited(MouseEvent e) {
		    configurePopups(e);
		}
	    });

	list.addListSelectionListener(
	    new ListSelectionListener() {
		@Override
		public void valueChanged(ListSelectionEvent e) {
		    repaintPopups();
		}
	    });

	list.addPropertyChangeListener("model",
	    new PropertyChangeListener() {
		@Override
		public void propertyChange(PropertyChangeEvent e) {
		    modelChanged((ListModel)e.getOldValue(),
			(ListModel)e.getNewValue());
		}
	    });

	// Initialize
	modelChanged(null, list.getModel());
    }

    //
    // ListCellOverlay methods
    //

    /**
     * Gets the initial delay after hovering over the list before an overlay of
     * a cell appears.
     */
    public int getDelay() {
	return timer.getInitialDelay();
    }

    /**
     * Gets whether this {@code ListCellOverlay} is enabled.
     */
    public boolean getEnabled() {
	return enabled;
    }

    public JList getList() {
	return list;
    }

    /**
     * Gets the {@code JComponent} that is displays the cell renderer in the
     * overlay.  This {@code JComponent} can be customized with a border, a
     * change in background color, etc.
     */
    public JComponent getOverlayComponent() {
	return panel;
    }

    /**
     * Gets the {@code JScrollPane} containing the {@link #getOverlayComponent
     * overlay component}.  This provides a border that (presumably) matches the
     * one surrounding the list.
     */
    public JScrollPane getOverlayScrollPane() {
	return panelScroll;
    }

    /**
     * Gets the style to use when displaying the overlay.
     */
    public Style getStyle() {
	return style;
    }

    /**
     * Sets the style to use when displaying the overlay. {@link
     * Style#SINGLE_POPUP} uses a single, tooltip-like popup, complete with
     * borders, as the overlay.  {@link Style#MULTI_POPUP} uses multiple popups
     * to make it appear as though the scroll pane that encloses the list
     * changes shape to accommodate the overlay.  The latter style may appear
     * more polished, but the former has a lesser performance hit.  The default
     * value is {@link Style#MULTI_POPUP}.
     */
    public void setStyle(Style style) {
	this.style = style;
    }

    /**
     * Sets the initial delay after hovering over the list before an overlay of
     * a cell appears.
     */
    public void setDelay(int delay) {
	timer.setInitialDelay(delay);
    }

    /**
     * Gets whether this {@code ListCellOverlay} is enabled.
     */
    public void setEnabled(boolean enabled) {
	if (this.enabled != enabled) {
	    if (!enabled) {
		hidePopups();
	    }
	    this.enabled = enabled;
	}
    }

    //
    // Private methods
    //

    private void configurePopups(MouseEvent e) {
	if (!enabled || listScroll == null) {
	    return;
	}

	Rectangle cellRect = null;
	int index;

	Point listScrollPoint = SwingUtilities.convertPoint(
	    e.getComponent(), e.getPoint(), listScroll);

	// Is the point visible?
	if (!listScroll.contains(listScrollPoint)) {
	    index = -1;
	} else {
	    Point listPoint = SwingUtilities.convertPoint(
		listScroll, listScrollPoint, list);

	    index = list.locationToIndex(listPoint);
	    if (index != -1) {
		cellRect = list.getCellBounds(index, index);
		if (!cellRect.contains(listPoint)) {
		    // The point is not actually in a list cell
		    index = -1;
		}
	    }
	}

	// Has the index of the overlaid cell changed?
	if (this.index != index) {
	    hidePopups();

	    if (index != -1) {
		this.index = index;

		if (isCellObscured()) {
		    // We now need to figure out where to place popup windows
		    // (containing scroll, which contains panel, which paints
		    // the cell renderer) so that the cell renderer within the
		    // popups aligns with the cell renderer in the list.

		    // The size of the panel scroll pane border
		    // (panelScroll.getInsets() doesn't work under some L&Fs
		    // (like synth), so we are forced to do a layout and compare
		    // points)
		    panelScroll.setViewportView(panel);
		    panelScroll.doLayout();
		    Point panelScrollInsets = SwingUtilities.convertPoint(
			panel, 0, 0, panelScroll);

		    // The size of the panel border
		    Insets panelInsets = panel.getInsets();

		    if (cellRect == null) {
			cellRect = list.getCellBounds(index, index);
		    }

		    Dimension panelScrollPrefSize =
			panelScroll.getPreferredSize();

		    // The bounds of the panel scroll pane in list coordinates
		    Rectangle panelScrollBounds = new Rectangle(
			cellRect.x - panelInsets.left - panelScrollInsets.x,
			cellRect.y - panelInsets.top - panelScrollInsets.y,
			panelScrollPrefSize.width, panelScrollPrefSize.height);

		    // Convert to the list scroll pane's coordinates
		    panelScrollBounds = SwingUtilities.convertRectangle(
			list, panelScrollBounds, listScroll);

		    List<Rectangle> rectList = new ArrayList<Rectangle>();

		    switch (style) {
			case SINGLE_POPUP:
			    rectList.add(panelScrollBounds);
			    break;

			default:
			case MULTI_POPUP:
			    // The bounds of the list viewport in the list
			    // scroll pane's coordinates
			    Rectangle listViewBounds =
				listScroll.getViewport().getBounds();

			    Rectangle[] rects =
				SwingUtilities.computeDifference(
				panelScrollBounds, listViewBounds);

			    CollectionUtil.addAll(rectList, rects);

			    // Convert to the list scroll pane's coordinates
			    cellRect = SwingUtilities.convertRectangle(
				list, cellRect, listScroll);

			    // Now add one more rect to cover the visible area
			    // of the cell entirely.  This is necessary because
			    // the renderer may be drawing its content truncated
			    // (ie. "Foo bar..."), and we need it to be drawn at
			    // full size.
			    rectList.add(cellRect);
		    }

		    Point listScrollScreenPoint =
			listScroll.getLocationOnScreen();

		    for (Rectangle rect : rectList) {
			Point point = rect.getLocation();
			point.translate(-panelScrollBounds.x,
			    -panelScrollBounds.y);

			JViewport viewport = new JViewport();
			viewport.setPreferredSize(new Dimension(
			    rect.width, rect.height));

			CellPanel cell = new SimpleCellPanel(panelScroll);

			if (debug) {
			    JLabel label = new JLabel();
			    label.setOpaque(true);
			    label.setBackground(ColorUtil.getRandomColor());
			    cell = new SimpleCellPanel(label);
			}

			viewport.setView(cell);
			viewport.setViewPosition(point);

			int x = rect.x + listScrollScreenPoint.x;
			int y = rect.y + listScrollScreenPoint.y;

			Popup popup = PopupFactory.getSharedInstance().getPopup(
			    list, viewport, x, y);

			popups.put(popup, cell);
		    }

		    timer.restart();
		}
	    }
	}
    }

    private boolean getPopupsShowing() {
	return !popups.isEmpty();
    }

    private void hidePopups() {
	timer.stop();
	index = -1;
	for (Iterator<Popup> i = popups.keySet().iterator(); i.hasNext();) {
	    Popup popup = i.next();
	    popup.hide();
	    i.remove();
	}
	list.repaint();
    }

    private boolean isCellObscured() {
	Rectangle cellRect = list.getCellBounds(index, index);
	Dimension panelSize = panel.getPreferredSize();

	// Is the cell rect smaller than the preferred size?
	if (cellRect.width < panelSize.width ||
	    cellRect.height < panelSize.height) {
	    return true;
	}

	// The bounds of panel at its preferred size, relative to listScroll
	Rectangle panelBounds = SwingUtilities.convertRectangle(list,
	    new Rectangle(cellRect), listScroll);

	Rectangle scrollBounds = new Rectangle(listScroll.getSize());

	return !scrollBounds.contains(panelBounds);
    }

    private void modelChanged(ListModel oldModel, ListModel newModel) {
	if (oldModel != null) {
	    oldModel.removeListDataListener(listModelListener);
	}

	if (newModel != null) {
	    newModel.addListDataListener(listModelListener);
	}
    }

    private void repaintPopups() {
	if (getPopupsShowing()) {
	    for (CellPanel cell : popups.values()) {
		cell.repaint();
	    }
	}
    }
}
