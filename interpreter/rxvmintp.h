#ifndef CREXX_RXVMINTP_H
#define CREXX_RXVMINTP_H

#include "rxas.h"

#define rxversion "cREXX I0265"

#define SMALLEST_STRING_BUFFER_LENGTH 32

typedef struct value value;
typedef struct stack_frame stack_frame;

typedef union {
    struct {
        unsigned int type_object : 1;
        unsigned int type_string : 1;
        unsigned int type_decimal : 1;
        unsigned int type_float : 1;
        unsigned int type_int : 1;
    };
    unsigned int all_type_flags;
} value_type;

struct value {
    /* bit field to store value status - these are explicitly set (not automatic at all) */
    value_type status;

    /* Value */
    rxinteger int_value;
    double float_value;
    void *decimal_value; /* TODO */
    char *string_value;
    size_t string_length;
    size_t string_buffer_length;
    size_t string_pos;
#ifndef NUTF8
    size_t string_chars;
    size_t string_char_pos;
#endif
    void *object_value;
    char small_string_buffer[SMALLEST_STRING_BUFFER_LENGTH];
};

/* Module Structure */
typedef struct module {
    bin_space segment;
    char *name;
    value **globals;
} module;

struct stack_frame {
    stack_frame *prev_free;
    stack_frame *parent;
    proc_constant *procedure;
    void *return_inst;
    bin_code *return_pc;
    value *return_reg;
    size_t number_locals;
    size_t nominal_number_locals;
    size_t number_args;
    value **baselocals; /* Initial / base / fixed local pointers */
    value **locals;   /* Locals pointer mapping (after swaps / links */
};

#ifdef NDEBUG  // RELEASE
    #define DEBUG(...) (void)0
#else          // DEBUG
    #define DEBUG(...) if (debug_mode) fprintf(stderr, __VA_ARGS__)
#endif

#define RXERROR(...)   { fprintf(stderr, __VA_ARGS__); goto SIGNAL; }
#define MAP_ADDR(instr, op1, op2, op3, target, msg)             \
                instruction = src_inst(instr, op1,op2,op3);     \
                address_map[instruction->opcode] = target;

#ifdef NTHREADED

#define START_OF_INSTRUCTIONS CASE_START:; switch ((enum instructions)(pc->instruction.opcode)) {
#define END_OF_INSTRUCTIONS }
#define START_INSTRUCTION(inst) case INST_ ## inst:
#define START_BREAKPOINT BREAKPOINT:
#define END_BREAKPOINT goto CASE_START;
#define CALC_DISPATCH(n)           { next_pc = pc + (n) + 1; }
#define CALC_DISPATCH_MANUAL
#define DISPATCH                   { pc = next_pc; goto *(check_breakpoint)?&&BREAKPOINT:&&CASE_START; }

#else

#define START_OF_INSTRUCTIONS
#define END_OF_INSTRUCTIONS
#define START_INSTRUCTION(inst) inst:
#define START_BREAKPOINT BREAKPOINT:
#define END_BREAKPOINT goto *next_inst;
#define CALC_DISPATCH(n)           { next_pc = pc + (n) + 1; next_inst = (next_pc)->impl_address; }
#define CALC_DISPATCH_MANUAL       { next_inst = (next_pc)->impl_address; }
#define DISPATCH                   { pc = next_pc; goto *(check_breakpoint)?&&BREAKPOINT:next_inst; }

#endif

#define REG_OP(n)                    current_frame->locals[(pc+(n))->index]
#define REG_VAL(n)                   current_frame->locals[n]
#define REG_IDX(n)                   (pc+(n))->index
#define INT_OP(n)                    (pc+(n))->iconst
#define FLOAT_OP(n)                  (pc+(n))->fconst

#define CONSTSTRING_OP(n)            ((string_constant *)(current_frame->procedure->binarySpace->const_pool + (pc+(n))->index))
#define PROC_OP(n)                   ((proc_constant *)(current_frame->procedure->binarySpace->const_pool + (pc+(n))->index))
#define INT_VAL(vx)                  vx->int_value
#define FLOAT_VAL(vx)                vx->float_value

//
// PEJ Macros   April 2021

#define REG_RETURN_INT(val)        { set_int(REG_OP(1),val);}
#define REG_RETURN_FLOAT(val)      { set_float(REG_OP(1),val);  }
#define REG_RETURN_STRING(val)     { set_const_string(REG_OP(1), val);}

#define REG_RET_CHAR(val)          { v1=REG_OP(1); if (v1) set_char(v1,val);                               \
                                    else REG_OP(1) = value_char_f(current_frame,val); }
// TODO: String to integer just for real integers, or stop converting at "."
// maximum size of rxinteger is 20 digits plus sign
// maximum size of double is about 16 decimal digits plus sign

#define S2INT(t,s)                 { if ((s)->string_length>20)  goto convlength;                       \
                                    (s)->string_value[(s)->string_length]='\0';                         \
                                    (t) = strtol((s)->string_value, &converr, 0);                         \
                                    if (converr[0] != '\0' && converr[0]!='.') goto converror; }

#define S2FLOAT(t,s)              { if ((s)->string_length>16)  goto convlength;                       \
                                    (s)->string_value[(s)->string_length]='\0';                         \
                                    (t) = strtod((s)->string_value, &converr);                          \
                                    if (converr[0] != '\0') goto converror; }

#define CONV2INT(i,v)             { if ((v)->status.type_float)                                      \
                                    (i) = (rxinteger) (v)->float_value;                                 \
                                    else if ((v)->status.type_string) S2INT(i,v); }

#define CONV2FLOAT(i,v) if ((v)->status.type_int) (i) = (double) (v)->int_value;                      \
        else if ((v)->status.type_string) S2FLOAT(i,v);                                               \
                                                                                                      \
// Get Character
#ifndef NUTF8
  #define GETSTRCHAR(c,v,p) {string_set_byte_pos((v),(p)); utf8codepoint((v)->string_value+(v)->string_pos, &(c));}
#else
  #define GETSTRCHAR(c,v,p) {c=(v)->string_value[(p)]; }
#endif

#ifndef NUTF8
  #define GETSTRLEN(i,v)   { i = (rxinteger) v->string_chars; }
#else
  #define GETSTRLEN(i,v)   { i = (rxinteger) v->string_len; }
#endif

#ifndef NUTF8
  #define PUTSTRLEN(v,i)   { v->string_length=i; v->string_chars=i;}
#else
  #define PUTSTRLEN(v,i)   { v->string_length=i; }
#endif



// TODO PEJ what kind of checks must be performed in runtime/debug mode
#define REG_TEST(v)            { if (!(v)) goto notreg; }
#define op1R                     (REG_OP(1))
#define op2R                     (REG_OP(2))
#define op3R                     (REG_OP(3))
#define op1I                     (INT_OP(1))
#define op2I                     (INT_OP(2))
#define op3I                     (INT_OP(3))
#define op1F                     (FLOAT_OP(1))
#define op2F                     (FLOAT_OP(2))
#define op3F                     (FLOAT_OP(3))
#define op1S                     (CONSTSTRING_OP(1))
#define op2S                     (CONSTSTRING_OP(2))
#define op3S                     (CONSTSTRING_OP(3))
#define op1RI                    (INT_VAL(op1R))
#define op2RI                    (INT_VAL(op2R))
#define op3RI                    (INT_VAL(op3R))
#define op2RF                    (FLOAT_VAL(op2R))
#define op3RF                    (FLOAT_VAL(op3R))
#define REG_OP_TEST(v,n)        { (v) = REG_OP(n);}
//#define REG_OP_TEST_INT(v,n)   { (v) = REG_OP(n); REG_TEST(v);                                      \
//                                 if ((v)->status.type_int==0)  goto notint; }
//#define REG_OP_TEST_FLOAT(v,n)  { (v) = REG_OP(n); REG_TEST(v);                                      \
//                                   if ((v)->status.type_float==0)  goto notfloat; }
#define REG_OP_TEST_INT(v,n)    { (v) = REG_OP(n);}
#define REG_OP_TEST_FLOAT(v,n)  { (v) = REG_OP(n);}



/* Signals an error - this function does not return */
void dosignal(int code);

int initialz();
int finalize();
int run(int num_modules, module *program, int argc, char *argv[], int debug_mode);

#endif //CREXX_RXVMINTP_H
