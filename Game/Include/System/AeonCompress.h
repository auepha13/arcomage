/*******************************************************************************
 * This file is part of the AEON Framework.
 *
 * (c) 2007 - 2012 kagemai.net. All Rights reserved.
 *
 ******************************************************************************/
#ifndef AeonCompress_h__
#define AeonCompress_h__
#include <string>
#include <vector>

#include <AeonCore.h>

#include <ZipFile.h>

namespace Aeon {

	class AeonCompress {
	public:

		static Ptr<ZipFile> createZipFile(const String& file,
			ZipMode::Value mode = ZipMode::ZIP_CACHE_ALLOCATE_FULL);
	};
}
#endif // AeonCompress_h__
