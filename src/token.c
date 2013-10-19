#include "token.h"

struct Token {
    Integer8 length;
    Integer8 codepoints[];
};

static Token *TokenCreate(Integer8 length) {
    Token *token = MemoryAllocRegion(sizeof(Token), sizeof(Integer8), length);
    token->length = length;
    return token;
}

static void TokenDealloc(Token *token) {
    MemoryDealloc(token);
}

Bool TokenDecode(Binary *binary, Integer32 *offset, Value **value) {
    Integer8 length;
    if (!BinaryDecodeInteger8(binary, offset, &length))
        return FALSE;
    Token *token = TokenCreate(length);
    for (Integer8 index = 0; index < length; index += 1) {
        Integer8 codepoint;
        if (!BinaryDecodeInteger8(binary, offset, &codepoint))
            goto out;
        token->codepoints[index] = codepoint;
    }
    *value = ValueCreateToken(token);
    return TRUE;

out:
    TokenDealloc(token);
    return FALSE;
}
