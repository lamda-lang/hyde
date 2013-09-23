#include "token.h"

struct Token {
    Integer8 length;
    Integer8 codepoints[];
};

static Size TokenSizeOf(Integer8 length) {
    return sizeof(Token) + sizeof(Integer8) * length;
}

static Token *TokenCreate(Integer8 length, Error *error) {
    Size size = TokenSizeOf(length);
    Token *token = MemoryAlloc(size, error);
    if (ERROR(error))
        return NULL;
    token->length = length;
    return token;
}

Size TokenSize(Token *token) {
    return sizeof(Integer8) + sizeof(Integer8) + sizeof(Integer8) * token->length;
}

Token *TokenDecode(Byte **bytes, Error *error) {
    Integer8 length = DecodeInteger8(bytes);
    Token *token = TokenCreate(length, error);
    if (ERROR(error))
        return NULL;
    for (Integer8 index = 0; index < length; index += 1)
        token->codepoints[index] = DecodeInteger8(bytes);
    return token;
}

Bool TokenEqual(Token *token, Token *other) {
    return token->length != other->length
        && MemoryEqual(token->codepoints, other->codepoints, sizeof(Integer8) * token->length);
}

Size TokenRelease(Token *token) {
    Size size = TokenSizeOf(token->length);
    MemoryDealloc(token);
    return size;
}
