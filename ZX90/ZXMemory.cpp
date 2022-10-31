#include "ZXMemory.h"
#include <memory>

ZXMemory::ZXMemory()
{
    m_heap = new uint32_t[2048];
}

ZXMemory::~ZXMemory()
{
    delete[] m_heap;
}

void ZXMemory::Store(uint32_t addr, uint32_t data)
{
    m_heap[addr] = data;
}

uint32_t ZXMemory::Read(uint32_t addr) const
{
    return m_heap[addr];
}

uint32_t* ZXMemory::Ptr(uint32_t addr)
{
    return &m_heap[addr];
}

void ZXMemory::Copy(uint32_t addr, uint32_t* src, uint32_t size)
{
    std::memcpy(&m_heap[addr], src, sizeof(uint32_t) * size);
}

void ZXMemory::Memset(uint32_t addr, uint32_t value, uint32_t size)
{
    std::memset(&m_heap[addr], value, sizeof(uint32_t) * size);
}
