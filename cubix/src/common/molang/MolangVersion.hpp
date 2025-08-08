#pragma once
#include <cstdint>

enum class MolangVersion : int32_t {
    Invalid          = -1,
    BeforeVersioning = 0,
    Initial,
    FixedItemRemainingUseDurabilityQuery,
    ExpressionErrorMessages,
    UnexpectedOperatorErrors,
    ConditionalOperatorAssociativity,
    ComparisonAndLogicalOperatorPrecedence,
    DivideByNegativeValue,
    FixedCapeFlapAmountQuery,
    QueryBlockPropertyRenamedToState,
    DeprecateOldBlockQueryNames,
    DeprecateSnifferAndCamelQueries,
    LeafSupportingInFirstSolidBlockBelow,
    CarryingBlockQueryAllActors,

    NumValidVersions,
    Latest          = NumValidVersions - 1,
    HardcodedMolang = Latest
};