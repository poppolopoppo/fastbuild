/*
 * Author:  David Robert Nadeau
 * Site:    http://NadeauSoftware.com/
 * License: Creative Commons Attribution 3.0 Unported License
 *          http://creativecommons.org/licenses/by/3.0/deed.en_US
 */

#include "Core/Env/Types.h"

#if defined(_WIN32)
#include <Windows.h>
#else
#include <unistd.h>
#include <sys/types.h>
#include <sys/param.h>
#if defined(BSD)
#include <sys/sysctl.h>
#endif
#endif

// Returns the size of physical memory (RAM) in bytes.
//------------------------------------------------------------------------------
void GetSystemMemorySize( size_t * free, size_t * total )
{
#if defined(_WIN32) && (defined(__CYGWIN__) || defined(__CYGWIN32__))
	/* Cygwin under Windows. ------------------------------------ */
	/* New 64-bit MEMORYSTATUSEX isn't available.  Use old 32.bit */
	MEMORYSTATUS status;
	status.dwLength = sizeof(status);
	GlobalMemoryStatus( &status );

    *free = (size_t)status.dwAvailPhys;
	*total = (size_t)status.dwTotalPhys;

#elif defined(_WIN32)
	/* Windows. ------------------------------------------------- */
	/* Use new 64-bit MEMORYSTATUSEX, not old 32-bit MEMORYSTATUS */
	MEMORYSTATUSEX status;
	status.dwLength = sizeof(status);
	GlobalMemoryStatusEx( &status );

    *free = (size_t)status.ullAvailPhys;
	*total = (size_t)status.ullTotalPhys;

#else
    /* UNIX variants. ------------------------------------------- */
    /* Prefer sysctl() over sysconf() except sysctl() HW_REALMEM and HW_PHYSMEM */

#if defined(_SC_PHYS_PAGES) && defined(_SC_PAGESIZE) && defined(_SC_AVPHYS_PAGES)
    /* FreeBSD, Linux, OpenBSD, and Solaris. -------------------- */
	const uint64_t psz = (uint64_t)sysconf( _SC_PAGESIZE );
    *total = (size_t)( (uint64_t)sysconf( _SC_PHYS_PAGES ) * psz );
	*free = (size_t)( (uint64_t)sysconf( _SC_AVPHYS_PAGES ) * psz );
#else
#	error "not implemented"
#endif

#endif
}
