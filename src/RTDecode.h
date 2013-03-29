#ifndef RT_DECODE
#define RT_DECODE

#include "Runtime.h"

/** @brief Returns an @code{RTInteger8Bit} value created by decoding one byte from @code{data}.
    @arg data The byte array.
    @return An @code{RTInteger8Bit} value.
    @effect @code{*data} points one past the byte segment that contains the value. */
RTInteger8Bit RTDecodeInteger8Bit(RTByte **data);

/** @brief Returns an @code{RTInteger16Bit} value created by decoding two bytes from @code{data} using little-endian byte order.
    @arg data The byte array.
    @return An @code{RTInteger16Bit} value.
    @effect @code{*data} points one past the byte segment that contains the value. */
RTInteger16Bit RTDecodeInteger16Bit(RTByte **data);

/** @brief Returns an @code{RTInteger32Bit} value created by decoding four bytes from @code{data} using little-endian byte order.
    @arg data The byte array.
    @return An @code{RTInteger32Bit} value.
    @effect @code{*data} points one past the byte segment that contains the value. */
RTInteger32Bit RTDecodeInteger32Bit(RTByte **data);

/** @brief Returns an @code{RTInteger64Bit} value created by decoding eight bytes from @code{data} using little-endian byte order.
    @arg data The byte array.
    @return An @code{RTInteger64Bit} value.
    @effect @code{*data} points one past the byte segment that contains the value. */
RTInteger64Bit RTDecodeInteger64Bit(RTByte **data);

/** @brief Returns an @code{RTInteger32Bit} value created by decoding a variable number of bytes from @code{data} using little-endian byte order.
    @arg data The byte array.
    @return An @code{RTInteger32Bit} value.
    @effect @code{*data} points one past the byte segment that contains the value. */
RTInteger32Bit RTDecodeVBRInteger32Bit(RTByte **data);

#endif
