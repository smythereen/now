/* SPDX-License-Identifier: Apache-2.0 OR GPL-2.0-or-later */
/* Copyright (c) 2007-2026 John R. Smythe Jr. */
/******************************************************************************
 * 
 *	This file defines the following puplic functions.
 *		Micro_Now( );
 ******************************************************************************/
#include	<now.h>

/* FUNCTION:	Micro_Now
 *
 *	DESCRIPTION:
 *		Funtion Returns Current Time in Microseconds From (00:00 1-Jan-70 GMT)
 *
 *	INPUTS:
 *
 *	RETURNS:
 *		64 Bit Current Time in Microseconds 
 *
 *	ON ERROR:
 *		none
 */

u64	Micro_Now( void )
{
	struct	timeval		now;

	gettimeofday( &now, NULL );
	return( (u64)( (u64)( (u64)now.tv_sec * (u64)1000000 ) + (u64)now.tv_usec ) );
}
