/*******************************************************************************
 * This file is part of the AEON Framework.
 *
 * (c) 2007 - 2012 kagemai.net. All Rights reserved.
 *
 ******************************************************************************/

#include "unzip.h"

#if (!defined(_WIN32)) && (!defined(WIN32)) && (!defined(__APPLE__))
#ifndef __USE_FILE_OFFSET64
#define __USE_FILE_OFFSET64
#endif
#ifndef __USE_LARGEFILE64
#define __USE_LARGEFILE64
#endif
#ifndef _LARGEFILE64_SOURCE
#define _LARGEFILE64_SOURCE
#endif
#ifndef _FILE_OFFSET_BIT
#define _FILE_OFFSET_BIT 64
#endif
#endif

#ifdef __APPLE__
// In darwin and perhaps other BSD variants off_t is a 64 bit value, hence no need for specific 64 bit functions
#define FOPEN_FUNC(filename, mode) fopen(filename, mode)
#define FTELLO_FUNC(stream) ftello(stream)
#define FSEEKO_FUNC(stream, offset, origin) fseeko(stream, offset, origin)
#else
#define FOPEN_FUNC(filename, mode) fopen64(filename, mode)
#define FTELLO_FUNC(stream) ftello64(stream)
#define FSEEKO_FUNC(stream, offset, origin) fseeko64(stream, offset, origin)
#endif


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <errno.h>
#include <fcntl.h>

#ifdef _WIN32
# include <direct.h>
# include <io.h>
#else
# include <unistd.h>
# include <utime.h>
#endif


#include "unzip.h"

#define CASESENSITIVITY (0)
#define WRITEBUFFERSIZE (8192)
#define MAXFILENAME (256)

#ifdef _WIN32
#define USEWIN32IOAPI
#include "iowin32.h"
#endif

#include <ZipFile.h>
#include <algorithm>
#include <iterator>
#include <stdio.h>
#include <string.h>
namespace Aeon {

	class ZlibWrap {
	public:

		// ---------------------------------------------------------------------
		ZlibWrap() : rawData(0), zip(0),
			mode(ZipMode::ZIP_CACHE_ALLOCATE_FULL), errCode(Compress::ZIP_NONE)
		{

		}

		// ---------------------------------------------------------------------
		~ZlibWrap()
		{
			if(zip != 0) {
				close();
			}
			freeRawData();
		}

		// ---------------------------------------------------------------------
		void open(const char* fname)
		{
			zip = unzOpen(fname);
		}

		// ---------------------------------------------------------------------
		void readDictionary(const String& file, ZipMode::Value mode)
		{
			this->mode = mode;
			readFile(file, mode == ZipMode::ZIP_CACHE_ALLOCATE_FULL);
		}

		// ---------------------------------------------------------------------
		void readFile(const String& file, bool cacheAll = false)
		{

			close();

			freeRawData();

			open(file.c_str());

			unz_global_info info;
			if(unzGetGlobalInfo(zip, &info) != UNZ_OK) {
				errCode = Compress::ZIP_FILE_READ_ERROR;
				return;
			}

			if(info.number_entry == 0) {
				errCode = Compress::ZIP_NO_FILES;
				return;
			}

			uint32_t uncompressed_size = 0;

			if(cacheAll) {
				uncompressed_size = getUncompressedBlockSize();

				if(close() != UNZ_OK) {
					errCode = Compress::ZIP_FILE_ERROR;
					return;
				}

				open(file.c_str());

				if(uncompressed_size <= 0) {
					errCode = Compress::ZIP_FILE_READ_ERROR;
					return;
				}

				rawData = new LinearMemoryBlock(uncompressed_size);

			}

			do {
				unz_file_info file_info;
				char filename[256+1];

				if(unzGetCurrentFileInfo(zip, &file_info, filename, sizeof(filename),
					NULL,
					0, NULL, 0) != UNZ_OK) {
						errCode = Compress::ZIP_FILE_READ_ERROR;
					return;
				}

				if(file_info.uncompressed_size > 0) {
					CompressedFile entry = {};
					strncpy(entry.filename, filename,256);
					filename[256]  = '\0';

					if(cacheAll) {
						entry.uncompressed_size = file_info.
							uncompressed_size;
						if(!unpackToRawMemory(&entry,
							file_info.uncompressed_size)) {
							close();
							freeRawData();
							errCode = Compress::ZIP_HEAP_ERROR;
							return;
						}
					} else {
						entry.uncompressed_size = 0;
					}

					dictionary[entry.filename] = entry;
				}


			} while(unzGoToNextFile(zip) == UNZ_OK);
			if(cacheAll) {
				close();
			}

		}

		// ---------------------------------------------------------------------
		RawMemoryBlock getRawMem(const String& filename)
		{
			RawMemoryBlock mem;

			if(dictionary[filename].uncompressed_size > 0) {
				mem.ptr = this->rawData->data+dictionary[filename].
					offset;
				mem.length = dictionary[filename].uncompressed_size;
			} else if(mode != ZipMode::ZIP_CACHE_ALLOCATE_FULL) {
				mem  = seekFileOnDisk(filename.c_str());
			} else {
				errCode = Compress::ZIP_FILE_NOT_FOUND;
				return mem;
			}

			if(mem.length > 0) {
				errCode = Compress::ZIP_FILE_OK;
			}

			return mem;
		}
		// ---------------------------------------------------------------------
		RawMemoryBlock seekFileOnDisk(const char* filename)
		{
			RawMemoryBlock mem;
			if(!zip) {
				errCode = Compress::ZIP_FILE_ERROR;
				return mem;
			}

			if(unzLocateFile(zip, filename, 2) != UNZ_OK) {
				errCode = Compress::ZIP_FILE_NOT_FOUND;
				return mem;
			}
			unz_file_info file_info;
			if(unzGetCurrentFileInfo(zip, &file_info, 0, 0,
				0,
				0, 0, 0) != UNZ_OK) {
					errCode = Compress::ZIP_FILE_READ_ERROR;
				return mem;
			}
			/*
			if(mode == ZipMode::ZIP_CACHE_ON_DEMAND) {
				dictionary[filename].uncompressed_size = file_info.uncompressed_size;
			}
			*/

			mem.length = file_info.uncompressed_size;
			mem.ptr = (Byte*)AllocateNonAligned(file_info.uncompressed_size);
			if(!unzipRawMem(mem.ptr, mem.length)) {
				close();
				freeRawData();
				mem.length = 0;
				DeallocateNonAligned(mem.ptr);
				mem.ptr = 0;
				errCode = Compress::ZIP_HEAP_ERROR;
			}

			return mem;

		}
		// ---------------------------------------------------------------------
		int close()
		{
			int ret = 0;
			if(zip != 0) {
				ret = unzClose(zip);
				zip = 0;

				errCode = Compress::ZIP_NONE;
			}
			return ret;

		}

		// ---------------------------------------------------------------------
		const std::map<const String, CompressedFile>& getDictionary()
		{
			return dictionary;
		}

		// ---------------------------------------------------------------------
		void freeRawData()
		{
			if(rawData != 0) {
				DeallocateNonAligned(rawData->data);
				rawData->offset = 0;
				rawData->size = 0;
				delete rawData;
				rawData = 0;

				errCode = Compress::ZIP_NONE;
			}
		}

		// ---------------------------------------------------------------------
		int getError() {
			return errCode;
		}

	private:
		int errCode;
		ZipMode::Value mode;
		unzFile zip;
		LinearMemoryBlock* rawData;
		std::map<const String, CompressedFile> dictionary;

		// ---------------------------------------------------------------------
		void* alloc(uint32_t size)
		{
			if(size + rawData->offset > rawData->size || rawData==0) {
				return 0;
			}

			void* mem = rawData->data + rawData->offset;
			rawData->offset += size;
			return mem;
		}

		// ---------------------------------------------------------------------
		bool unpackToRawMemory(CompressedFile* entry,
			uint32_t uncompressed_size)
		{
			entry->offset = rawData->offset;
			void* mem = alloc(uncompressed_size);
			if(!mem) {
				errCode = Compress::ZIP_HEAP_ERROR;
				throw std::bad_alloc();
			}

			return unzipRawMem(mem, uncompressed_size);

		}
		// ---------------------------------------------------------------------
		bool unzipRawMem(void* ptr, uint32_t size)
		{

			if(unzOpenCurrentFile(zip) != UNZ_OK) {
				errCode = Compress::ZIP_FILE_READ_ERROR;
				return false;
			}

			if(unzReadCurrentFile(zip, ptr,
				size) != size) {
					errCode = Compress::ZIP_DECOMPRESSION_FAILED;
				return false;
			}

			if(unzCloseCurrentFile(zip) != UNZ_OK) {
				errCode = Compress::ZIP_FILE_ERROR;
				return false;
			}

			return true;
		}
		// ---------------------------------------------------------------------
		uint32_t getUncompressedBlockSize()
		{
			if(unzGoToFirstFile(zip) != UNZ_OK) {
				return 0;
			}

			uint32_t sum = 0;
			do {
				unz_file_info file_info;

				if(unzGetCurrentFileInfo(zip, &file_info, 0, 0, 0,
					0, 0, 0) != UNZ_OK) {
						errCode = Compress::ZIP_FILE_ERROR;
					return 0;
				}

				if(file_info.uncompressed_size > 0) {
					sum += file_info.uncompressed_size;
				}
			} while(unzGoToNextFile(zip) == UNZ_OK);

			return sum;
		}

	};

	// -------------------------------------------------------------------------
	struct CompressedFileKey {
		template <typename T>
		typename T::first_type operator()(T keyValuePair) const
		{
			return keyValuePair.first;
		}
	};

	// -------------------------------------------------------------------------
	ZipFile::ZipFile(const String& file,
		ZipMode::Value mode/* = ZipMode::ZIP_CACHE_ALLOCATE_FULL */) :
		zlibImpl(new ZlibWrap())
	{
		zlibImpl->readDictionary(file, mode);
	}


	// -------------------------------------------------------------------------
	ZipFile::~ZipFile()
	{
		delete zlibImpl;
	}

	// -------------------------------------------------------------------------
	const FileList ZipFile::getFilenames() const
	{
		std::vector<std::string> files;
		Dictionary dict = zlibImpl->getDictionary();
		std::transform(dict.begin(), dict.end(), std::back_inserter(files),
			CompressedFileKey());
		return files;
	}


	// -------------------------------------------------------------------------
	const RawMemoryBlock ZipFile::unpackRaw(const String& file) const
	{
		return zlibImpl->getRawMem(file);
	}

	// -------------------------------------------------------------------------
	const String ZipFile::unpackAsString( const String& file ) const
	{
		RawMemoryBlock mem = unpackRaw(file);
		return String(reinterpret_cast<char*>(mem.ptr), mem.length).c_str();
	}

	// -------------------------------------------------------------------------
	int ZipFile::getLastError() const {
		return zlibImpl->getError();
	}
}
