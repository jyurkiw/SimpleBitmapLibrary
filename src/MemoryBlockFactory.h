/*
 * MemoryBlock.h
 *
 *  Created on: 2012-01-07
 *  @author: master
 *  @version: 0.1
 */

#ifndef MEMORYBLOCK_H_
#define MEMORYBLOCK_H_

/*!
 * Factory variant class that handles data translation from various numeric
 * forms to character strings.
 */
template <typename T>
class MemoryBlockFactory
{
public:
	/*!
	 * Pointer to the translated numeric data.
	 */
	char *block_handle;

	/*!
	 * The size of the block.
	 */
	int block_size;

	/*!
	 * Constructor. Set the initial block_handle address to zero.
	 */
	MemoryBlockFactory()
	{
		block_handle = 0;
	}

	/*!
	 * Destructor. If the block_handle address is not zero, free the memory.
	 */
	~MemoryBlockFactory()
	{
		if (block_handle != 0) delete[] block_handle;
	}

	/*!
	 * Template function. Translates passed numeric data to a character string.
	 * @param T block The numeric data to translate.
	 */
	template <typename T>
	void set_memoryblock_handle(T block)
	{
		if (block_handle != 0) delete[] block_handle;

		block_size = sizeof(block);
		block_handle = new char[block_size];

		for (int x = 0, shift = x*8; x < block_size; x++, shift = x*8)
			block_handle[x] = (block >> shift) & 0xff;
	}

	/*!
	 * Merges the current memory block into the passed string. This version
	 * starts at index 0.
	 * @param char* string The string data to be merged into.
	 * @param int length The length of the string we're merging into.
	 * @return int The number of characters written.
	 */
	int merge_memoryblock_into_string(char* string, int length)
	{
		return merge_memoryblock_into_string(string, length, 0);
	}

	/*!
	 * Merges the current memory block into the passed string. This version
	 * starts at start_index.
	 * @param char* string The string data to be merged into.
	 * @param int length The length of the string we're merging into.
	 * @param int start_index The starting index of the insertion operation.
	 * @return int The number of characters written.
	 */
	int merge_memoryblock_into_string(char* string, int length, int start_index)
	{
		int end_index = start_index + block_size;

		if (end_index < length)
			for (int i = start_index, bi = 0; i < end_index; i++, bi++)
				string[i] = block_handle[bi];
		else return 0;

		return block_size;
	}
};

typedef MemoryBlockFactory memblock;

#endif /* MEMORYBLOCK_H_ */
