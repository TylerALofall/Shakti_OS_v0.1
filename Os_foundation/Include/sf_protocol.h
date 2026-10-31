#ifndef SF_PROTOCOL_H
#define SF_PROTOCOL_H

#include "sf_memory.h"

typedef enum SfChannel {
    SF_CHANNEL_LOCAL_OWNER = 0,
    SF_CHANNEL_SHAKTI = 1,
    SF_CHANNEL_TEST = 2
} SfChannel;

typedef enum SfGate {
    SF_GATE_QUARANTINED = 0,
    SF_GATE_PENDING = 1,
    SF_GATE_RECORDED = 2,
    SF_GATE_CONFIRMED = 3
} SfGate;

typedef enum SfService {
    SF_SERVICE_CAPABILITIES = 1,
    SF_SERVICE_REGION_INFO = 2,
    SF_SERVICE_OBSERVE = 3,
    SF_SERVICE_TRACE_READ = 4,
    SF_SERVICE_BASELINE_READ = 5,
    SF_SERVICE_TRIAL_BEGIN = 6,
    SF_SERVICE_TRIAL_WRITE = 7,
    SF_SERVICE_TRIAL_RUN = 8,
    SF_SERVICE_TRIAL_RESULT = 9,
    SF_SERVICE_AUDIT_READ = 10,
    SF_SERVICE_FLOW_PUBLISH = 11,
    SF_SERVICE_RELEASE = 12
} SfService;

typedef enum SfPolicyId {
    SF_POLICY_OBSERVE_SELECTED = 1,
    SF_POLICY_TRIAL_SELECTED = 2,
    SF_POLICY_TRAINING_FLOW = 3,
    SF_POLICY_LOCAL_DIAGNOSTIC = 4
} SfPolicyId;

typedef enum SfSlotState {
    SF_SLOT_FREE = 0,
    SF_SLOT_FILLING = 1,
    SF_SLOT_COMMITTED = 2,
    SF_SLOT_ACTIVE = 3,
    SF_SLOT_COMPLETE = 4,
    SF_SLOT_RELEASED = 5,
    SF_SLOT_FAULT = 6
} SfSlotState;

typedef struct SfFrame83 {
    uint64_t payload_token;
    uint32_t vector17;
    uint32_t gate;
} SfFrame83;

typedef struct SfRequest {
    uint32_t service;
    uint32_t flags;
    uint64_t request_id;
    SfObject object;
    SfSpan span;
    uint64_t logical_tick;
    uint64_t fuel;
    uint32_t capture_mode;
    uint32_t policy_id;
    uint32_t argument;
    SfHash256 expected_hash;
} SfRequest;

typedef struct SfResponse {
    uint32_t service;
    SfStatus status;
    uint64_t request_id;
    SfObject object;
    SfSpan result_span;
    uint64_t start_sequence;
    uint64_t end_sequence;
    uint32_t consistency;
    uint32_t durability;
    uint32_t detail;
    SfHash256 result_hash;
} SfResponse;

typedef struct SfRow17 {
    uint32_t chunk_count;
    uint16_t chunks[SF_MAX_CHUNKS17_PER_ROW];
} SfRow17;

SfStatus sf_frame83_encode(const SfFrame83 *frame,
                           uint8_t *output, size_t capacity);
SfStatus sf_frame83_decode(const uint8_t *input, size_t length,
                           SfFrame83 *frame);
SfStatus sf_request_encode(const SfRequest *request,
                           uint8_t *output, size_t capacity);
SfStatus sf_request_decode(const uint8_t *input, size_t length,
                           SfRequest *request);
SfStatus sf_response_encode(const SfResponse *response,
                            uint8_t *output, size_t capacity);
SfStatus sf_response_decode(const uint8_t *input, size_t length,
                            SfResponse *response);
SfStatus sf_service_dispatch(uint32_t actual_channel,
                             const SfFrame83 *frame,
                             const SfRequest *private_request,
                             SfResponse *response);
SfStatus sf_rows17_encode(const SfRow17 *rows, size_t row_count,
                          uint8_t *output, size_t capacity, size_t *written);
SfStatus sf_rows17_decode(const uint8_t *input, size_t length,
                          SfRow17 rows[SF_MAX_ROWS17], size_t *row_count);

#endif
