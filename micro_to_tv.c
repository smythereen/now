/* SPDX-License-Identifier: Apache-2.0 OR GPL-2.0-or-later */
/* Copyright (c) 2007-2026 John R. Smythe Jr. */
/******************************************************************************
 * 
 *	This file defines the following puplic functions.
 *		Micro_To_Timeval( );
 ******************************************************************************/
#include	<now.h>

/* FUNCTION:	Micro_To_Timeval
 *
 *	DESCRIPTION:
 *		Funtion Returns timeval structure from 64 Bit Time in Microseconds
 *
 *	INPUTS:
 *
 *	RETURNS:
 *		64 Bit Current Time in Microseconds 
 *
 *	ON ERROR:
 *		none
 */

tv_t	Micro_To_Timeval( u64 mt )
{
	return( (tv_t){ (u32)( (u64)( mt / 1000000 ) ), (u32)( (u64)( mt % 1000000 ) ) } );
}
