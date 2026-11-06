/* SPDX-License-Identifier: Apache-2.0 OR GPL-2.0-or-later */
/* Copyright (c) 2007-2026 John R. Smythe Jr. */
/******************************************************************************
 * 
 *	This file defines the following puplic functions.
 *		Micro_To_Local( );
 ******************************************************************************/
#include	<now.h>

/* FUNCTION:	Micro_To_Local
 *
 *	DESCRIPTION:
 *		Funtion Returns tm structure from 64 Bit Time in Microseconds
 *
 *	INPUTS:
 *
 *	RETURNS:
 *		64 Bit Current Time in Microseconds 
 *
 *	ON ERROR:
 *		none
 */

void	Micro_To_Local( u64 mt, tm_t * tm )
{
	time_t	t;

	tm->tm_usec = ( mt % 1000000 );
	t = (time_t)( mt / 1000000 );
	localtime_r( &t, (struct tm *)tm );
	return;
}
