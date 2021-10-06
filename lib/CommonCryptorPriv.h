/* 
 * Copyright (c) 2006-2010 Apple, Inc. All Rights Reserved.
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

/* 
 * CommonCryptorPriv.h - interface between CommonCryptor and operation- and
 *           algorithm-specific service providers. 
 */

#ifndef _CC_COMMON_CRYPTOR_PRIV_
#define _CC_COMMON_CRYPTOR_PRIV_

#include  <CommonCrypto/CommonCryptor.h>
#include  <CommonCrypto/CommonCryptorSPI.h>
#include "ccDispatch.h"

#include "corecryptoSymmetricBridge.h"

#ifdef DEBUG
#include <stdio.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif
    
    /* Byte-Size Constants */
#define CCMAXBUFFERSIZE 128             /* RC2/RC5 Max blocksize */
#define DEFAULT_CRYPTOR_MALLOC 4096
#define CC_STREAMKEYSCHED  2048
#define CC_MODEKEYSCHED  2048
#define CC_MAXBLOCKSIZE  128
    
typedef struct cipherMode_t {
    dispatch_once_t init;
    const struct ccmode_ecb* ecb;
    const struct ccmode_cbc* cbc;
    const struct ccmode_cfb* cfb;
    const struct ccmode_cfb8* cfb8;
    const struct ccmode_ctr* ctr;
    const struct ccmode_ofb* ofb;
    const struct ccmode_xts* xts;
    const struct ccmode_gcm* gcm;
    const struct ccmode_ccm* ccm;
} cipherMode;

#define ACTIVE 1
#define RELEASED 0xDEADBEEF
    
typedef struct _CCCryptor {
    struct _CCCryptor *compat;
#ifdef DEBUG
    uint64_t        active;
    uint64_t        cryptorID;
#endif
    uint8_t         buffptr[32];
    size_t          bufferPos;
    size_t          bytesProcessed;
    size_t          cipherBlocksize;

    CCAlgorithm     cipher;
    CCMode          mode;
    CCOperation     op;        /* kCCEncrypt, kCCDecrypt, or kCCBoth */
    
    corecryptoMode  symMode[CC_DIRECTIONS];
    const cc2CCModeDescriptor *modeDesc;
    modeCtx         ctx[CC_DIRECTIONS];
    const cc2CCPaddingDescriptor *padptr;
    
} CCCryptor;
    
static inline CCCryptor *
getRealCryptor(CCCryptorRef p, int checkactive) {
    if(!p) return NULL;
    if(p->compat) p = p->compat;
#ifdef DEBUG
    if(checkactive && p->active != ACTIVE) printf("Using Finalized Cryptor %16llx\n", p->cryptorID);
#endif
    return p;
}
    
    

    
#define CCCRYPTOR_SIZE  sizeof(struct _CCCryptor)
#define kCCContextSizeGENERIC (sizeof(struct _CCCryptor))
#define CC_COMPAT_SIZE (sizeof(void *)*2)


const corecryptoMode getCipherMode(CCAlgorithm cipher, CCMode mode, CCOperation direction);

#ifdef __cplusplus
}
#endif

#endif  /* _CC_COMMON_CRYPTOR_PRIV_ */
