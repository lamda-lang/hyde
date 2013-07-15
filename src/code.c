#include "code.h"

typedef struct {
    Eval *eval;
    void *data;
} Instruction;

typedef struct {
    Decode *decode;
    Eval *eval;
} Operation;

struct Code {
    Integer32 count;
    Instruction instruction[];
};

static Operation operation[] = {
    [0] = {
        .decode = NilDecode,
        .eval = NilEval
    },
    [1] = {
        .decode = BooleanDecodeTrue,
        .eval = BooleanEval
    },
    [2] = {
        .decode = BooleanDecodeFalse,
        .eval = BooleanEval
    },
    [3] = {
        .decode = IntegerDecode,
        .eval = IntegerEval
    },
    [4] = {
        .decode = FloatDecode,
        .eval = FloatEval
    },
    [5] = {
        .decode = IdentifierDecode,
        .eval = IdentifierEval
    },
    [6] = {
        .decode = StringDecode,
        .eval = StringEval
    },
    [7] = {
        .decode = RangeDecode,
        .eval = RangeEval
    },
    [8] = {
        .decode = SetDecode,
        .eval = SetEval
    },
    [9] = {
        .decode = ListDecode,
        .eval = ListEval
    },
    [10] = {
        .decode = MapDecode,
        .eval = MapEval
    },
    [11] = {
        .decode = ModuleDecode,
        .eval = ModuleEval
    },
    [12] = {
        .decode = DoDecode,
        .eval = DoEval
    },
    [13] = {
        .decode = LamdaDecode,
        .eval = LamdaEval
    },
    [14] = {
        .decode = ImportDecode,
        .eval = ImportEval
    },
    [15] = {
        .decode = WhenDecode,
        .eval = WhenEval
    },
    [16] = {
        .decode = CaseDecode,
        .eval = CaseEval
    },
    [17] = {
        .decode = ResultDecode,
        .eval = ResultEval
    },
    [18] = {
        .decode = IdentityDecode,
        .eval = IdentityEval
    }
};

static Code *Create(Integer32 count, Error *error) {
    Code *code = MemoryAlloc(sizeof(Code) + sizeof(Instruction) * count, error);
    if (code == NULL) {
        goto returnError;
    }
    code->count = count;
    return code;

returnError:
    return NULL;
}

Code *CodeDecode(Byte **byte, Error *error) {
    Integer32 count = DecodeInteger32VLE(byte);
    Code *code = Create(count, error);
    if (code == NULL) {
        goto returnError;
    }
    for (Integer32 index = 0; index < count; index += 1) {
        Integer8 opcode = DecodeInteger8FLE(byte);
        void *data = operation[opcode].decode(byte, error);
        if (data == NULL) {
            goto returnError;
        }
        code->instruction[index].data = data;
        code->instruction[index].eval = operation[opcode].eval;
    }
    return code;

returnError:
    return NULL;
}

Value *CodeEvalInstructionAtIndex(Code *code, Value **context, Integer32 index, Bool pure, Error *error) {
    Instruction instruction = code->instruction[index];
    return instruction.eval(instruction.data, code, context, pure, error);
}
