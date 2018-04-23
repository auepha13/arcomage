/*******************************************************************************
 * This file is part of the AEON Framework.
 *
 * (c) 2007 - 2012 kagemai.net. All Rights reserved.
 *
 ******************************************************************************/
#ifndef AeonCore_h__
#define AeonCore_h__
#include <stdint.h>
#include <string>

#ifndef NO_BOOST
#include <boost/shared_ptr.hpp>
#endif

namespace Aeon {
	typedef std::string String;
	typedef unsigned long long ulong64_t;
	typedef unsigned char Byte;
#if defined(_M_X64) || defined(_WIN64) || defined(__MINGW64__) || defined(_LP64) || defined(__LP64__) || defined(__ia64__) || defined(__x86_64__)
	typedef unsigned long uint;
#else
	typedef unsigned int uint;
#endif

#if defined(NO_BOOST)
#define Ptr std::tr1::shared_ptr
#else
#define Ptr boost::shared_ptr
#endif
}

#endif // AeonCore_h__
