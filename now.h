/* SPDX-License-Identifier: Apache-2.0 OR GPL-2.0-or-later */
/* Copyright (c) 2009-2026 John R. Smythe Jr. */
/*******************************************************************************
 * 
 *	(NOW) Global header file.
 *
 *	This file defines common structures, variables, and routines
 *	needed for NOW processes.
 ******************************************************************************/
#ifndef	NOW_H
#define	NOW_H

#include	<time.h>
#include	<common.h>

#if	defined( __cplusplus )
extern	"C"	{
#endif

//#define		NOW_TRC_LVL	0x00100000

typedef	struct	tm	TM;

typedef	struct	{
#if	defined( __cplusplus )
	struct	tm	tm;
#else
	struct	tm	tm;
#endif
	int		tm_usec;	/* microseconds */
}	tm_t;

typedef	struct	timeval	tv_t;

/*
 *	Global Routines (NOW)
 */

extern	u64	Micro_From_String( char * buf, tm_t * tm_struct );
extern	u64	Micro_From_Timeval( tv_t timeval_struct );
extern	u64	Micro_From_tm( tm_t * tm_struct );
extern	u64	Micro_Now( void );
extern	void	Micro_To_GMT( u64 mt, tm_t * tm_struct );
extern	void	Micro_To_Local( u64 mt, tm_t * tm_struct );
extern	tv_t	Micro_To_Timeval( u64 microtime );
extern	int	Micro_To_String_GMT( char * buf, size_t buf_size, char * fmt, u64 microtime );
extern	int	Micro_To_String_Local( char * buf, size_t buf_size, char * fmt, u64 microtime );

#if	defined( __cplusplus )
}
#endif

#endif
