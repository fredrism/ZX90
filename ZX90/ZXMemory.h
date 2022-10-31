#pragma once
#include <stdint.h>

const int PROG_START = 0;
const int HEAP_START = 512;

class ZXMemory
{
public:
	ZXMemory();
	~ZXMemory();

	void Store(uint32_t addr, uint32_t data);
	uint32_t Read(uint32_t addr) const;
	uint32_t* Ptr(uint32_t addr);

	void Copy(uint32_t addr, uint32_t* src, uint32_t size);
	void Memset(uint32_t addr, uint32_t value, uint32_t size);

private:
	uint32_t* m_heap;

};

