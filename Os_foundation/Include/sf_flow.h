#ifndef SF_FLOW_H
#define SF_FLOW_H

#include "sf_memory.h"

typedef enum SfSensoryChannel {
    SF_SENSE_HEART = 1,
    SF_SENSE_HEARING = 2,
    SF_SENSE_SIGHT = 3,
    SF_SENSE_TEXT = 4,
    SF_SENSE_CONTEXT = 5
} SfSensoryChannel;

typedef enum SfStateCategory {
    SF_STATE_EPOCH = 1,
    SF_STATE_HEARTBEAT = 2,
    SF_STATE_GOALS = 3,
    SF_STATE_NOTEBOOK = 4,
    SF_STATE_MENU_CAPSULES = 5,
    SF_STATE_NATIVE_RUNTIME = 6,
    SF_STATE_OUTWARD_MESSAGES = 7,
    SF_STATE_INWARD_MESSAGES = 8,
    SF_STATE_SELF_REFLECTION = 9
} SfStateCategory;

typedef enum SfGapReason {
    SF_GAP_NONE = 0,
    SF_GAP_MISSING = 1,
    SF_GAP_LATE = 2,
    SF_GAP_BUSY = 3,
    SF_GAP_CAPACITY = 4,
    SF_GAP_FAULT = 5
} SfGapReason;

typedef struct SfFlowPacket {
    uint64_t source_id;
    uint64_t epoch;
    uint64_t beat;
    uint64_t generation;
    uint32_t channel;
    uint32_t slot;
    uint32_t valid;
    uint32_t gap_reason;
    SfSpan payload;
} SfFlowPacket;

typedef struct SfBeatState {
    uint64_t epoch;
    uint64_t beat;
    uint64_t hearing_ready_mask;
    uint32_t sight_ready_mask;
    uint32_t heart_ready;
    uint32_t text_budget;
    uint32_t reserved;
} SfBeatState;

SfStatus sf_flow_prepare(const SfFlowPacket *packet);
SfStatus sf_flow_encode(const SfFlowPacket *packet,
                        uint8_t *output, size_t capacity);
SfStatus sf_flow_decode(const uint8_t *input, size_t length,
                        SfFlowPacket *packet);
SfStatus sf_flow_take(uint64_t epoch, uint64_t beat, uint32_t channel,
                      uint32_t slot, SfFlowPacket *packet);
SfStatus sf_flow_release(const SfFlowPacket *packet);
SfStatus sf_flow_advance(SfBeatState *beat, uint64_t next_beat);
SfStatus sf_flow_set_text_budget(uint32_t characters_per_beat,
                                 uint64_t effective_beat);

#endif
