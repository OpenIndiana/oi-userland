/*
 *
 * mkcookie.c 1.x
 *
 * Copyright (c) 1990, 2015, Oracle and/or its affiliates. All rights reserved.
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
 *
 */

/*
 * $XConsortium: auth.c,v 1.17 89/12/14 09:42:18 rws Exp $
 *
 * Copyright 1988 Massachusetts Institute of Technology
 *
 * Permission to use, copy, modify, and distribute this software and its
 * documentation for any purpose and without fee is hereby granted, provided
 * that the above copyright notice appear in all copies and that both that
 * copyright notice and this permission notice appear in supporting
 * documentation, and that the name of M.I.T. not be used in advertising or
 * publicity pertaining to distribution of the software without specific,
 * written prior permission.  M.I.T. makes no representations about the
 * suitability of this software for any purpose.  It is provided "as is"
 * without express or implied warranty.
 *
 * Author:  Keith Packard, MIT X Consortium
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <sys/sockio.h>
#include <netinet/in.h>
#include <net/if.h>
#include <netdb.h>
#include <X11/X.h>
#include <X11/Xauth.h>
#include <X11/Xos.h>
#include <rpc/rpc.h>
#include <sys/random.h>

#define AUTH_DATA_LEN       16      /* bytes of MIT-MAGIC-COOKIE data */
#define DEF_USER_AUTH_DIR   "/tmp"  /* Backup directory for User Auth file */

static void setAuthNumber(Xauth *auth, const char *name);
static void DefineLocal(FILE *file, Xauth *auth);
static void DefineSelf(int fd, FILE *file, Xauth *auth);
static void writeAuth(FILE *file, Xauth *auth);
static void GenerateCryptoKey(char *auth, int len);

struct display {
    char *      name;           /* DISPLAY name */
    Xauth *     authorization;  /* authorization data */
    char *      authFile;       /* file to store authorization in */
    const char *userAuthDir;    /* backup directory for tickets */
    const char *authName;       /* authorization protocol name */
};

struct verify_info {
    uid_t       uid;            /* user id */
    gid_t       gid;            /* group id */
};

struct addrList {
    unsigned short      family;
    unsigned short      address_length;
    unsigned short      number_length;
    char *              address;
    char *              number;
    struct addrList *   next;
};

static struct addrList *addrs;

static const char *programName;

/* PRINTFLIKE1 */
static void _X_NORETURN _X_ATTRIBUTE_PRINTF(1, 2)
fatalError(const char *msg, ...)
{
    va_list args;

    fflush(stdout);
    fflush(stderr);
    fprintf(stderr, "%s: error: ", programName);

    va_start(args, msg);
    vfprintf(stderr, msg, args);
    va_end(args);

    fprintf(stderr, "\n");
    exit(EXIT_FAILURE);
}

static int
binaryEqual(const char *a, const char *b, int len)
{
    while (len-- > 0)
        if (*a++ != *b++)
            return 0;
    return 1;
}

#ifdef DEBUG
static void
dumpBytes(int len, const char *data)
{
    int i;

    printf("%d: ", len);
    for (i = 0; i < len; i++)
        printf("%02x ", data[i] & 0377);
    printf("\n");
}

static void
dumpAuth(Xauth *auth)
{
    printf("family: %d\n", auth->family);
    printf("addr:   ");
    dumpBytes(auth->address_length, auth->address);
    printf("number: ");
    dumpBytes(auth->number_length, auth->number);
    printf("name:   ");
    dumpBytes(auth->name_length, auth->name);
    printf("data:   ");
    dumpBytes(auth->data_length, auth->data);
}
#endif /* DEBUG */

static int
checkAddr(unsigned short family,
          unsigned short address_length, const char *address,
          unsigned short number_length, const char *number)
{
    struct addrList *a;

    for (a = addrs; a != NULL; a = a->next) {
        if (a->family == family &&
            a->address_length == address_length &&
            binaryEqual(a->address, address, address_length) &&
            a->number_length == number_length &&
            binaryEqual(a->number, number, number_length)) {
            return 1;
        }
    }
    return 0;
}

static void
saveAddr(unsigned short family,
         unsigned short address_length, const char *address,
         unsigned short number_length, const char *number)
{
    struct addrList *new;

    if (checkAddr(family, address_length, address, number_length, number))
        return;
    new = calloc(1, sizeof(struct addrList));
    if (new == NULL) {
        perror("saveAddr");
        return;
    }
    if ((new->address_length = address_length) > 0) {
        new->address = malloc(address_length);
        if (new->address == NULL) {
            goto fail;
        }
        memcpy(new->address, address, (size_t) address_length);
    }
    else
        new->address = NULL;
    if ((new->number_length = number_length) > 0) {
        new->number = malloc(number_length);
        if (new->number == NULL) {
            goto fail;
        }
        memcpy(new->number, number, (size_t) number_length);
    }
    else
        new->number = NULL;
    new->family = family;
    new->next = addrs;
    addrs = new;
    return;

  fail:
    perror("saveAddr");
    free(new->address);
    free(new);
    return;
}

static void
writeLocalAuth(FILE *file, Xauth *auth, const char *name)
{
    int fd;

    setAuthNumber(auth, name);
    fd = socket(PF_INET6, SOCK_STREAM, 0);
    DefineSelf(fd, file, auth);
    close(fd);

    DefineLocal(file, auth);
}

static void
writeAddr(int family, size_t addr_length, char *addr, FILE *file, Xauth *auth)
{
    auth->family = (unsigned short) family;
    auth->address_length = (unsigned short) addr_length;
    auth->address = addr;
#ifdef DEBUG
    printf("--- writeAddr:\n");
    dumpAuth(auth);
#endif
    writeAuth(file, auth);
}

static void
DefineSelf(int fd, FILE *file, Xauth *auth)
{
    char                buf[2048] = { 0 };
    void *              bufptr = buf;
    size_t              len = sizeof(buf);
    char *              addr;
    int                 n;
    int                 family;
    struct lifreq *     ifr;
    struct lifnum       ifn = { .lifn_family = AF_UNSPEC, .lifn_flags = 0 };
    struct lifconf      ifc = { .lifc_family = AF_UNSPEC, .lifc_flags = 0 };

    if (ioctl(fd, (int) SIOCGLIFNUM, &ifn) < 0) {
        perror("Getting interface count");
    }
    else if (len < (ifn.lifn_count * sizeof(struct lifreq))) {
        len = ifn.lifn_count * sizeof(struct lifreq);
        bufptr = malloc(len);
    }

    ifc.lifc_len = (int) len;
    ifc.lifc_buf = bufptr;
    if (ioctl(fd, (int) SIOCGLIFCONF, &ifc) < 0) {
	perror("Getting interface list");
        return;
    }
    for (ifr = ifc.lifc_req, n = ifc.lifc_len / (int) sizeof(struct lifreq);
         --n >= 0; ifr++) {
	struct sockaddr *saddr = (struct sockaddr *) &ifr->lifr_addr;

        switch (saddr->sa_family) {
        case AF_INET:
            /*
             * If we get back a 0.0.0.0 IP address, ignore this entry.
             * This typically happens when a machine is in a standalone mode.
             */
	    addr = (char *) &(((struct sockaddr_in *) saddr)->sin_addr);
            if (addr[0] == 0 && addr[1] == 0 && addr[2] == 0 && addr[3] == 0)
                continue;
	    family = FamilyInternet;
	    len = sizeof(struct in_addr);
            break;

        case AF_INET6:
	    addr = (char *) &(((struct sockaddr_in6 *) saddr)->sin6_addr);
            if (IN6_IS_ADDR_LOOPBACK(((struct in6_addr *) addr)))
                continue;
	    family = FamilyInternet6;
	    len = sizeof(struct in6_addr);
            break;

        default:
            continue;
        }

        writeAddr(family, len, addr, file, auth);
    }
}

static void
DefineLocal(FILE *file, Xauth *auth)
{
    char displayname[MAXHOSTNAMELEN];

    if (gethostname(displayname, sizeof(displayname)) == 0)
        writeAddr(FamilyLocal, strlen(displayname), displayname, file, auth);
    else
        perror("gethostname");
}

static void
setAuthNumber(Xauth *auth, const char *name)
{
    const char *colon;
    const char *dot;
    char *number;

    colon = strrchr(name, ':');
    if (colon) {
        ++colon;
        if ((dot = strchr(colon, '.')))
            auth->number_length = (unsigned short) (dot - colon);
        else
            auth->number_length = (unsigned short) strlen(colon);
        number = malloc(auth->number_length + 1);
        if (number) {
            strncpy(number, colon, auth->number_length);
            number[auth->number_length] = '\0';
        }
        else {
            perror("setAuthNumber");
            auth->number_length = 0;
        }
        auth->number = number;
    }
}

static int
openFiles(const char *name, char *new_name, size_t new_name_size,
          FILE ** oldp, FILE ** newp)
{
    int newfd;

    snprintf(new_name, new_name_size, "%s-n", name);
    (void) remove(new_name);
    newfd = open(new_name, O_WRONLY | O_CREAT | O_EXCL, 0600);
    if (newfd == -1) {
        perror(new_name);
        return 0;
    }
    *newp = fdopen(newfd, "w");
    if (*newp == NULL) {
	perror(new_name);
	close(newfd);
	(void) remove(new_name);
        return 0;
    }
    *oldp = fopen(name, "r");

    return 1;
}

static void
writeAuth(FILE *file, Xauth *auth)
{
    saveAddr(auth->family, auth->address_length, auth->address,
             auth->number_length, auth->number);
    if (!XauWriteAuth(file, auth)) {
        fatalError("Could not write authorization info. for user. exiting");
    }
}

static void
doneAddrs(void)
{
    struct addrList *a, *n;

    for (a = addrs; a != NULL; a = n) {
        n = a->next;
        free(a->address);
        free(a->number);
        free(a);
    }
    addrs = NULL;
}

static Xauth *
GenerateAuthorization(const char *name)
{
    Xauth *new;

    new = calloc(1, sizeof(Xauth));
    if (new == NULL) {
        goto fail;
    }
    new->family = FamilyWild;

    if (strcmp(name, "MIT-MAGIC-COOKIE-1") == 0) {
        new->data = malloc(AUTH_DATA_LEN);
        if (new->data == NULL) {
            goto fail;
        }
        GenerateCryptoKey(new->data, AUTH_DATA_LEN);
        new->data_length = AUTH_DATA_LEN;
    }
    else if (strcmp(name, "SUN-DES-1") == 0) {
        char netname[MAXNETNAMELEN + 1] = "";
        uid_t uid = getuid();

        if (!user2netname(netname, uid, 0)) {
            goto fail;
        }
        new->data = strdup(netname);
        if (new->data == NULL) {
            goto fail;
        }
        new->data_length = (unsigned short) strlen(netname);
    }
    else {
        fprintf(stderr, "%s: unsupported authorization protocol '%s'\n",
                programName, name);
        goto fail;
    }

    new->name = strdup(name);
    if (new->name == NULL) {
        goto fail;
    }
    new->name_length = (unsigned short) strlen(name);
    return new;

  fail:
    perror("GenerateAuthorization");
    if (new != NULL) {
	free(new->data);
	free(new);
    }
    return (Xauth *) NULL;

}

static void
GenerateCryptoKey(char *auth, int len)
{
    int needed = len;
    int received = 0;

    while (needed > 0) {
        int result = getrandom(auth + received, needed, GRND_RANDOM);

        if (result == -1) {
            if ((errno != EAGAIN) && (errno != EINTR)) {
                perror("getrandom");
                break;
            }
        }
        else {
            needed -= result;
            received += result;
        }
    }

    if (needed > 0) { /* fallback if getrandom returns non-retryable error */
        struct timeval now;
        int seed;
        int i;

        gettimeofday(&now, NULL);
        seed = (int) (now.tv_sec + (now.tv_usec << 16));
        srand(seed);

        for (i = received; i < len; i++) {
            int value = rand();
            auth[i] = (char) (value & 0xff);
        }
    }
}

static int
SaveServerAuthorization(const char *authFile, Xauth *auth)
{
    FILE *auth_file;
    int auth_fd;
    int ret;

    (void) remove(authFile);
    auth_fd = open(authFile, O_WRONLY | O_CREAT | O_EXCL, 0600);
    if (auth_fd == -1) {
        perror(authFile);
        return FALSE;
    }

    auth_file = fdopen(auth_fd, "w");
    if (auth_file == NULL) {
	perror(authFile);
        close(auth_fd);
	(void) remove(authFile);
        ret = FALSE;
    }
    else {
        if (!XauWriteAuth(auth_file, auth) || (fflush(auth_file) == EOF)) {
            ret = FALSE;
        }
        else {
            ret = TRUE;
        }
        fchmod(auth_fd, S_IREAD);
        fclose(auth_file);
    }
    return ret;
}

static void
SetLocalAuthorization(struct display *d)
{
    Xauth *auth;

    if (d->authorization) {
        XauDisposeAuth(d->authorization);
        d->authorization = (Xauth *) NULL;
    }
    auth = GenerateAuthorization(d->authName);
    if (auth == NULL)
        return;

    /* Change to real user id, before writing any files */
    setuid(getuid());

    if (SaveServerAuthorization(d->authFile, auth)) {
        d->authorization = auth;
    }
    else {
        XauDisposeAuth(auth);
        fatalError("Could not write server authorization file. exiting");
    }
}

static void
SetUserAuthorization(struct display *d, struct verify_info *verify)
{
    FILE *old = NULL, *new = NULL;
    char home_name[1024], backup_name[1024], new_name[1024];
    char *name = NULL;
    char *home;
    char *envname;
    int lockStatus;
    Xauth *entry, *auth;
    struct stat statb;

    new_name[0] = '\0';

    if ((auth = d->authorization) != NULL) {
        home = getenv("HOME");
        lockStatus = LOCK_ERROR;
        if (home) {
            snprintf(home_name, sizeof(home_name), "%s/.Xauthority", home);
            lockStatus = XauLockAuth(home_name, 1, 2, 10);
            if (lockStatus == LOCK_SUCCESS) {
                if (openFiles
                    (home_name, new_name, sizeof(new_name), &old, &new)) {
                    name = home_name;
                }
                else {
                    XauUnlockAuth(home_name);
                    lockStatus = LOCK_ERROR;
                }
            }
        }
        if (lockStatus != LOCK_SUCCESS) {
            int tmpfd;

            snprintf(backup_name, sizeof(backup_name), "%s/.XauthXXXXXX",
                     d->userAuthDir);
            tmpfd = mkstemp(backup_name);
            lockStatus = XauLockAuth(backup_name, 1, 2, 10);

            if (lockStatus == LOCK_SUCCESS) {
                if (openFiles
                    (backup_name, new_name, sizeof(new_name), &old, &new)) {
                    name = backup_name;
                }
                else {
                    XauUnlockAuth(backup_name);
                    lockStatus = LOCK_ERROR;
                }
            }
            close(tmpfd);
        }
        if (lockStatus != LOCK_SUCCESS) {
            return;
        }
        addrs = NULL;
        writeLocalAuth(new, auth, d->name);

        if (old) {
            if (fstat(fileno(old), &statb) != -1)
                fchmod(fileno(new), statb.st_mode & 0777);
            while ((entry = XauReadAuth(old))) {
                if (!checkAddr(entry->family,
                               entry->address_length, entry->address,
                               entry->number_length, entry->number)) {
                    writeAuth(new, entry);
                }
                XauDisposeAuth(entry);
            }
            fclose(old);
        }
        doneAddrs();
        fclose(new);
        remove(name);

        envname = name;
        if (link(new_name, name) == -1) {
            envname = new_name;
        }
        else {
            remove(new_name);
        }
        XauUnlockAuth(name);
        if (envname) {
            chown(envname, verify->uid, verify->gid);
        }
    }

}

static void
usage(const char *str)
{
    fprintf(stderr, "usage: %s Server_auth_file [-auth protocol]\n", str);
    fprintf(stderr, "      where protocol is one of magic-cookie or sun-des\n");
}

int
main(int argc, char *argv[])
{
    struct display d = {
        .authorization  = NULL,
        .userAuthDir    = DEF_USER_AUTH_DIR,
        .authName       = "MIT-MAGIC-COOKIE-1"
    };
    struct verify_info verify;
    const char *au_name = NULL;

    programName = argv[0];

    if ((argc < 2) || (strcmp(argv[1], "--help") == 0)) {
        usage(argv[0]);
        fprintf(stderr, "\n"
                "WARNING: This program will overwrite existing files.\n"
                "This may cause your X server to not accept any"
                " new client connections.\n");
        exit((argc < 2) ? -1 : 0);
    }

    d.authFile = argv[1];

    if ((d.name = strrchr(d.authFile, ':')) == NULL) {
        fatalError("Invalid filename: %s\n"
                   "Filename should include display",
                   d.authFile);
    }

    if (argv[2] && strcmp(argv[2], "-auth") == 0) {
        if (argv[3]) {
            au_name = argv[3];
        }
        else {
            fprintf(stderr, "%s: -auth requires an argument\n", argv[0]);
            usage(argv[0]);
            exit(-1);
        }
    }
    else if (argv[2]) {
        fprintf(stderr, "%s: unrecognized option %s\n", argv[0], argv[2]);
        usage(argv[0]);
        exit(-1);
    }

    if (au_name) {
        if (strcmp(au_name, "sun-des") == 0) {
            d.authName = "SUN-DES-1";
        }
        else if (strncmp(au_name, "magic", 5) != 0) {
            fprintf(stderr, "%s: -auth: unrecognized protocol %s\n", argv[0],
                    au_name);
            usage(argv[0]);
            exit(-1);
        }
    }

    verify.uid = getuid();
    verify.gid = getgid();

    SetLocalAuthorization(&d);
    SetUserAuthorization(&d, &verify);
    exit(0);
}
