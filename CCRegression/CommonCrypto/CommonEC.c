
#include "capabilities.h"
#include "testmore.h"
#include "testbyteBuffer.h"

#if (CCEC == 0)
entryPoint(CommonEC,"Elliptic Curve Cryptography")
#else

#include <CommonCrypto/CommonECCryptor.h>

static int kTestTestCount = 12;

int CommonEC(int __unused argc, char *const * __unused argv) {
	CCCryptorStatus retval;
    size_t keysize;
    CCECCryptorRef publicKey, privateKey;
    CCECCryptorRef publicKey2;
    CCECCryptorRef badPublicKey, badPrivateKey;
    CCECCryptorRef privateKey224;
    // byteBuffer keydata, dekeydata;
    byteBuffer hash;
    byteBuffer badPublicKeyBytes, badPrivateKeyBytes;
    byteBuffer privateKey224Bytes;
    char encryptedKey[8192];
    size_t encryptedKeyLen = 8192;
    // char decryptedKey[8192];
    // size_t decryptedKeyLen = 8192;
    char signature[8192];
    size_t signatureLen = 8192;
    char importexport[8192];
    size_t importexportLen = 8192;
    uint32_t valid;
    int accum = 0;
    int debug = 0;
    
	plan_tests(kTestTestCount);
    
    keysize = 256;
    
    retval = CCECCryptorGeneratePair(keysize, &publicKey, &privateKey);
    if(debug) printf("Keys Generated\n");
    ok(retval == 0, "Generate an EC Key Pair");
	accum |= retval;

#ifdef ECDH
    keydata = hexStringToBytes("000102030405060708090a0b0c0d0e0f");
    
    retval = CCECCryptorWrapKey(publicKey, keydata->bytes, keydata->len, encryptedKey, &encryptedKeyLen, kCCDigestSHA1);
    
    ok(retval == 0, "Wrap Key Data with EC Encryption - ccPKCS1Padding");
    accum |= retval;
    
    retval = CCECCryptorUnwrapKey(privateKey, encryptedKey, encryptedKeyLen,
                        decryptedKey, &decryptedKeyLen);
    
    ok(retval == 0, "Unwrap Key Data with EC Encryption - ccPKCS1Padding");
    accum |= retval;

	dekeydata = bytesToBytes(decryptedKey, decryptedKeyLen);
    
	ok(bytesAreEqual(dekeydata, keydata), "Round Trip CCECCryptorWrapKey/CCECCryptorUnwrapKey");
    accum |= retval;
#endif

    
    hash = hexStringToBytes("000102030405060708090a0b0c0d0e0f");

    retval = CCECCryptorSignHash(privateKey, 
                     hash->bytes, hash->len,
                     signature, &signatureLen);
                     
    ok(retval == 0, "EC Signing");
    valid = 0;
    accum |= retval;
    if(debug) printf("Signing Complete\n");
    
    retval = CCECCryptorVerifyHash(publicKey,
                       hash->bytes, hash->len, 
                       signature, signatureLen, &valid);
    ok(retval == 0, "EC Verifying");
    accum |= retval;
	ok(valid, "EC Validity");
    accum |= retval;
    if(debug) printf("Verify Complete\n");
   
    // Mess with the sig - see what happens
    signature[signatureLen-3] += 3;
    retval = CCECCryptorVerifyHash(publicKey,
                                   hash->bytes, hash->len, 
                                   signature, signatureLen, &valid);
    ok(retval == 0, "EC Verifying");
    accum |= retval;
	ok(!valid, "EC Invalid Signature");
    accum |= retval;
    
    if(debug) printf("Verify2 Complete\n");
    
    encryptedKeyLen = 8192;
	retval = CCECCryptorExportPublicKey(publicKey, importexport, &importexportLen);
    
    ok(retval == 0, "EC Export Public Key");
    accum |= retval;

    retval = CCECCryptorImportPublicKey(importexport, importexportLen, &publicKey2);
    
    ok(retval == 0, "EC Import Public Key");
    accum |= retval;
                          
	encryptedKeyLen = 8192;
    retval = CCECCryptorComputeSharedSecret(privateKey, publicKey, encryptedKey, &encryptedKeyLen);

    ok(retval == 0, "EC Shared Secret");
    accum |= retval;
    
    // These are keys from WebCrypto that were invalid.
    badPublicKeyBytes = hexStringToBytes("044c4d4c1c624fcf8db7221efd097f19d8b6a33e870f1f8d2988491859e2cf9cb7cbef11efc0f4c8bf58b602f814d5432335341c636459a090e4fcf71185f44d00");
    retval = CCECCryptorImportPublicKey(badPublicKeyBytes->bytes, badPublicKeyBytes->len, &badPublicKey);
    ok(retval == kCCInvalidKey, "Reject Invalid Public Key");
    
    // Generated bad key
    badPrivateKeyBytes = hexStringToBytes("044c4d4c1c624fcf8db7221efd097f19d8b6a33e870f1f8d2988491859e2cf9cb7cbef11efc0f4c8bf58b602f814d5432335341c636459a090e4fcf71185f44d001bc7662261a5e0ed73902c99b872c813bfc1d7081ab672a592fe20079a36d23e");
    retval = CCECCryptorImportKey(kCCImportKeyBinary, badPrivateKeyBytes->bytes, badPrivateKeyBytes->len, ccECKeyPrivate, &badPrivateKey);
    ok(retval == kCCInvalidKey, "Reject Invalid Private Key");

    // Import a P-224 private key.
    privateKey224Bytes = hexStringToBytes("040b75435120c361428ba8b6fa219d65b7dcd9b51302d40009ca7c6bba1524090ec83448b41a213e93d0ee7b94ba15fa49aff3f68863b1ff4b000102030405060708090a0b0c0d0e0f101112131415161718191a1b");
    retval = CCECCryptorImportKey(kCCImportKeyBinary, privateKey224Bytes->bytes, privateKey224Bytes->len, ccECKeyPrivate, &privateKey224);
    is(retval, 0, "Import P-224 Private Key");

    CCECCryptorRelease(publicKey);
    CCECCryptorRelease(publicKey2);
    CCECCryptorRelease(privateKey);
    CCECCryptorRelease(privateKey224);
    free(hash);
    free(badPublicKeyBytes);
    free(badPrivateKeyBytes);
    free(privateKey224Bytes);
    return accum;
}
#endif /* CCEC */
