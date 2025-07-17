#pragma once
#include <cstdint>

enum class MolangVersion : int32_t {
    Invalid                                = 0xFF,
    BeforeVersioning                       = 0x0000,
    Initial                                = 0x0001,
    FixedItemRemainingUseDurabilityQuery   = 0x0002,
    ExpressionErrorMessages                = 0x0003,
    UnexpectedOperatorErrors               = 0x0004,
    ConditionalOperatorAssociativity       = 0x0005,
    ComparisonAndLogicalOperatorPrecedence = 0x0006,
    DivideByNegativeValue                  = 0x0007,
    FixedCapeFlapAmountQuery               = 0x0008,
    QueryBlockPropertyRenamedToState       = 0x0009,
    DeprecateOldBlockQueryNames            = 0x000a,
    DeprecateSnifferAndCamelQueries        = 0x000b,
    LeafSupportingInFirstSolidBlockBelow   = 0x000c,

    NumValidVersions                       = 0x000d,
    Latest                                 = 0x000c,
    HardcodedMolang                        = 0x000c
};