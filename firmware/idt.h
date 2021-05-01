#include "../lib/type.h"

// Segment selectors
#define KERNEL_CS 0x08
#define IDT_ENTRIES 256

typedef struct
{
    word low_offset; // lower 16 bits of handler address
    word selector; // kernel seg selector
    byte always0;
    byte flags;
    word high_offset;
} __attribute__((packed)) idt_gate_t;

// pointer to interrupt handler array
typedef struct
{
    word limit;
    uint32_t base;
} __attribute__((packed)) idt_register_t;

static idt_gate_t idt[IDT_ENTRIES];
static idt_register_t idt_reg;

void set_idt_gate(int n, uint32_t handler);
void apply_idt();
