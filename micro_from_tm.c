/* SPDX-License-Identifier: Apache-2.0 OR GPL-2.0-or-later */
/* Copyright (c) 2007-2026 John R. Smythe Jr. */
/******************************************************************************
 * 
 *	This file defines the following puplic functions.
 *		Micro_From_tm( );
 ******************************************************************************/
#include	<now.h>

/* FUNCTION:	Micro_From_tm
 *
 *	DESCRIPTION:
 *		Funtion Returns 64 Bit Time in Microseconds From A (Modified) tm Structure
 *
 *	INPUTS:
 *
 *	RETURNS:
 *		64 Bit Current Time in Microseconds 
 *
 *	ON ERROR:
 *		none
 */

u64	Micro_From_tm( tm_t * t )
{
	if( t->tm.tm_year < 70 ) return( (u64)0 );
	return( (u64)( (u64)( (u64)1000000 * mktime( (struct tm *)t ) ) + (u64)t->tm_usec ) );
}
