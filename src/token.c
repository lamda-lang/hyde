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

Value *TokenDecode(Binary *binary, Integer32 *offset) {
    Integer8 length;
    if (!BinaryDecodeInteger8(binary, offset, &length))
        return NULL;
    Token *token = TokenCreate(length);
    for (Integer8 index = 0; index < length; index += 1) {
        Integer8 codepoint;
        if (!BinaryDecodeInteger8(binary, offset, &codepoint))
            goto out;
        token->codepoints[index] = codepoint;
    }
    return ValueCreateToken(token);

out:
    TokenDealloc(token);
    return NULL;
}
