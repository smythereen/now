/* SPDX-License-Identifier: Apache-2.0 OR GPL-2.0-or-later */
/* Copyright (c) 2009-2026 John R. Smythe Jr. */
/******************************************************************************
 * 
 *	This file defines the following puplic functions.
 *		Micro_To_String_Local( );
 ******************************************************************************/
#include	<now.h>

static	void	Skip_NonDigits( char ** buf )
{
	while( **buf != 0 ) {
		if( isdigit( **buf ) ) return;
		*buf += 1;
	}
}

/* FUNCTION:	Micro_From_String
 *
 *	DESCRIPTION:
 *		Funtion Returns A Local String From MicroTime
 *
 *	INPUTS:
 *		Local Based String Time
 *
 *	RETURNS:
 *		MicroTime
 *
 *	ON ERROR:
 *		none
 */

u64	Micro_From_String( char * buf, tm_t * tm )
{
	int	i;
	s32	x;
	tm_t	t;


	if( tm == NULL ) tm = &t;

	memset( tm, 0, sizeof( tm_t ) );
	tm->tm.tm_mday = 1;
	
	if( buf == NULL || *buf == 0 ) return( Micro_From_tm( tm ) );

	for( i = 0, x = 0; i < 4; i++ ) {
		if( *buf == 0 || !isdigit( *buf ) ) break;
		x *= 10;
		x += ( *buf++ - '0' );
	}
	tm->tm.tm_year = x - 1900;
	Skip_NonDigits( &buf );
	if( *buf == 0 ) return( Micro_From_tm( tm ) );

	for( i = 0, x = 0; i < 2; i++ ) {	// Up To A 2-Digit Month
		if( *buf == 0 || !isdigit( *buf ) ) break;
		x *= 10;
		x += ( *buf++ - '0' );
	}
	if( x > 0 ) x -= 1;
	tm->tm.tm_mon = x;
	Skip_NonDigits( &buf );
	if( *buf == 0 ) return( Micro_From_tm( tm ) );

	for( i = 0, x = 0; i < 2; i++ ) {	// Up To A 2-Digit Month Day
		if( *buf == 0 || !isdigit( *buf ) ) break;
		x *= 10;
		x += ( *buf++ - '0' );
	}
	if( x == 0 ) x += 1;
	tm->tm.tm_mday = x;
	Skip_NonDigits( &buf );
	if( *buf == 0 ) return( Micro_From_tm( tm ) );

	for( i = 0, x = 0; i < 2; i++ ) {	// Up To A 2-Digit Hour (0-23)
		if( *buf == 0 || !isdigit( *buf ) ) break;
		x *= 10;
		x += ( *buf++ - '0' );
	}
	tm->tm.tm_hour = x;
	Skip_NonDigits( &buf );
	if( *buf == 0 ) return( Micro_From_tm( tm ) );

	for( i = 0, x = 0; i < 2; i++ ) {	// Up To A 2-Digit Minute (0-59)
		if( *buf == 0 || !isdigit( *buf ) ) break;
		x *= 10;
		x += ( *buf++ - '0' );
	}
	tm->tm.tm_min = x;
	Skip_NonDigits( &buf );
	if( *buf == 0 ) return( Micro_From_tm( tm ) );

	for( i = 0, x = 0; i < 2; i++ ) {	// Up To A 2-Digit Second (0-59)
		if( *buf == 0 || !isdigit( *buf ) ) break;
		x *= 10;
		x += ( *buf++ - '0' );
	}
	tm->tm.tm_sec = x;
	Skip_NonDigits( &buf );
	if( *buf == 0 ) return( Micro_From_tm( tm ) );

	for( i = 0, x = 0; i < 6; i++ ) {	// Up To A 6-Digit SubSecond
		if( *buf == 0 || !isdigit( *buf ) ) {
			for( ; i < 6; i++ ) x *= 10;
			break;
		}
		x *= 10;
		x += ( *buf++ - '0' );
	}
	tm->tm_usec = x;
	return( Micro_From_tm( tm ) );
}

