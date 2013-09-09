#include <builtin/token.h>

typedef struct Token Token;

struct Token {
    Integer8 length;
    Integer8 codepoints[];
};

static Token *TokenCreate(Integer8 length, Error *error) {
    Token *token = MemoryAlloc(sizeof(Token) + sizeof(Integer8) * length, error);
    if (*error != ErrorNone)
        return NULL;
    token->length = length;
    return token;
}

static void TokenDealloc(Token *token) {
    MemoryDealloc(token);
}

Value *TokenDecode(Byte **bytes, Error *error) {
    Integer8 length = DecodeInteger8(bytes);
    Token *token = TokenCreate(length, error);
    if (*error != ErrorNone)
        return NULL;
    for (Integer8 index = 0; index < length; index += 1)
        token->codepoints[index] = DecodeInteger8(bytes);
    return ValueCreate(BuiltinToken, token, error);
}

Bool TokenEqual(void *tokenModel, void *otherModel) {
    Token *token = tokenModel;
    Token *other = otherModel;
    if (token->length != other->length)
        return FALSE;
    return MemoryEqual(token->codepoints, other->codepoints, sizeof(Integer8) * token->length);
}

void TokenRelease(void *tokenModel) {
    TokenDealloc(tokenModel);
}
