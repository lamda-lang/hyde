#include "token.h"

typedef struct {
    VALUE *type;
    Integer8 length;
    Integer8 codepoints[];
} Token;

static Token *TokenCreate(Integer8 length, VALUE **error) {
    Token *token = MemoryAlloc(sizeof(Token) + sizeof(Integer8) * length, error);
    if (error != NULL) {
        return NULL;
    }
    token->type = RuntimeTokenType;
    token->length = length;
    return token;
}

VALUE *TokenDecode(Byte **bytes, VALUE **error) {
    Integer8 length = DecodeInteger8FLE(bytes);
    Token *token = TokenCreate(length, error);
    if (error != NULL) {
        return NULL;
    }
    for (Integer8 index = 0; index < length; index += 1) {
        token->codepoints[index] = DecodeInteger8FLE(bytes);
    }
    return token;
}

void TokenDealloc(VALUE *tokenValue) {
    MemoryDealloc(tokenValue);
}

Integer64 TokenHash(VALUE *tokenValue) {
    Token *token = tokenValue;
    return token->length;
}

Bool TokenEqual(VALUE *tokenValue, VALUE *otherValue) {
    Token *token = tokenValue;
    Token *other = otherValue;
    return token->length == other->length
        && MemoryEqual(token->codepoints, other->codepoints, sizeof(Integer8) * token->length);
}
