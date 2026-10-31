#ifndef SF_MEMORY_H
#define SF_MEMORY_H

#include "sf_config.h"

#define SF_RIGHT_READ UINT32_C(1)
#define SF_RIGHT_WRITE UINT32_C(2)
#define SF_RIGHT_EXECUTE UINT32_C(4)

typedef enum SfRegionId {
    SF_REGION_PRIVATE = 1,
    SF_REGION_GUEST = 2,
    SF_REGION_SNAPSHOT_A = 3,
    SF_REGION_SNAPSHOT_B = 4,
    SF_REGION_TRACE = 5,
    SF_REGION_IO = 6,
    SF_REGION_TRIAL_CACHE = 7,
    SF_REGION_REQUESTS = 8,
    SF_REGION_RESPONSES = 9,
    SF_REGION_FLOW = 10,
    SF_REGION_DISPLAY = 11,
    SF_REGION_SOURCE_MAP = 12
} SfRegionId;

typedef enum SfMemoryKind {
    SF_MEMORY_UNUSABLE = 0,
    SF_MEMORY_USABLE = 1,
    SF_MEMORY_FIRMWARE = 2,
    SF_MEMORY_MMIO = 3,
    SF_MEMORY_FOUNDATION = 4
} SfMemoryKind;

typedef struct SfMemoryDescriptor {
    uint64_t physical_base;
    uint64_t byte_length;
    uint64_t attributes;
    uint32_t kind;
    uint32_t reserved;
} SfMemoryDescriptor;

typedef struct SfRegion {
    uint32_t id;
    uint32_t owner;
    uint64_t virtual_base;
    uint64_t byte_length;
    uint64_t generation;
    uint32_t rights;
    uint32_t frozen;
} SfRegion;

typedef struct SfView {
    uint32_t id;
    uint32_t reader;
    uint32_t writer;
    uint32_t slice_count;
    uint64_t generation;
    SfSpan slices[SF_MAX_VIEW_SLICES];
} SfView;

typedef struct SfLease {
    uint32_t view_id;
    uint32_t actor;
    uint64_t generation;
    uint64_t lease_id;
} SfLease;

SfStatus sf_memory_bind_fixed(const SfMemoryDescriptor *map, size_t map_count,
                              SfFault *fault);
SfStatus sf_memory_freeze_layout(void);
SfStatus sf_memory_get_region(uint32_t region_id, SfRegion *region);
SfStatus sf_memory_validate_view(const SfView *view, SfFault *fault);
SfStatus sf_memory_acquire(uint32_t actor, uint32_t view_id, SfLease *lease);
SfStatus sf_memory_release(const SfLease *lease);
SfStatus sf_memory_publish(uint32_t writer, uint32_t view_id,
                           uint64_t expected_generation,
                           uint64_t *published_generation);

#endif
