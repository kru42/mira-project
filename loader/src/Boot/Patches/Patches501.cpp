// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include <Boot/Patches.hpp>

/*
	Please, please, please!
	Keep patches consistent with the used patch style for readability.
*/
void Mira::Boot::Patches::install_prerunPatches_501()
{
#if MIRA_PLATFORM == MIRA_PLATFORM_ORBIS_BSD_501
	// NOTE: Only apply patches that the loader requires to run, the rest of them should go into Mira's ELF
	// You must assign the kernel base pointer before anything is done
	if (!gKernelBase)
		return;

	// Use "kmem" for all patches
	uint8_t *kmem;

	// Enable UART
	kmem = (uint8_t *)&gKernelBase[0x019ECEB0];
	kmem[0] = 0x00;

	// Patch sys_dynlib_dlsym: Allow from anywhere
	kmem = (uint8_t *)&gKernelBase[0x00237E2A];
	kmem[0] = 0xE9;
	kmem[1] = 0xC1;
	kmem[2] = 0x01;
	kmem[3] = 0x00;
	kmem[4] = 0x00;

	kmem = (uint8_t *)&gKernelBase[0x002B2350];
	kmem[0] = 0x31;
	kmem[1] = 0xC0;
	kmem[2] = 0xC3;

	// Patch sys_mmap: Allow RWX (read-write-execute) mapping
	kmem = (uint8_t *)&gKernelBase[0x0013D510];
	kmem[0] = 0x37;
	kmem[3] = 0x37;

	// Patch setuid: Don't run kernel exploit more than once/privilege escalation
	kmem = (uint8_t *)&gKernelBase[0x00054A72];
	kmem[0] = 0xB8;
	kmem[1] = 0x00;
	kmem[2] = 0x00;
	kmem[3] = 0x00;
	kmem[4] = 0x00;

	// Enable RWX (kmem_alloc) mapping
	kmem = (uint8_t *)&gKernelBase[0x000FCC38];
	kmem[0] = 0x07;

	kmem = (uint8_t *)&gKernelBase[0x000FCC46];
	kmem[0] = 0x07;

	// Patch copyin/copyout: Allow userland + kernel addresses in both params
	kmem = (uint8_t *)&gKernelBase[0x001EA572];
	kmem[0] = 0x90;
	kmem[1] = 0x90;

	kmem = (uint8_t *)&gKernelBase[0x001EA657];
	kmem[0] = 0x90;
	kmem[1] = 0x90;

	// Patch copyinstr
	kmem = (uint8_t *)&gKernelBase[0x001EAA83];
	kmem[0] = 0x90;
	kmem[1] = 0x90;

	kmem = (uint8_t *)&gKernelBase[0x001EAAB3];
	kmem[0] = 0x90;
	kmem[1] = 0x90;

	// Patch memcpy stack
	kmem = (uint8_t *)&gKernelBase[0x001EA42D];
	kmem[0] = 0xEB;

	// Patch mprotect: Allow RWX (mprotect) mapping
	kmem = (uint8_t *)&gKernelBase[0x00080B8B];
	kmem[0] = 0x90;
	kmem[1] = 0x90;
	kmem[2] = 0x90;
	kmem[3] = 0x90;
	kmem[4] = 0x90;
	kmem[5] = 0x90;
#endif
}
