#include <string.h>
#include "token.h"

struct Token {
    Value base;
    Integer8 length;
    Integer8 codepoint[];
};

typedef struct {
    Integer8 length;
    Integer8 codepoint[];
} Model;

static Token *Create(Integer8 length, Error *error) {
    Token *token = MemoryAlloc(sizeof(Token) + sizeof(Integer8) * length, error);
    if (token == NULL) {
        goto returnError;
    }
    token->base = TypeToken;
    token->length = length;
    return token;

returnError:
    return NULL;
}

void *TokenDecode(Byte **bytes, Error *error) {
    Integer8 length = DecodeInteger8FLE(bytes);
    Model *model = MemoryAlloc(sizeof(Model) + sizeof(Integer8) * length, error);
    if (model == NULL) {
        goto returnError;
    }
    for (Integer8 index = 0; index < length; index += 1) {
        model->codepoint[index] = DecodeInteger8FLE(bytes);
    }
    return model;

returnError:
    return NULL;
}

Value *TokenEval(void *data, Code *code, Value **context, Bool pure, Error *error) {
    Model *model = data;
    Token *token = Create(model->length, error);
    if (token == NULL) {
        goto returnError;
    }
    MemoryCopy(model->codepoint, token->codepoint, sizeof(Integer8) * model->length);
    return BridgeFromToken(token);

returnError:
    return NULL;
}

Value *TokenCreateWithCharacters(Char *chars, Error *error) {
    Integer8 length = strnlen(chars, 0XF) & 0XF;
    Token *token = Create(length, error);
    if (token == NULL) {
        goto returnError;
    }
    MemoryCopy(chars, token->codepoint, length);
    return BridgeFromToken(token);

returnError:
    return NULL;
}

void TokenDealloc(Value *tokenValue) {
    MemoryDealloc(tokenValue);
}

Integer64 TokenHash(Value *tokenValue) {
    return BridgeToToken(tokenValue)->length;
}

Bool TokenEqual(Value *tokenValue, Value *otherValue) {
    Token *token = BridgeToToken(tokenValue);
    Token *other = BridgeToToken(otherValue);
    return token->length == other->length &&
           MemoryEqual(token->codepoint, other->codepoint, sizeof(Integer8) * token->length);
}
