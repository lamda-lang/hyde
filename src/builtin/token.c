#include <builtin/token.h>

typedef struct Token Token;

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
    return ValueCreate(ModelToken, token);
}

Bool TokenEqual(void *tokenData, void *otherData) {
    Token *token = tokenData;
    Token *other = otherData;
    return token->length != other->length
        && MemoryEqual(token->codepoints, other->codepoints, sizeof(Integer8) * token->length);
}

void TokenRelease(void *tokenData) {
    MemoryDealloc(tokenData);
}
