#ifndef _MVISOR_ARCH_AARCH64_H_
#define _MVISOR_ARCH_AARCH64_H_

#include <asm/aarch64_helper.h>
#include <mvisor/vm.h>

#define read_sysreg32(name) ({                          \
    uint32_t _r;                                        \
    asm volatile("mrs  %0, "stringify(name) : "=r" (_r));         \
    _r; })

#define write_sysreg32(v, name) do {                    \
    uint32_t _r = v;                                    \
    asm volatile("msr "stringify(name)", %0" : : "r" (_r));       \
} while (0)

#define write_sysreg64(v, name) do {                    \
    uint64_t _r = v;                                    \
    asm volatile("msr "stringify(name)", %0" : : "r" (_r));       \
} while (0)

#define read_sysreg64(name) ({                          \
    uint64_t _r;                                        \
    asm volatile("mrs  %0, "stringify(name) : "=r" (_r));         \
    _r; })

#define read_sysreg(name)     read_sysreg64(name)
#define write_sysreg(v, name) write_sysreg64(v, name)

static inline void flush_local_tlb(void)
{
	/* current VMID only */
	asm volatile (
		"dsb sy;"
		"tlbi vmalls12e1;"
		"dsb sy;"
		"isb;"
		: : : "memory"
	);
}

static inline void flush_local_tlbis(void)
{
	/* current vmid only and innershareable TLBS */
	asm volatile(
		"dsb sy;"
		"tlbi vmalls12e1is;"
		"dsb sy;"
		"isb;"
		: : : "memory"
	);
}

static inline void flush_all_tlb(void)
{
	/* flush all vmids local TLBS, non-hypervisor mode */
	asm volatile(
		"dsb sy;"
		"tlbi alle1;"
		"dsb sy;"
		"isb;"
		: : : "memory"
	);
}

static inline void flush_all_tlbis(void)
{
	/* flush innershareable TLBS, all VMIDs, non-hypervisor mode */
	asm volatile(
		"dsb sy;"
		"tlbi alle1is;"
		"dsb sy;"
		"isb;"
		: : : "memory"
	);
}

int get_cpu_id(void);
int arch_early_init(void);
int arch_init(void);
int arch_vm_init(struct vm *vm);

#endif