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

package com.oracle.solaris.vp.util.swing;

import java.awt.datatransfer.*;
import java.io.IOException;
import java.util.Arrays;
import javax.swing.*;
import javax.swing.table.TableModel;
import com.oracle.solaris.vp.util.misc.ArrayUtil;

@SuppressWarnings({"serial"})
public class EditableTableTransferHandler extends TransferHandler {
    //
    // Inner classes
    //

    public static class TableRow {
	//
	// Instance data
	//

	public int index;
	public Object[] data;

	// Whether this row was successfully imported or not
	public boolean success = true;

	//
	// Constructors
	//

	public TableRow(int index, Object[] data) {
	    this.index = index;
	    this.data = data;
	}
    }

    public static class TableData {
	//
	// Instance data
	//

	private int tableHashCode;
	private TableRow[] rows;

	//
	// Constructors
	//

	public TableData(int tableHashCode, TableRow[] rows) {
	    this.tableHashCode = tableHashCode;
	    this.rows = rows;
	}

	//
	// TableData methods
	//

	public int getTableHashCode() {
	    return tableHashCode;
	}

	public TableRow[] getRows() {
	    return rows;
	}
    }

    public class EditableTableTransferable implements Transferable {
	//
	// Instance data
	//

	private TableData data;

	//
	// Constructors
	//

	public EditableTableTransferable(TableData data) {
	    this.data = data;
	}

	//
	// Transferable methods
	//

	@Override
	public Object getTransferData(DataFlavor flavor)
	    throws UnsupportedFlavorException {

	    if (!isDataFlavorSupported(flavor)) {
		throw new UnsupportedFlavorException(flavor);
	    }

	    return data;
	}

	@Override
	public DataFlavor[] getTransferDataFlavors() {
	    return new DataFlavor[] {
		localFlavor, serialFlavor
	    };
	}

	@Override
	public boolean isDataFlavorSupported(DataFlavor flavor) {
	    return localFlavor.equals(flavor) || serialFlavor.equals(flavor);
	}
    }

    //
    // Static data
    //

    protected static DataFlavor localFlavor;
    static {
	String localType = DataFlavor.javaJVMLocalObjectMimeType +
	    ";class=\"" + TableData.class.getName() + "\"";

	try {
	    localFlavor = new DataFlavor(localType);
	} catch (ClassNotFoundException ignore) {
	}
    }

    protected static final DataFlavor serialFlavor =
	new DataFlavor(TableData.class, "TableData");

    //
    // TransferHandler methods
    //

    @Override
    public boolean canImport(JComponent c, DataFlavor[] flavors) {
	return c instanceof JTable &&
	    ((JTable)c).getModel() instanceof EditableTableModel &&
	    (hasLocalFlavor(flavors) || hasSerialFlavor(flavors));
    }

    @Override
    protected Transferable createTransferable(JComponent c) {
	EditableTableTransferable transferable = null;

	if (c instanceof JTable) {
	    JTable table = (JTable)c;
	    int[] selectedRows = table.getSelectedRows();

	    if (selectedRows.length != 0) {

		int nCols = table.getColumnCount();
		if (nCols != 0) {

		    Arrays.sort(selectedRows);
		    TableModel model = table.getModel();
		    TableRow[] rows = new TableRow[selectedRows.length];

		    for (int i = 0; i < selectedRows.length; i++) {
			int row = selectedRows[i];
			Object[] data = new Object[nCols];

			for (int col = 0; col < nCols; col++) {
			    data[col] = model.getValueAt(row, col);
			}

			rows[i] = new TableRow(row, data);
		    }

		    transferable = new EditableTableTransferable(
			new TableData(table.hashCode(), rows));
		}
	    }
	}

	return transferable;
    }

    @Override
    protected void exportDone(JComponent c, Transferable t, int action) {
	if (action == MOVE) {

	    if (c instanceof JTable) {
		JTable table = (JTable)c;

		DataFlavor[] flavors = t.getTransferDataFlavors();

		DataFlavor flavor = null;
		if (hasLocalFlavor(flavors)) {
		    flavor = localFlavor;
		} else if (hasSerialFlavor(flavors)) {
		    flavor = serialFlavor;
		}

		if (flavor != null) {
		    try {
			TableData data = (TableData)t.getTransferData(flavor);
			TableRow[] rows = data.getRows();
			TableModel model = table.getModel();
			if (model instanceof EditableTableModel) {
			    EditableTableModel editModel =
				(EditableTableModel)model;

			    for (int i = rows.length - 1; i >= 0; i--) {
				TableRow row = rows[i];
				if (row.success) {
				    editModel.removeRow(row.index);
				}
			    }
			}

		    // Thrown by getTransferData
		    } catch (IOException e) {

		    // Thrown by getTransferData
		    } catch (UnsupportedFlavorException e) {
		    }
		}
	    }
	}
    }

    @Override
    public int getSourceActions(JComponent c) {
	return COPY_OR_MOVE;
    }

    @Override
    public boolean importData(JComponent c, Transferable t) {
	boolean dropped = false;

	if (c instanceof JTable) {

	    JTable target = (JTable)c;
	    DataFlavor[] flavors = t.getTransferDataFlavors();

	    DataFlavor flavor = null;
	    if (hasLocalFlavor(flavors)) {
		flavor = localFlavor;
	    } else if (hasSerialFlavor(flavors)) {
		flavor = serialFlavor;
	    }

	    if (flavor != null) {
		JTable.DropLocation dropLoc = target.getDropLocation();

		if (dropLoc != null) {
		    int insertRow = dropLoc.getRow();

		    try {
			TableData data = (TableData)t.getTransferData(flavor);
			TableRow[] rows = data.getRows();

			// Is the source table the same as the target table?
			boolean isSame = flavor == localFlavor &&
			    data.getTableHashCode() == target.hashCode();

			// Rows cannot be dropped onto any row in selected range
			// if the source and target are the same table
			if (!isSame || insertRow <= rows[0].index ||
			    insertRow > rows[rows.length -1].index) {

			    TableModel model = target.getModel();
			    if (model instanceof EditableTableModel) {
				EditableTableModel editModel =
				    (EditableTableModel)model;

				int selectStart = insertRow;

				for (TableRow row : rows) {
				    row.success = editModel.attemptInsertRow(
					insertRow, row.data);

				    if (row.success) {
					if (isSame) {
					    for (TableRow r : rows) {
						if (r.index >= insertRow) {
						    r.index++;
						}
					    }
					}
					insertRow++;
				    }
				}

				int selectEnd = insertRow - 1;

				if (selectEnd >= selectStart) {
				    target.setRowSelectionInterval(
					selectStart, selectEnd);
				}

				target.requestFocusInWindow();

				dropped = true;
			    }
			}

		    // Thrown by getTransferData
		    } catch (IOException e) {

		    // Thrown by getTransferData
		    } catch (UnsupportedFlavorException e) {
		    }
		}
	    }
	}

	return dropped;
    }

    //
    // Private methods
    //

    private boolean hasLocalFlavor(DataFlavor[] flavors) {
	return ArrayUtil.indexOf(flavors, localFlavor) != -1;
    }

    private boolean hasSerialFlavor(DataFlavor[] flavors) {
	return ArrayUtil.indexOf(flavors, serialFlavor) != -1;
    }
}
