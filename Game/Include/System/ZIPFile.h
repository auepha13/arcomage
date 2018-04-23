/*******************************************************************************
 * This file is part of the AEON Framework.
 *
 * (c) 2007 - 2012 kagemai.net. All Rights reserved.
 *
 ******************************************************************************/
#ifndef ZipFile_h__
#define ZipFile_h__

#include <AeonCore.h>
#include <AeonAllocator.h>
#include <vector>
#include <map>
#include <string>

namespace Aeon {

	// -------------------------------------------------------------------------
	struct CompressedFile {
		char filename[2048];
		uint32_t uncompressed_size;
		uint32_t offset;
	};

	// -------------------------------------------------------------------------
	class ZlibWrap;
	typedef std::vector<String> FileList;
	typedef std::map<const String, CompressedFile> Dictionary;

	// -------------------------------------------------------------------------
	namespace Compress {
		/**
		 * Denotes the status of the zip file.
		 */
		typedef enum _ZIPFileStatus {
			ZIP_NONE = 0,
			ZIP_FILE_OK ,
			ZIP_FILE_ERROR,
			ZIP_FILE_READ_ERROR,
			ZIP_HEAP_ERROR,
			ZIP_DECOMPRESSION_FAILED,
			ZIP_FILE_NOT_FOUND,
			ZIP_NO_FILES
		} ZIPFileStatus;
	}

	// -------------------------------------------------------------------------
	typedef struct _ZipMode {
		typedef enum _Value {
			ZIP_CACHE_ALLOCATE_FULL = 0,
			ZIP_CACHE_ON_DEMAND,
			ZIP_CACHE_NONE
		} Value;
	} ZipMode;

	// -------------------------------------------------------------------------
	/**
	 * Represents a Zip file
	 */
	class ZipFile {
		friend class AeonCompress;

	public:
		~ZipFile();

		/**
		 * Returns a reduced copy of the internal dictionary containing only
		 * filenames. The list is generated on the fly when calling this function,
		 * use sparingly.
		 */
		const FileList getFilenames() const;

		/**
		 * Returns an information container containing the raw memory pointer and 
		 * length of the requested file for further processing.
		 * 
		 * @note
		 * If the requested file was not found, the pointer and length are 0,
		 * the call has to check this manually!
		 */
		const RawMemoryBlock unpackRaw(const String& file) const;

		/**
		 * Returns a copy of the requested file as String. If the requested file
		 * was not found, an empty string is returned.
		 */
		const String unpackAsString(const String& file) const;

		/**
		 * Returns the current state (or last error) of this zip file. Use this
		 * to determine whether unpacking was OK. In this case, the error is
		 * ZIP_FILE_OK
		 */
		int getLastError() const;

	private:
		ZipFile& operator =(const ZipFile& other)
		{
		}
		ZipFile(const ZipFile& other)
		{
		}
		ZipFile(const String& file, ZipMode::Value mode);

		ZlibWrap* zlibImpl;
	};

}

#endif // ZipFile_h__
