#include "kernel.h"

struct Kernel {
    Value base;
    Integer8 arity;
    Type type[8];
    KernelFunction *function;
};

static Kernel kernel[] = {
    [KernelIdentifierIntegerSum] = {
	.base = TypeLamda | FlagKernel,
	.arity = 2,
	.type = {TypeInteger, TypeInteger},
	.function = IntegerSum
    },
    [KernelIdentifierStringConcatenate] = {
	.base = TypeLamda | FlagKernel,
	.arity = 2,
	.type = {TypeString, TypeString},
	.function = StringConcatenate
    },
    [KernelIdentifierDoPrint] = {
	.base = TypeDo | FlagKernel,
	.arity = 1,
	.type = {TypeString},
	.function = StringPrint
    }
};

Kernel *KernelWithIdentifier(KernelIdentifier id) {
    return &kernel[id];
}
