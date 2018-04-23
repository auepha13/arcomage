/*******************************************************************************
 * This file is part of the AEON Framework.
 *
 * (c) 2007 - 2012 kagemai.net. All Rights reserved.
 *
 ******************************************************************************/
#ifndef AeonAllocator_h__
#define AeonAllocator_h__
#include <malloc.h>
#include <stdio.h>
#include <AeonCore.h>

namespace Aeon {

#ifdef __cplusplus
	extern "C" {
#endif
		/** 
		 * Allocates non-aligned memory
		 */
		static void* AllocateNonAligned(uint32_t memory)
		{
			return malloc(memory);
		}

		/**
		 * Deallocates non aligned memory 
		 */
		static void DeallocateNonAligned(void* mem)
		{
			if(mem != 0) {
				free(mem);
			}
		}


#ifdef __cplusplus
	}
#endif

	/**
	* Represents a linear block of raw memory.
	*/
#pragma pack(push)
	struct LinearMemoryBlock {
		explicit LinearMemoryBlock(uint32_t size) : size(size), offset(0)
		{
			data = (Byte*)AllocateNonAligned(size);
		}
/*		~LinearMemoryBlock()
		{
			if(data != 0) {
				DeallocateNonAligned(data);
				data = 0;
			}
		}
*/
		Byte* data;
		uint32_t size;
		uint32_t offset;
	};

#pragma pack(pop)

#pragma pack(push)
	struct RawMemoryBlock {
		explicit RawMemoryBlock() : ptr(0), length(0)
		{
		}
		void* ptr;
		uint32_t length;
	};
#pragma pack(pop)
}
#endif // AeonAllocator_h__
