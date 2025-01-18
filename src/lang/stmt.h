#pragma once

typedef enum {
    STMT_DEFINE,
    STMT_DEFINE_NODE,
    // STMT_DEFINE_RULE,
} stmt_kind_t;


struct stmt_t {
    stmt_kind_t kind;
    // union {
    // };
};
