/* To add a test, just add it here */

// Random MUST BE FIRST
ONE_TEST(CommonRandom)

// No particular sequence
ONE_TEST(CommonCPP)
ONE_TEST(CommonCryptoSymECB)
ONE_TEST(CommonCryptoSymCBC)
ONE_TEST(CommonCryptoSymOFB)
ONE_TEST(CommonCryptoSymGCM)
ONE_TEST(CommonCryptoSymCCM)
ONE_TEST(CommonCryptoSymCTR)
ONE_TEST(CommonCryptoSymXTS)
ONE_TEST(CommonCryptoSymRC2)
ONE_TEST(CommonCryptoSymRegression)
ONE_TEST(CommonCryptoSymOffset)
ONE_TEST(CommonCryptoSymZeroLength)
ONE_TEST(CommonCryptoOutputLength)
ONE_TEST(CommonCryptoNoPad)
ONE_TEST(CommonCryptoSymCFB)
ONE_TEST(CommonCryptoCTSPadding)
ONE_TEST(CommonSymmetricWrap)
ONE_TEST(CommonDH)
ONE_TEST(CommonDigest)
ONE_TEST(CommonHMac)
ONE_TEST(CommonCryptoReset)
#if !defined(_WIN32)
ONE_TEST(CommonBigNum) /* BignNm is not ported to Windows */
#endif
ONE_TEST(CommonBigDigest)
ONE_TEST(CommonCryptoWithData)
ONE_TEST(CommonCryptoBlowfish)
ONE_TEST(CommonCRCTest)
ONE_TEST(CommonBaseEncoding)
ONE_TEST(CommonHKDF)
ONE_TEST(CommonNISTKDF)
ONE_TEST(CommonKeyDerivation)
ONE_TEST(CommonEC)
ONE_TEST(CommonRSA)
ONE_TEST(CommonHMacClone)
ONE_TEST(CommonCMac)

