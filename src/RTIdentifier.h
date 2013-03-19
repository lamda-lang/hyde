/** @module RTIdentifier 
    @brief API for primitive of type @code{RTIdentifier}. */

#ifndef RT_IDENTIFIER
#define RT_IDENTIFIER

#include "Runtime.h"

/**  */
RTIdentifier RTIdentifierCreate(RTInteger8Bit length);

/**  */
void RTIdentifierDealloc(void *id_RTIdentifier);

/**  */
void RTIdentifierDecode(RTIdentifier id, RTByte **data, RTInteger8Bit length);

/**  */
RTBool RTIdentifierEqual(void *id_RTIdentifier, void *other_RTIdentifier);

/**  */
RTInteger32Bit RTIdentifierHash(void *id_RTIdentifier);

#endif
