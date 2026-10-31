#ifndef SF_BASE_H
#define SF_BASE_H

/* Interface declarations only. No implementation has been compiled here. */
#include <stdint.h>
#include <stddef.h>
#include <limits.h>

#if !defined(__STDC_VERSION__) || (__STDC_VERSION__ != 199901L)
#error "SF requires ISO C99 mode for portable native code"
#endif
#if CHAR_BIT != 8
#error "SF requires eight-bit bytes"
#endif
#if !defined(UINT8_MAX) || !defined(UINT16_MAX) || !defined(UINT32_MAX) || !defined(UINT64_MAX)
#error "SF requires exact-width unsigned integer types"
#endif
#if INT_MAX != 2147483647
#error "SF initial ABI requires a 32-bit int"
#endif

typedef char SfCheckU8[(sizeof(uint8_t) == 1u) ? 1 : -1];
typedef char SfCheckU16[(sizeof(uint16_t) == 2u) ? 1 : -1];
typedef char SfCheckU32[(sizeof(uint32_t) == 4u) ? 1 : -1];
typedef char SfCheckU64[(sizeof(uint64_t) == 8u) ? 1 : -1];
typedef char SfCheckPointer[(sizeof(void *) == 8u) ? 1 : -1];
typedef char SfCheckSize[(sizeof(size_t) == 8u) ? 1 : -1];

typedef enum SfStatus {
    SF_OK = 0,
    SF_ERR_ARGUMENT = -1,
    SF_ERR_RANGE = -2,
    SF_ERR_OVERFLOW = -3,
    SF_ERR_CAPACITY = -4,
    SF_ERR_ALIGNMENT = -5,
    SF_ERR_RIGHTS = -6,
    SF_ERR_BUSY = -7,
    SF_ERR_STALE = -8,
    SF_ERR_TRUNCATED = -9,
    SF_ERR_FORMAT = -10,
    SF_ERR_VERSION = -11,
    SF_ERR_PADDING = -12,
    SF_ERR_CHECKSUM = -13,
    SF_ERR_HASH = -14,
    SF_ERR_UNSUPPORTED = -15,
    SF_ERR_HARDWARE = -16,
    SF_ERR_IO = -17,
    SF_ERR_FLUSH = -18,
    SF_ERR_INCOMPLETE = -19,
    SF_ERR_AUDIT_FULL = -20,
    SF_ERR_NOT_DURABLE = -21,
    SF_ERR_POLICY = -22,
    SF_ERR_STATE = -23,
    SF_ERR_EXHAUSTED = -24,
    SF_ERR_FUEL = -25,
    SF_ERR_GAP = -26,
    SF_ERR_NOT_TESTED = -27,
    SF_ERR_INCONSISTENT = -28,
    SF_ERR_SOURCE = -29,
    SF_ERR_EXISTS = -30
} SfStatus;

typedef enum SfActor {
    SF_ACTOR_NONE = 0,
    SF_ACTOR_FOUNDATION = 1,
    SF_ACTOR_SHAKTI = 2,
    SF_ACTOR_GUEST = 3,
    SF_ACTOR_LOCAL_OWNER = 4,
    SF_ACTOR_TEST = 5
} SfActor;

typedef enum SfEvidence {
    SF_EVIDENCE_DIRECT = 1,
    SF_EVIDENCE_DECLARED = 2,
    SF_EVIDENCE_DERIVED = 3
} SfEvidence;

typedef enum SfProof {
    SF_PROOF_NOT_RUN = 0,
    SF_PROOF_REVIEWED = 1,
    SF_PROOF_COMPILED = 2,
    SF_PROOF_SOFTWARE_PASS = 3,
    SF_PROOF_HARDWARE_PASS = 4,
    SF_PROOF_FAIL = 5
} SfProof;

typedef struct SfHash256 {
    uint8_t bytes[32];
} SfHash256;

typedef struct SfSha256 {
    uint32_t state[8];
    uint8_t block[64];
    uint64_t total_bytes;
    uint32_t block_used;
    uint32_t finalized;
} SfSha256;

typedef struct SfObject {
    uint64_t id;
    uint64_t generation;
} SfObject;

typedef struct SfSpan {
    uint32_t region_id;
    uint32_t rights;
    uint64_t offset;
    uint64_t length;
    uint64_t generation;
} SfSpan;

typedef struct SfFault {
    SfStatus status;
    uint32_t resource_id;
    uint64_t requested;
    uint64_t capacity;
    uint64_t sequence;
} SfFault;

/* Native structs are logical values. Never serialize their object bytes. */
SfStatus sf_checked_add_u64(uint64_t a, uint64_t b, uint64_t *sum);
SfStatus sf_checked_mul_u64(uint64_t a, uint64_t b, uint64_t *product);
SfStatus sf_check_span(uint64_t capacity, uint64_t offset, uint64_t length);
SfStatus sf_bytes_copy(uint8_t *destination, size_t destination_capacity,
                       const uint8_t *source, size_t source_length);
SfStatus sf_bytes_clear(uint8_t *destination, size_t destination_capacity,
                        size_t count);
SfStatus sf_bytes_equal(const uint8_t *a, const uint8_t *b, size_t count,
                        uint32_t *equal);
SfStatus sf_crc32c(const uint8_t *data, size_t length, uint32_t *result);
SfStatus sf_sha256(const uint8_t *data, size_t length, SfHash256 *result);
SfStatus sf_sha256_begin(SfSha256 *context);
SfStatus sf_sha256_update(SfSha256 *context, const uint8_t *data, size_t length);
SfStatus sf_sha256_end(SfSha256 *context, SfHash256 *result);

#endif
