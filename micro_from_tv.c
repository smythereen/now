/* SPDX-License-Identifier: Apache-2.0 OR GPL-2.0-or-later */
/* Copyright (c) 2007-2026 John R. Smythe Jr. */
/******************************************************************************
 * 
 *	This file defines the following puplic functions.
 *		Micro_From_Timeval( );
 ******************************************************************************/
#include	<now.h>

/* FUNCTION:	Micro_From_Timeval
 *
 *	DESCRIPTION:
 *		Funtion Returns 64 Bit Time in Microseconds From A Timeval Structure
 *
 *	INPUTS:
 *
 *	RETURNS:
 *		64 Bit Current Time in Microseconds 
 *
 *	ON ERROR:
 *		none
 */

u64	Micro_From_Timeval( tv_t t )
{
	return( (u64)( (u64)( (u64)t.tv_sec * (u64)1000000 ) + (u64)t.tv_usec ) );
}
