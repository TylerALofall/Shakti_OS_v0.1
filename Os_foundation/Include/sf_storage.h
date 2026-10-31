#ifndef SF_STORAGE_H
#define SF_STORAGE_H

#include "sf_config.h"

typedef enum SfDurability {
    SF_DURABILITY_NONE = 0,
    SF_DURABILITY_RAM_ONLY = 1,
    SF_DURABILITY_COMMITTED = 2
} SfDurability;

typedef enum SfAuthorization {
    SF_AUTH_UNKNOWN = 0,
    SF_AUTH_ALLOWED = 1,
    SF_AUTH_DENIED = 2
} SfAuthorization;

typedef enum SfTestOutcome {
    SF_TEST_NOT_RUN = 0,
    SF_TEST_PASS = 1,
    SF_TEST_FAIL = 2
} SfTestOutcome;

typedef struct SfDiskExtent {
    uint64_t first_lba;
    uint64_t lba_count;
    uint32_t sector_bytes;
    uint32_t owner;
    uint32_t rights;
    uint32_t id;
} SfDiskExtent;

typedef struct SfAuditInput {
    uint32_t kind;
    uint32_t flags;
    uint64_t sequence;
    uint64_t logical_tick;
    uint64_t epoch;
    uint64_t subject_id;
    const uint8_t *payload;
    size_t payload_length;
} SfAuditInput;

typedef struct SfAuditReceipt {
    uint64_t sequence;
    uint64_t segment;
    uint64_t offset;
    SfHash256 record_hash;
    uint32_t durability;
    SfStatus status;
} SfAuditReceipt;

typedef struct SfBaseline {
    SfObject object;
    SfHash256 content_hash;
    uint64_t byte_length;
    uint32_t extent_id;
    uint32_t consistent_source;
} SfBaseline;

typedef struct SfTrial {
    SfObject object;
    SfObject baseline;
    uint64_t owner_request;
    uint64_t changed_blocks;
    uint32_t policy_id;
    uint32_t state;
} SfTrial;

typedef struct SfTrialResult {
    SfObject trial;
    uint64_t changed_blocks;
    uint32_t authorization;
    uint32_t test_outcome;
    uint32_t test_id;
    uint32_t policy_id;
    SfHash256 receipt_hash;
} SfTrialResult;

SfStatus sf_block_read(uint32_t extent_id, uint64_t logical_block,
                       uint32_t block_count, uint8_t *output, size_t capacity);
SfStatus sf_block_write(uint32_t extent_id, uint64_t logical_block,
                        uint32_t block_count, const uint8_t *input,
                        size_t length, uint64_t owner_request);
SfStatus sf_block_flush(uint32_t extent_id);
SfStatus sf_audit_append(const SfAuditInput *input, SfAuditReceipt *receipt);
SfStatus sf_audit_recover(uint32_t extent_id, SfAuditReceipt *last_committed,
                         SfFault *fault);
SfStatus sf_baseline_register(const SfBaseline *baseline);
SfStatus sf_trial_begin(const SfObject *baseline, uint64_t owner_request,
                        uint32_t policy_id, SfTrial *trial);
SfStatus sf_trial_read(const SfObject *trial, uint64_t offset,
                       uint8_t *output, size_t length);
SfStatus sf_trial_write(const SfObject *trial, uint64_t offset,
                        const uint8_t *input, size_t length,
                        uint64_t owner_request, SfAuditReceipt *receipt);
SfStatus sf_trial_run(const SfObject *trial, uint32_t test_id,
                      uint64_t fuel, SfTrialResult *result);
SfStatus sf_trial_result(const SfObject *trial, SfTrialResult *result);

#endif
