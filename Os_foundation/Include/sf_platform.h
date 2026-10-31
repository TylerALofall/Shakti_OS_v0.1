#ifndef SF_PLATFORM_H
#define SF_PLATFORM_H

#include "sf_memory.h"

#define SF_CAP_LONG_MODE UINT64_C(1)
#define SF_CAP_VMX UINT64_C(2)
#define SF_CAP_EPT UINT64_C(4)
#define SF_CAP_NX UINT64_C(8)
#define SF_CAP_IOMMU UINT64_C(16)
#define SF_CAP_INTERRUPT_REMAP UINT64_C(32)
#define SF_CAP_DURABLE_FLUSH UINT64_C(64)

typedef struct SfPlatformInfo {
    uint64_t capabilities;
    uint64_t usable_ram_bytes;
    uint64_t framebuffer_physical;
    uint64_t framebuffer_bytes;
    uint32_t logical_cpu_count;
    uint32_t physical_address_bits;
    uint32_t framebuffer_width;
    uint32_t framebuffer_height;
    uint32_t framebuffer_stride_bytes;
    uint32_t framebuffer_format;
    uint32_t storage_sector_bytes;
    uint32_t storage_controller_kind;
} SfPlatformInfo;

typedef struct SfBootInfo {
    uint32_t version;
    uint32_t descriptor_count;
    SfHash256 image_hash;
    SfHash256 profile_hash;
    SfPlatformInfo platform;
    SfMemoryDescriptor descriptors[SF_MAX_MEMORY_DESCRIPTORS];
} SfBootInfo;

typedef struct SfGuestExit {
    uint64_t sequence;
    uint64_t instruction_pointer;
    uint64_t qualification;
    uint64_t guest_physical_address;
    uint32_t vcpu;
    uint32_t reason;
    SfStatus status;
} SfGuestExit;

/* Adapter routines are explicit hardware-boundary implementations. */
SfStatus sf_platform_probe(SfBootInfo *boot, SfFault *fault);
SfStatus sf_platform_enter(const SfBootInfo *boot);
SfStatus sf_platform_map_view(const SfView *view);
SfStatus sf_platform_protect(uint32_t region_id, uint32_t actor,
                             uint32_t rights);
SfStatus sf_platform_dma_bind(uint32_t device_id, uint32_t region_id);
SfStatus sf_platform_dma_quiesce(uint32_t device_id, uint64_t fuel);
SfStatus sf_platform_guest_start(uint32_t profile_id, uint32_t vcpu_count);
SfStatus sf_platform_guest_step(uint64_t fuel, SfGuestExit *exit_record);
SfStatus sf_platform_guest_pause(uint32_t vcpu_mask, uint64_t fuel);
SfStatus sf_platform_guest_resume(uint32_t vcpu_mask);
SfStatus sf_platform_publish_barrier(void);
SfStatus sf_platform_acquire_barrier(void);
SfStatus sf_platform_claim_slot(uint32_t slot, uint32_t expected_state,
                                uint32_t new_state, uint32_t generation);

#endif
