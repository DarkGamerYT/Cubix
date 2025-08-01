#ifndef COMMANDSTATUS_HPP
#define COMMANDSTATUS_HPP

#include <cstdint>

enum class CommandStatus : int32_t {
    FailedToParseCommand       = -2147483648,
    CommandNotFound            = -2147483647,
    NotEnoughPermissions       = -2147483646,
    CommandVersionMismatch     = -2147483645,
    InvalidOverloadSyntax      = -2147483644,
    InvalidCommandContext      = -2147483643,
    InvalidCommandCall         = -2147483642,
    CommandsDisabled           = -2147483641,
    NoChatPermissions          = -2147483640,
    NoTargetFound              = -2147483639,
    ChatMuted                  = -2147483638,
    InvalidCommandOrigin       = -2147483637,
    ExpectedRequestMsg         = -2147418112,
    MalformedRequest           = -2147418111,
    VersionMismatch            = -2147418110,
    TooManyPendingRequests     = -2147418109,
    MustSpecifyVersion         = -2147418108,
    EncryptionRequired         = -2147418107,
    ExecutionFail              = -2147352576,
    CommandStepFail            = -2147352575,
    AllTargetsWillFail         = -2147352574,
    FailWithoutFailMsg         = -2147352573,
    Success                    = 0,
    CommandStepDone            = 131073,
    CommandExeIncomplete       = 131074,
    CommandRequestInitiated    = 131075,
    NewCommandVersionAvailable = 131076
};

#endif //COMMANDSTATUS_HPP
