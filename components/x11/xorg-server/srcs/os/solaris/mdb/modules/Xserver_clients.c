/*
 * Copyright (c) 2004, 2012, Oracle and/or its affiliates. All rights reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */


#include <sys/mdb_modapi.h>
#include <sys/procfs.h>
#include "Xserver_mdb.h"

#include "xorg-server.h"
#include "dixstruct.h"
#include "misc.h"
#include "client.h"
#include "os/osdep.h"
#include "IA/interactive_srv.h"

struct client_walk_data {
    uintptr_t client_next;
    uintptr_t clients_end;
    ClientRec client_data;
};

/* Just here to satisfy linkage from inlines in privates.h
   Should never ever be called from the module. */
_X_HIDDEN DevPrivateKey
_dixGetScreenPrivateKey(const DevScreenPrivateKey key, ScreenPtr pScreen)
{
    abort();
    return NULL; /* compiler whines about not returning a value after abort() */
}


/*
 * Initialize the client walker by either using the given starting address,
 * or reading the value of the server's "clients" pointer.  We also allocate
 * a  for storage, and save this using the walk_data pointer.
 */
_X_HIDDEN int
client_walk_init(mdb_walk_state_t *wsp)
{
    struct client_walk_data *cwda;
    short max_clients = MAXCLIENTS;

# define CUR_MAX_CLIENTS "currentMaxClients"

    if (wsp->walk_addr == NULL) {
       /* Xorg 1.6 - clients is the array itself */
       GElf_Sym clients_sym;
       if (mdb_lookup_by_name("clients", &clients_sym) == -1) {
	   mdb_warn("failed to lookup 'clients'");
	   return (WALK_ERR);
       }
       wsp->walk_addr = clients_sym.st_value;
       if (mdb_readvar(&max_clients, CUR_MAX_CLIENTS) == -1) {
	   mdb_warn("failed to read '%s'", CUR_MAX_CLIENTS);
	   return (WALK_ERR);
       } else {
	   mdb_printf("%s = %d\n", CUR_MAX_CLIENTS, max_clients);
       }
    }

    wsp->walk_data = mdb_alloc(sizeof (struct client_walk_data), UM_SLEEP);
    cwda = (struct client_walk_data *) wsp->walk_data;
    cwda->clients_end = wsp->walk_addr + (max_clients * (sizeof(void *)));
    return (WALK_NEXT);
}

/*
 * At each step, read a client struct into our private storage, and then invoke
 * the callback function.  We terminate when we reach the end of the clients
 * array.
 */
_X_HIDDEN int
client_walk_step(mdb_walk_state_t *wsp)
{
	int status;
	uintptr_t clientPtr;
	struct client_walk_data *cwda =
	  (struct client_walk_data *) wsp->walk_data;

	if (wsp->walk_addr == NULL)
		return (WALK_DONE);

	do {
	    if (mdb_vread(&clientPtr, sizeof (void *), wsp->walk_addr) == -1) {
		mdb_warn("failed to read client table entry at %p", wsp->walk_addr);
		return (WALK_DONE);
	    }
	    if (clientPtr == NULL) {
#ifdef DEBUG
		mdb_printf("NULL entry at %p", wsp->walk_addr);
#endif
		wsp->walk_addr += sizeof(void *);
	    }
	    if (wsp->walk_addr >= cwda->clients_end) {
#ifdef DEBUG
		mdb_printf("End of client list at %p", cwda->clients_end);
#endif
		return (WALK_DONE);
	    }
	} while (clientPtr == NULL);

	if (clientPtr == NULL) {
	    return (WALK_DONE);
	}

	if (mdb_vread(&(cwda->client_data), sizeof (ClientRec), (uintptr_t) clientPtr) == -1) {
		mdb_warn("failed to read client data at %p", wsp->walk_addr);
		return (WALK_DONE);
	}

	status = wsp->walk_callback(wsp->walk_addr, &(cwda->client_data),
	  wsp->walk_cbdata);

	wsp->walk_addr = wsp->walk_addr + sizeof(void *);
	return (status);
}

/*
 * The walker's fini function is invoked at the end of each walk.  Since we
 * dynamically allocated a proc_t in client_walk_init, we must free it now.
 */
_X_HIDDEN void
client_walk_fini(mdb_walk_state_t *wsp)
{
	mdb_free(wsp->walk_data, sizeof (ClientRec));
}

_X_HIDDEN void
client_pids_help(void)
{
    mdb_printf(
	"Prints information about a ClientRec entry in the X server's array\n"
	"of currently connected X clients.  Prints process pid and name that\n"
	"was recorded at connection time for each client, if available.\n"
	"\n"
	"If no %<u>addr%</u> is specified, uses ::client_walk to walk the linked list\n"
	"of ClientRec entries stored in the global array \"clients\" and print\n"
	"information about each one.\n"
	"\n");
    (void) mdb_dec_indent(2);
    mdb_printf("%<b>OPTIONS%</b>\n");
    (void) mdb_inc_indent(2);
    mdb_printf(
	"-w\tPrint arguments with process name when available.\n");
}

_X_HIDDEN int
client_pids(uintptr_t addr, uint_t flags, int argc, const mdb_arg_t *argv)
{
    uintptr_t clientP;
    ClientRec client_data;
    uint_t show_cmd_args = FALSE;

    if (mdb_getopts(argc, argv,
		    'w', MDB_OPT_SETBITS, TRUE, &show_cmd_args,
		    NULL) != argc)
	return (DCMD_USAGE);

    /*
     * If no client address was specified on the command line, we can
     * print out all clients by invoking the walker, using this
     * dcmd itself as the callback.
     */
    if (!(flags & DCMD_ADDRSPEC)) {
	if (mdb_walk_dcmd("client_walk", "client_pids",
			  argc, argv) == -1) {
	    mdb_warn("failed to walk 'client_walk'");
	    return (DCMD_ERR);
	}
	return (DCMD_OK);
    }

    /*
     * If this is the first invocation of the command, print a nice
     * header line for the output that will follow.
     */
    if (DCMD_HDRSPEC(flags))
	mdb_printf("CLIENT SEQUENCE #   FD  PROCESS\n");


    if (mdb_vread(&clientP, sizeof (clientP), addr) != sizeof (clientP)) {
	mdb_warn("failed to read ClientPtr at %p", addr);
    } else {
	if (mdb_vread(&client_data, sizeof (client_data), clientP)
	    != sizeof (client_data)) {
	    mdb_warn("failed to read ClientRec at %p", clientP);
	} else {
	    int client_pid = -1;

	    mdb_printf("%5d  %10d ", client_data.index, client_data.sequence);

	    /* Find file descriptor for this client */
	    if (client_data.osPrivate != NULL) {
		OsCommRec oscomm;
	    
		if (mdb_vread(&oscomm, sizeof (oscomm),
			      (uintptr_t)client_data.osPrivate)
		    != sizeof (oscomm)) {
		    mdb_warn("failed to read struct OsCommRec at %p",
			     client_data.osPrivate);
		} else {
		    mdb_printf("%4d ", oscomm.fd);
		}
	    } else {
		mdb_printf("NULL ");
	    }

	    /* Find client pid & cmd recorded on connection setup by
	       Xorg 1.11 and later */
	    if (client_data.clientIds != NULL) {
		ClientIdRec cir;

		if (mdb_vread(&cir, sizeof (cir),
			      (uintptr_t)client_data.clientIds)
		    != sizeof (cir)) {
		    mdb_warn("failed to read struct ClientIdRec at %p",
			     client_data.clientIds);
		} else {
		    char cmd[PRARGSZ];

		    if (mdb_readstr(cmd, sizeof(cmd),
				    (uintptr_t)cir.cmdname) == -1) {
			mdb_warn("failed to read cmdname at %p", cir.cmdname);
			cmd[0] = '\0';
		    }
		    mdb_printf("%6d %s", cir.pid, cmd);
		    client_pid = cir.pid;
		    if (show_cmd_args && (cir.cmdargs != NULL)) {
			if (mdb_readstr(cmd, sizeof(cmd),
					(uintptr_t)cir.cmdargs) == -1) {
			    mdb_warn("failed to read cmdargs at %p",
				     cir.cmdargs);
			    cmd[0] = '\0';
			}
			mdb_printf(" %s\n", cmd);
		    } else {
			mdb_printf("\n", cmd);
		    }
		}
	    } else {
		mdb_printf(" ???? - NULL ClientPtr->clientIds\n");
	    }
	    
	    /* Check to see if any additional pids were registered
	       with SolarisIA extension. */
	    static GElf_Sym iaprivkey_sym;

	    if ((iaprivkey_sym.st_value == 0) &&
		(mdb_lookup_by_obj("libia.so", "IAPrivKeyRec", &iaprivkey_sym)
		 == -1)) {
		mdb_warn("failed to lookup 'libia.so`IAPrivKeyRec'");
	    }

	    if (iaprivkey_sym.st_value != 0) {
		ClientProcessPtr cpp = NULL;
		DevPrivateKeyRec IAPrivKeyRec;

		if (mdb_vread(&IAPrivKeyRec, sizeof(DevPrivateKeyRec),
			      iaprivkey_sym.st_value)
		    != sizeof(DevPrivateKeyRec)) {
		    mdb_warn("failed to read 'IAPrivKeyRec'");
		} else if (!IAPrivKeyRec.initialized) {
		    mdb_warn("IAPrivKeyRec is uninitialized");
		} else {
		    uintptr_t dpaddr =	((uintptr_t)client_data.devPrivates)
			+ IAPrivKeyRec.offset;
		    uintptr_t cppaddr = (uintptr_t) NULL;

		    /*
		     * ClientProcessPtr is the first entry in the
		     * IAClientPrivatePtr that devPrivates points to
		     */
		    if (mdb_vread(&cppaddr, sizeof (cppaddr), dpaddr)
			!= sizeof (cppaddr)) {
			mdb_warn("failed to read "
				 " client_data.devPrivates+offset");
		    } else if (cppaddr == NULL) {
			/*
			 * if osPrivate is NULL, client connection is closed,
			 * and it's no surprise we can't find ClientProcessPtr
			 */
			if (client_data.osPrivate != NULL)
			    mdb_warn("no ClientProcessPtr found");
		    } else if (mdb_vread(&cpp, sizeof (cpp), cppaddr)
			       != sizeof (cpp)) {
			cpp = NULL;
			mdb_warn("failed to read IAClientPrivatePtr");
		    }
		}

		if (cpp != NULL) {
		    ClientProcessRec cpr;
		    ConnectionPidRec pid;

		    if (mdb_vread(&cpr, sizeof (cpr), (uintptr_t)cpp)
			!= sizeof (cpr)) {
			mdb_warn("failed to read struct ClientProcessRec"
				 " at %p", client_data.osPrivate);
		    } else {
			int i, num_printed = 0;
			uintptr_t pidP = (uintptr_t) cpr.pids;

			for (i = 0; i < cpr.count; i++, pidP += sizeof(pid)) {
			    if (mdb_vread(&pid, sizeof (pid), pidP)
				== sizeof (pid)) {
				if (pid != client_pid) {
				    if (num_printed == 0)
					mdb_printf("%22s", "+");
				    num_printed++;
				    mdb_printf(" %6d", pid);
				}
			    } else {
				mdb_warn("failed to read pid #%d from %p",
					 i, pidP);
			    }
			}
			if (num_printed != 0)
			    mdb_printf("\n");
		    }
		}
	    }
	}
    }

    return (DCMD_OK);
}
