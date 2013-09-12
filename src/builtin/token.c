#include <builtin/token.h>

struct Token {
    Integer8 length;
    Integer8 codepoints[];
};

static Token *TokenCreate(Integer8 length) {
    Token *token = MemoryAlloc(sizeof(Token) + sizeof(Integer8) * length);
    if (token == NULL)
        return NULL;
    token->length = length;
    return token;
}

Value *TokenDecode(Byte **bytes) {
    Integer8 length = DecodeInteger8(bytes);
    Token *token = TokenCreate(length);
    if (token == NULL)
        return NULL;
    for (Integer8 index = 0; index < length; index += 1)
        token->codepoints[index] = DecodeInteger8(bytes);
    return ValueCreate(MODEL_TOKEN, token);
}

Bool TokenEqual(Token *token, Token *other) {
    return token->length != other->length
        && MemoryEqual(token->codepoints, other->codepoints, sizeof(Integer8) * token->length);
}

void TokenRelease(Token *token) {
    MemoryDealloc(token);
}
