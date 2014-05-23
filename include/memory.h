/*
 * memory.h
 *
 * Type and function declarations for memory management.
 *
 * (c) 2014 Hadi Moshayedi <hadi@moshayedi.net>
 */

#ifndef MEMORY_H
#define MEMORY_H

#define KERNEL_BASE 0x80000000

#ifndef __ASSEMBLER__

#include <types.h>

/* conversion macros */
#define SECTION_INDEX(x) ((uint32_t)x >> 20)
#define PAGE_INDEX(x) (((uint32_t)x >> 12) & 255)
#define PAGE_TABLE_TO_BASE(x) ((uint32_t)x >> 10)
#define BASE_TO_PAGE_TABLE(x) ((void *) ((uint32_t)x << 10))

#define P2V(x) (((uint32_t) x) + KERNEL_BASE)
#define V2P(x) (((uint32_t) x) - KERNEL_BASE)

/* memory layout */
#define MAX_KERNEL_SIZE 0x1000000
#define UART0_BASE (KERNEL_BASE + MAX_KERNEL_SIZE)
#define PIC_BASE (UART0_BASE + PAGE_SIZE)
#define INTERRUPT_VECTOR_BASE 0xffff0000

/* physical memory */
#define UART0_PHYSICAL 0x101f1000
#define PIC_PHYSICAL 0x10140000

/* page table */
#define PAGES_PER_SECTION 1024
#define SECTION_COUNT 4096
#define PAGE_SIZE 4096
#define SECTION_SIZE (PAGE_SIZE * PAGES_PER_SECTION)

/* memory layout */
#define USER_LIMIT (KERNEL_BASE - SECTION_SIZE)
#define USER_VPAGE_TABLE (USER_LIMIT - SECTION_SIZE)

/* descriptor types */
#define PAGE_DESC 2
#define SECTION_DESC 1
#define SECTION_COARSE 1
#define PAGE_SMALL 2

/* access permissions */
#define AP_RW_D 0x55
#define AP_RW_R 0xaa
#define AP_RW_RW 0xff

#define PAGE_TABLE_ALIGNMENT 1024
#define SECTION_TABLE_ALIGNMENT 16384
#define PAGE_TABLE_SIZE 1024
#define SECTION_TABLE_SIZE 16384

struct SectionTableEntry {
	unsigned int desc_type : 2;
	unsigned int : 3;
	unsigned int domain : 4;
	unsigned int : 1;
	unsigned int base_address : 22;
};

struct PageTableEntry {
	unsigned int desc_type : 2;
	unsigned int bufferable : 1;
	unsigned int cacheable : 1;
	unsigned int access_permissions : 8;
	unsigned int base_address : 20;
};

struct MemoryMapping {
	uint32_t virtual_address;
	uint32_t physical_start;
	uint32_t physical_end;
	int access_permissions;

};

struct PhysicalPage {
	struct PhysicalPage *next;
	uint16_t reference_count;
};

void memory_init(void);
void clean_low_mem(void);

#endif
#endif
