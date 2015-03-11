#!/usr/sbin/dtrace -Zs
/*
 * Copyright (c) 2015, Oracle and/or its affiliates. All rights reserved.
 */

#pragma D option quiet
#pragma D option switchrate=10hz

dtrace:::BEGIN
{
    printf("%-20s %-8s %9s %-5s %-6s %s\n", "CLIENT", "USER", "LAT(us)",
        "DIR", "BYTES", "PATH");
}

ftp*:::transfer-start
{
    self->start = timestamp;
}

ftp*:::transfer-done
/self->start/
{
    this->delta = (timestamp - self->start) / 1000;
    printf("%-20s %-8s %9d %-5s %-6d %s\n", args[0]->ci_remote,
    args[1]->fti_user, this->delta, args[1]->fti_cmd,
    args[1]->fti_nbytes, args[1]->fti_pathname);
    self->start = 0;
}
