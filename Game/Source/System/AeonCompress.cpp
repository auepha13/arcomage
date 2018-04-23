/*******************************************************************************
 * This file is part of the AEON Framework.
 *
 * (c) 2007 - 2012 kagemai.net. All Rights reserved.
 *
 ******************************************************************************/
#include <AeonCompress.h>

namespace Aeon {


	// -------------------------------------------------------------------------
	Ptr<ZipFile> AeonCompress::createZipFile( const String& file,
		ZipMode::Value mode /*= ZipMode::ZIP_CACHE_ALLOCATE_FULL*/ )
	{
		return Ptr<ZipFile>(new ZipFile(file, mode));
	}
}
