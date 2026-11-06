/* SPDX-License-Identifier: Apache-2.0 OR GPL-2.0-or-later */
/* Copyright (c) 2007-2026 John R. Smythe Jr. */
/******************************************************************************
 * 
 *	This file defines the following puplic functions.
 *		Micro_To_String_Local( );
 ******************************************************************************/
#include	<now.h>

/* FUNCTION:	Micro_To_String_Local
 *
 *	DESCRIPTION:
 *		Funtion Returns A Local String From MicroTime
 *
 *	INPUTS:
 *		MicroTime
 *
 *	RETURNS:
 *		Local Based String Time
 *
 *	ON ERROR:
 *		none
 */

int	Micro_To_String_Local( char * buf, size_t buf_size, char * fmt, u64 mt )
{
	char    b1[ 1024 ];
	tm_t	tm;

	Micro_To_Local( mt, &tm );
	if( fmt == NULL || *fmt == 0 ) fmt = "%y.%m.%d.%H.%M.%S";
	strftime( b1, sizeof( b1 ), fmt, (struct tm *)&tm );
	return( snprintf( buf, buf_size, "%s.%06u", b1, tm.tm_usec ) );
}

