/*	$NetBSD: v_screen.c,v 1.1.1.2 2008/05/18 14:31:43 aymeric Exp $ */

/*-
 * Copyright (c) 1993, 1994
 *	The Regents of the University of California.  All rights reserved.
 * Copyright (c) 1992, 1993, 1994, 1995, 1996
 *	Keith Bostic.  All rights reserved.
 *
 * See the LICENSE file for redistribution information.
 */

#include "config.h"

#ifndef lint
static const char sccsid[] = "Id: v_screen.c,v 10.12 2001/06/25 15:19:34 skimo Exp (Berkeley) Date: 2001/06/25 15:19:34";
#endif /* not lint */

#include <sys/types.h>
#include <sys/queue.h>
#include <sys/time.h>

#include <bitstring.h>
#include <limits.h>
#include <stdio.h>

#include "../common/common.h"
#include "vi.h"

/*
 * v_screen -- ^W
 *	Switch screens.
 *
 * PUBLIC: int v_screen __P((SCR *, VICMD *));
 */
int
v_screen(SCR *sp, VICMD *vp)
{
	/*
	 * You can't leave a colon command-line edit window -- it's not that
	 * it won't work, but it gets real weird, real fast when you execute
	 * a colon command out of a window that was forked from a window that's
	 * now backgrounded...  You get the idea.
	 */
	if (F_ISSET(sp, SC_COMEDIT)) {
		msgq(sp, M_ERR,
		    "308|Enter <CR> to execute a command, :q to exit");
		return (1);
	}
		
	/*
	 * Try for the next lower screen, or, go back to the first
	 * screen on the stack.
	 */
	if (sp->q.cqe_next != (void *)&sp->wp->scrq)
		sp->nextdisp = sp->q.cqe_next;
	else if (sp->wp->scrq.cqh_first == sp) {
		msgq(sp, M_ERR, "187|No other screen to switch to");
		return (1);
	} else
		sp->nextdisp = sp->wp->scrq.cqh_first;

	F_SET(sp->nextdisp, SC_STATUS);
	F_SET(sp, SC_SSWITCH | SC_STATUS);
	return (0);
}