#ifndef SF_OBSERVER_H
#define SF_OBSERVER_H

#include "sf_memory.h"

typedef enum SfCaptureMode {
    SF_CAPTURE_LIVE = 1,
    SF_CAPTURE_QUIESCED = 2
} SfCaptureMode;

typedef enum SfConsistency {
    SF_CONSISTENCY_LIVE = 1,
    SF_CONSISTENCY_QUIESCED = 2,
    SF_CONSISTENCY_INCOMPLETE = 3
} SfConsistency;

typedef enum SfTraceKind {
    SF_TRACE_ENTER = 1,
    SF_TRACE_LEAVE = 2,
    SF_TRACE_STAGE = 3,
    SF_TRACE_READ = 4,
    SF_TRACE_WRITE = 5,
    SF_TRACE_COMPARE = 6,
    SF_TRACE_FAULT = 7,
    SF_TRACE_GAP = 8
} SfTraceKind;

typedef enum SfValueKind {
    SF_VALUE_NONE = 0,
    SF_VALUE_U64 = 1,
    SF_VALUE_I64_BITS = 2,
    SF_VALUE_GUEST_PC = 3,
    SF_VALUE_STATUS = 4,
    SF_VALUE_COUNT = 5
} SfValueKind;

typedef struct SfTraceEvent {
    uint64_t sequence;
    uint64_t logical_tick;
    uint64_t epoch;
    SfHash256 build_id;
    uint32_t source_file;
    uint32_t source_function;
    uint32_t kind;
    uint32_t evidence;
    uint32_t value_kind;
    uint64_t object_id;
    uint64_t offset;
    uint64_t length;
    uint64_t value;
    uint64_t generation;
} SfTraceEvent;

typedef struct SfCaptureResult {
    SfSpan published;
    SfHash256 content_hash;
    uint64_t start_sequence;
    uint64_t end_sequence;
    uint64_t epoch;
    uint32_t consistency;
    uint32_t evidence;
    uint32_t frozen_vcpu_mask;
    uint32_t dma_quiesced;
} SfCaptureResult;

SfStatus sf_observe_capture(const SfSpan *subject, uint32_t mode,
                            uint64_t fuel, SfCaptureResult *capture,
                            SfFault *fault);
SfStatus sf_observe_release(const SfCaptureResult *capture);
SfStatus sf_trace_emit(const SfTraceEvent *event);
SfStatus sf_trace_encode(const SfTraceEvent *event,
                         uint8_t *output, size_t capacity);
SfStatus sf_trace_decode(const uint8_t *input, size_t length,
                         SfTraceEvent *event);
SfStatus sf_trace_read(uint64_t first_sequence, SfTraceEvent *events,
                       size_t capacity, size_t *count, uint64_t *next_sequence);

#endif
