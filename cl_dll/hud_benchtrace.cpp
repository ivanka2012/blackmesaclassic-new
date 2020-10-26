// hud_benchtrace.cpp
// Functions for spawning a thread to get a hopcount to a particular ip address and returning the result in a specified
//  variable

#ifdef _WIN32
#include "winsani_in.h"
#include <windows.h>
#include "winsani_out.h"
#else
#include "port.h"
#include <dlfcn.h>
#endif

// For tracking the trace threads
typedef struct
{
	// Inputs
	char	server[ 256 ];

	// Outputs
	int		*p_nresults;
	int		*p_ndone;
	
	// Local variables
	DWORD	hThreadId;
	HANDLE	hThread;
	HANDLE	hEventDone;
} trace_params_t;

// Static forces it to be zeroed out
static trace_params_t tp;

// For doing the actual traceroute
struct trace_options_s
{
	unsigned char ucTTL;
	unsigned char a[7];
};

struct
{
	DWORD			dwAddress;
	unsigned long	ulStatus, ulRoundTripTime;
	unsigned char	a[8];
	struct trace_options_s Options;
} traceReturn;

/*
==============
Trace_GetHopCount

Performs a synchronous hopcount on the specified server
==============
*/
int Trace_GetHopCount( char *pServer, int nMaxHops )
{
	return -1;
}

/*
==============
Trace_Cleanup

Destroys thread and event handle when trace is done, or when restarting a new trace
==============
*/
void Trace_Cleanup( void )
{

}

#ifdef _WIN32

/*
==============
Trace_ThreadFunction

Performs a trace, sets finish event and exits
==============
*/
DWORD WINAPI Trace_ThreadFunction( LPVOID p )
{
	return 0;
}
#endif

/*
==============
Trace_StartTrace

Create finish event, sets up data, and starts thread to do a traceroute.
==============
*/
void Trace_StartTrace( int *results, int *finished, const char *server )
{

}

/*
==============
Trace_Think

Invoked by general frame loop on client to periodically check if the traceroute thread has completed.
==============
*/
void Trace_Think( void )
{
	
}