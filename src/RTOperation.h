/** @module RTOperation */

#ifndef RT_OPERATION
#define RT_OPERATION

#include "Runtime.h"

/** @brief Creates a @code{RTIdentifier} object. */
RTValue RTOperationCreateIdentifier(RTByte **instruction);

/** @brief Creates a @code{RTString} object. */
RTValue RTOperationCreateString(RTByte **instruction);

/** @brief Creates a @code{RTList} object. */
RTValue RTOperationCreateList(RTByte **instruction);

/** @brief Creates a @code{RTModule} object. */
RTValue RTOperationCreateModule(RTByte **instruction);

/** @brief Fetches the content of a @code{RTList} object. */
void RTOperationFetchList(RTByte **instruction, RTValue *reg);

/** @brief Fetches the content of a @code{RTModule} object. */
void RTOperationFetchModule(RTByte **instruction, RTValue *reg);

#endif
