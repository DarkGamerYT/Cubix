#pragma once
#include <cstdint>

enum class CommandFlag : uint16_t {
    None                         = 0,
    TestUsage                    = 1 << 0,
    HiddenFromCommandBlockOrigin = 1 << 1,
    HiddenFromPlayerOrigin       = 1 << 2,
    HiddenFromAutomationOrigin   = 1 << 3,
    SyncLocal                    = 1 << 4,
    ExecuteDisallowed            = 1 << 5,
    TypeMessage                  = 1 << 6,
    NotCheat                     = 1 << 7,
    Async                        = 1 << 8,
    NoEditor                     = 1 << 9,
    Hidden                       = HiddenFromPlayerOrigin | HiddenFromCommandBlockOrigin,
    Removed                      = Hidden | HiddenFromAutomationOrigin
};