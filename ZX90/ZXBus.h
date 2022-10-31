#pragma once
#include <stdint.h>
#include <vector>

class ZXBusDevice
{
public:
	ZXBusDevice() {};
	virtual ~ZXBusDevice() = 0;
};

class ZXBus : public ZXBusDevice
{
public:
	ZXBus();
	~ZXBus();

	void Open(uint32_t device);
	void Close();

	void Write(uint32_t value, uint32_t addr);
	void Read();

	void Attach(ZXBusDevice* device);

private:
	std::vector<ZXBusDevice*> m_devices;
};

