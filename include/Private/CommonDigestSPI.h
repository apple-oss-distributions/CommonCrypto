/*
 * Copyright (c) 2010 Apple Inc. All Rights Reserved.
 *
 * @APPLE_LICENSE_HEADER_START@
 *
 * This file contains Original Code and/or Modifications of Original Code
 * as defined in and that are subject to the Apple Public Source License
 * Version 2.0 (the 'License'). You may not use this file except in
 * compliance with the License. Please obtain a copy of the License at
 * http://www.opensource.apple.com/apsl/ and read it before using this
 * file.
 *
 * The Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT.
 * Please see the License for the specific language governing rights and
 * limitations under the License.
 *
 * @APPLE_LICENSE_HEADER_END@
 */

#ifndef	_CC_DigestSPI_H_
#define _CC_DigestSPI_H_

#include <stdint.h>
#include <sys/types.h>
#include <os/availability.h>

#ifdef __cplusplus
extern "C" {
#endif


/*!
    @enum       CCDigestAlgorithm
    @abstract   Algorithms implemented in this module.

    @constant 	kCCDigestNone		Digest Selector for "no digest"
    @constant 	kCCDigestMD2		MD2 digest, Deprecated in iPhoneOS 11.0 and MacOSX10.13
    @constant 	kCCDigestMD4		MD4 digest, Deprecated in iPhoneOS 11.0 and MacOSX10.13
    @constant 	kCCDigestMD5		MD5 digest
    @constant 	kCCDigestRMD128		RMD 128 bit digest
    @constant 	kCCDigestRMD160		RMD 160 bit digest
    @constant 	kCCDigestRMD256		RMD 256 bit digest
    @constant 	kCCDigestRMD320		RMD 320 bit digest
    @constant 	kCCDigestSHA1		SHA-1 digest
    @constant 	kCCDigestSHA224		SHA-2 224 bit digest
    @constant 	kCCDigestSHA256		SHA-2 256 bit digest
    @constant 	kCCDigestSHA384		SHA-2 384 bit digest
    @constant 	kCCDigestSHA512		SHA-2 512 bit digest
    @constant 	kCCDigestSkein128	Skein 128 bit digest, Deprecated in iPhoneOS 6.0 and MacOSX10.9
    @constant 	kCCDigestSkein160	Skein 160 bit digest, Deprecated in iPhoneOS 6.0 and MacOSX10.9
    @constant 	kCCDigestSkein224	Skein 224 bit digest, Deprecated in iPhoneOS 6.0 and MacOSX10.9
    @constant 	kCCDigestSkein256	Skein 256 bit digest, Deprecated in iPhoneOS 6.0 and MacOSX10.9
    @constant 	kCCDigestSkein384	Skein 384 bit digest, Deprecated in iPhoneOS 6.0 and MacOSX10.9
    @constant 	kCCDigestSkein512	Skein 512 bit digest, Deprecated in iPhoneOS 6.0 and MacOSX10.9
 */

enum {
    kCCDigestNone = 0,
	kCCDigestMD2 API_DEPRECATED("No longer supported", macos(10.4, 10.13), ios(5.0, 11.0))      = 1,
	kCCDigestMD4 API_DEPRECATED("No longer supported", macos(10.4, 10.13), ios(5.0, 11.0))      = 2,
	kCCDigestMD5 				= 3,
	kCCDigestRMD128				= 4,
	kCCDigestRMD160				= 5,
	kCCDigestRMD256				= 6,
	kCCDigestRMD320				= 7,
	kCCDigestSHA1				= 8,
	kCCDigestSHA224				= 9,
	kCCDigestSHA256				= 10,
	kCCDigestSHA384				= 11,
	kCCDigestSHA512				= 12,
	kCCDigestSkein128 API_DEPRECATED("No longer supported", macos(10.4, 10.9), ios(5.0, 6.0))  = 13,
	kCCDigestSkein160 API_DEPRECATED("No longer supported", macos(10.4, 10.9), ios(5.0, 6.0))  = 14,
	kCCDigestSkein224 API_DEPRECATED("No longer supported", macos(10.4, 10.9), ios(5.0, 6.0))  = 16,
	kCCDigestSkein256 API_DEPRECATED("No longer supported", macos(10.4, 10.9), ios(5.0, 6.0))  = 17,
	kCCDigestSkein384 API_DEPRECATED("No longer supported", macos(10.4, 10.9), ios(5.0, 6.0))  = 18,
	kCCDigestSkein512 API_DEPRECATED("No longer supported", macos(10.4, 10.9), ios(5.0, 6.0))  = 19,
};
typedef uint32_t CCDigestAlgorithm;

// Hold this until Heimdal has changed.

#define CCDigestAlg CCDigestAlgorithm

/*!
    @typedef    CCDigestCtx
    @abstract   Digest context.
 */

#define CC_DIGEST_SIZE 1032
typedef struct CCDigestCtx_t {
    uint8_t context[CC_DIGEST_SIZE];
} CCDigestCtx, *CCDigestRef;

#define CC_RMD128_DIGEST_LENGTH   16          /* digest length in bytes */
#define CC_RMD128_BLOCK_BYTES     64          /* block size in bytes */
#define CC_RMD128_BLOCK_LONG      (CC_RMD128_BLOCK_BYTES / sizeof(CC_LONG))

#define CC_RMD160_DIGEST_LENGTH   20          /* digest length in bytes */
#define CC_RMD160_BLOCK_BYTES     64          /* block size in bytes */
#define CC_RMD160_BLOCK_LONG      (CC_RMD160_BLOCK_BYTES / sizeof(CC_LONG))

#define CC_RMD256_DIGEST_LENGTH   32          /* digest length in bytes */
#define CC_RMD256_BLOCK_BYTES     64          /* block size in bytes */
#define CC_RMD256_BLOCK_LONG      (CC_RMD256_BLOCK_BYTES / sizeof(CC_LONG))

#define CC_RMD320_DIGEST_LENGTH   40          /* digest length in bytes */
#define CC_RMD320_BLOCK_BYTES     64          /* block size in bytes */
#define CC_RMD320_BLOCK_LONG      (CC_RMD320_BLOCK_BYTES / sizeof(CC_LONG))

/**************************************************************************/
/* SPI Only                                                               */
/**************************************************************************/

/*
 * This information will remain SPI - internal functions available
 * to callers not needing a stable ABI that have a need to provide
 * their own memory for use as contexts and return digest values.
 */


/*!
    @function   CCDigestInit
    @abstract   Initialize a CCDigestCtx for a digest.

    @param      algorithm   Digest algorithm to perform.
    @param      ctx         A digest context.

    returns 0 on success.
 */

int
CCDigestInit(CCDigestAlgorithm algorithm, CCDigestRef ctx)
API_AVAILABLE(macos(10.7), ios(5.0));



/**************************************************************************/
/* Future API                                                             */
/**************************************************************************/

/*
 * These functions will be put out for API review after this release.  For
 * right now we're "road testing" them internally.
 */

/*!
    @function   CCDigest
    @abstract   Stateless, one-shot Digest function.

    @param      algorithm   Digest algorithm to perform.
    @param      data        The data to digest.
    @param      length      The length of the data to digest.
    @param      output      The digest bytes (space provided by the caller).

    Output is written to caller-supplied buffer, as in CCDigestFinal().
 */

int
CCDigest(CCDigestAlgorithm algorithm,
         const uint8_t *data, size_t length, uint8_t *output)
API_AVAILABLE(macos(10.7), ios(5.0));

/*!
    @function   CCDigestCreate
    @abstract   Allocate and initialize a CCDigestCtx for a digest.

    @param      alg   Digest algorithm to setup.

    returns a pointer to a digestRef on success.
 */

CCDigestRef
CCDigestCreate(CCDigestAlgorithm alg)
API_AVAILABLE(macos(10.7), ios(5.0));

/*!
    @function   CCDigestUpdate
    @abstract   Continue to digest data.

    @param      ctx         A digest context.
    @param      data        The data to digest.
    @param      length      The length of the data to digest.

    returns 0 on success.
 */

int
CCDigestUpdate(CCDigestRef ctx, const void *data, size_t length)
API_AVAILABLE(macos(10.7), ios(5.0));

/*!
    @function   CCDigestFinal
    @abstract   Conclude digest operations and produce the digest output.

    @param      ctx         A digest context.
    @param      output      The digest bytes (space provided by the caller).

    returns 0 on success.
 */

int
CCDigestFinal(CCDigestRef ctx, uint8_t *output)
API_AVAILABLE(macos(10.7), ios(5.0));
/*!
    @function   CCDigestDestroy
    @abstract   Clear and free a CCDigestCtx

    @param      ctx         A digest context.
 */


void
CCDigestDestroy(CCDigestRef ctx)
API_AVAILABLE(macos(10.7), ios(5.0));

/*!
    @function   CCDigestReset
    @abstract   Clear and re-initialize a CCDigestCtx for the same algorithm.

    @param      ctx         A digest context.
 */

void
CCDigestReset(CCDigestRef ctx)
API_AVAILABLE(macos(10.7), ios(5.0));

/*!
 @function   CCDigestGetBlockSize
 @abstract   Provides the block size of the digest algorithm

 @param      algorithm         A digest algorithm selector.

 returns 0 on failure or the block size on success.
 */

size_t
CCDigestGetBlockSize(CCDigestAlgorithm algorithm)
API_AVAILABLE(macos(10.7), ios(5.0));



/*!
 @function   CCDigestGetOutputSize
 @abstract   Provides the digest output size of the digest algorithm

 @param      algorithm         A digest algorithm selector.

 returns 0 on failure or the digest output size on success.
 */

size_t
CCDigestGetOutputSize(CCDigestAlgorithm algorithm)
API_AVAILABLE(macos(10.7), ios(5.0));

/*!
 @function   CCDigestGetBlockSizeFromRef
 @abstract   Provides the block size of the digest algorithm

 @param      ctx         A digest context.

 returns 0 on failure or the block size on success.
 */

size_t
CCDigestGetBlockSizeFromRef(CCDigestRef ctx)
API_AVAILABLE(macos(10.7), ios(5.0));

// Until Heimdal Changes
// #define CCDigestBlockSize CCDigestGetBlockSizeFromRef
size_t
CCDigestBlockSize(CCDigestRef ctx)
API_DEPRECATED_WITH_REPLACEMENT("CCDigestGetBlockSizeFromRef", macos(10.7, 10.14));

/*!
 @function   CCDigestGetOutputSizeFromRef
 @abstract   Provides the digest output size of the digest algorithm

 @param      ctx         A digest context.

 returns 0 on failure or the digest output size on success.
 */

size_t
CCDigestGetOutputSizeFromRef(CCDigestRef ctx)
API_AVAILABLE(macos(10.7), ios(5.0));

// Until Heimdal Changes
// #define CCDigestOutputSize CCDigestGetOutputSizeFromRef
size_t
CCDigestOutputSize(CCDigestRef ctx)
API_AVAILABLE(macos(10.7), ios(5.0));



const uint8_t *
CCDigestOID(CCDigestRef ctx)
API_AVAILABLE(macos(10.7), ios(5.0));

size_t
CCDigestOIDLen(CCDigestRef ctx)
API_AVAILABLE(macos(10.7), ios(5.0));

CCDigestRef
CCDigestCreateByOID(const uint8_t *OID, size_t OIDlen)
API_AVAILABLE(macos(10.7), ios(5.0));



#ifdef __cplusplus
}
#endif

#endif /* _CC_DigestSPI_H_ */
