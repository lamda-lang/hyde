#include <builtin/token.h>

typedef struct Token Token;

struct Token {
    Value *type;
    Integer8 length;
    Integer8 codepoints[];
};

static Token *TokenCreate(Integer8 length, Error *error) {
    Token *token = MemoryAlloc(sizeof(Token) + sizeof(Integer8) * length, error);
    if (error != NULL) return NULL;
    token->type = NULL;
    token->length = length;
    return token;
}

Value *TokenDecode(Byte **bytes, Error *error) {
    Integer8 length = DecodeInteger8(bytes);
    Token *token = TokenCreate(length, error);
    if (error != NULL) return NULL;
    for (Integer8 index = 0; index < length; index += 1) token->codepoints[index] = DecodeInteger8(bytes);
    return token;
}

void TokenDealloc(Value *tokenValue) {
    MemoryDealloc(tokenValue);
}
