#include <string.h>
#include "token.h"

struct Token {
    Type *type;
    Integer8 length;
    Integer8 codepoint[];
};

typedef struct {
    Integer8 length;
    Integer8 codepoint[];
} Model;

static Token *Create(Integer8 length, VALUE **error) {
    Token *token = MemoryAlloc(sizeof(Token) + sizeof(Integer8) * length, error);
    if (token == NULL) {
        goto returnVALUE;
    }
    token->type = TypeToken;
    token->length = length;
    return token;

returnVALUE:
    return NULL;
}

void *TokenDecode(Byte **bytes, VALUE **error) {
    Integer8 length = DecodeInteger8FLE(bytes);
    Model *model = MemoryAlloc(sizeof(Model) + sizeof(Integer8) * length, error);
    if (model == NULL) {
        goto returnVALUE;
    }
    for (Integer8 index = 0; index < length; index += 1) {
        model->codepoint[index] = DecodeInteger8FLE(bytes);
    }
    return model;

returnVALUE:
    return NULL;
}

VALUE *TokenCreateWithCharacters(Char *chars, VALUE **error) {
    Integer8 length = strnlen(chars, 0XF) & 0XF;
    Token *token = Create(length, error);
    if (token == NULL) {
        goto returnVALUE;
    }
    MemoryCopy(chars, token->codepoint, length);
    return BridgeFromToken(token);

returnVALUE:
    return NULL;
}

void TokenDealloc(VALUE *tokenVALUE) {
    MemoryDealloc(tokenVALUE);
}

Integer64 TokenHash(VALUE *tokenVALUE) {
    return BridgeToToken(tokenVALUE)->length;
}

Bool TokenEqual(VALUE *tokenVALUE, VALUE *otherVALUE) {
    Token *token = BridgeToToken(tokenVALUE);
    Token *other = BridgeToToken(otherVALUE);
    return token->length == other->length &&
           MemoryEqual(token->codepoint, other->codepoint, sizeof(Integer8) * token->length);
}
