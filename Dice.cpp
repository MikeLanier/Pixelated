#include "StdAfx.h"

#include <stdlib.h>
#include <time.h>

static BOOL	initialized = FALSE;

int	Dice()
{
	if( !initialized )
	{
		time_t	t;
		srand( int( time(&t) ) );
		initialized = TRUE;
	}
		
	return	((6 * rand()) / RAND_MAX);
}