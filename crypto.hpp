#ifndef CRYPTO_HPP
#define CRYPTO_HPP

/** --------------------------------------------------------------------------------------------------------------- **/

// CRYPTO++
#include <cryptopp/des.h>
#include <cryptopp/sha.h>
#include <cryptopp/base64.h>
#include <cryptopp/blowfish.h>

#define CRYPTOPP_DEFAULT_NO_DLL
#include <cryptopp/dll.h>
#include <cryptopp/default.h>
#ifdef CRYPTOPP_WIN32_AVAILABLE
#include <windows.h>
#endif

/** --------------------------------------------------------------------------------------------------------------- **/

// QT
#include <qstring.h>
#include <qbytearray.h>
#include <qcryptographichash.h>

#include <qdebug.h>

/** --------------------------------------------------------------------------------------------------------------- **/

#define FIRST_FAIL_HASH "JK54khOj54"
#define SECND_FAIL_HASH "54HjkljKH4"

/** --------------------------------------------------------------------------------------------------------------- **/

// NAMESPACES
using namespace std;
using namespace CryptoPP;

/** --------------------------------------------------------------------------------------------------------------- **/

class Crypto {

public:

    static const char * enhancePasswd(const char * passwd, const int & length) {
        string s("");
        if(strlen(passwd) > length) {
            for(int i(0); i < length; ++i)
                s += passwd[i];
        } else {
            s = passwd;
            for(int i(0); i < length - strlen(passwd); ++i)
                s += passwd[i%strlen(passwd)];
        }
        return s.c_str();
    }

    /** --------------------------------------------------------------------------------------------------------------- **/

    static string hex(const string & text, const bool & encryption = true) {
        string cipher("");
        try {
            if(encryption)
                StringSource(text, true, new HexEncoder(new StringSink(cipher)));
            else
                StringSource(text, true, new HexDecoder(new StringSink(cipher)));
        } catch(const CryptoPP::Exception & e) {
            cerr << e.what() << endl;
            exit(1);
        }
        return cipher;
    }

    /** --------------------------------------------------------------------------------------------------------------- **/

    static string base64(const string & text, const bool & encryption = true) {
        string cipher("");
        try {
            if(encryption)
                StringSource((const byte *)text.c_str(), text.length(), true, new Base64Encoder(new StringSink(cipher), false));
            else
                StringSource(text, true, new Base64Decoder(new StringSink(cipher)));
        } catch(const CryptoPP::Exception & e) {
            cerr << e.what() << endl;
            exit(1);
        }
        return cipher;
    }

    /** --------------------------------------------------------------------------------------------------------------- **/

    static QString hashMe(const QString & phrase) {
        QByteArray ba = QCryptographicHash::hash(QByteArray(
                                             QCryptographicHash::hash(QString(FIRST_FAIL_HASH).toUtf8(), QCryptographicHash::Md4) +
                                             QCryptographicHash::hash(phrase.toUtf8(), QCryptographicHash::Sha1) +
                                             QCryptographicHash::hash(QString(SECND_FAIL_HASH).toUtf8(), QCryptographicHash::Md5)), QCryptographicHash::Sha1);
        return ba.toHex();
    }

    /** --------------------------------------------------------------------------------------------------------------- **/

    static string blowfish(const string & text, const char * passwd = "", const char * stored_iv = "", const bool & encryption = true) {
        const char * enhPwd(enhancePasswd(passwd, int(Blowfish::DEFAULT_KEYLENGTH)));
        SecByteBlock key(strlen(enhPwd));
        byte iv[Blowfish::BLOCKSIZE];

        for(int i(0); i < strlen(enhPwd); ++i)
            key[i] = enhPwd[i];

        if(stored_iv == "") {
            AutoSeededRandomPool prng;
            prng.GenerateBlock(iv, sizeof(iv));
        } else
            for(int i(0); i < Blowfish::BLOCKSIZE; ++i)
                iv[i] = (byte)stored_iv[i];

        string cipher("");
        try {
            if(encryption) {
                CBC_Mode<Blowfish>::Encryption e;
                e.SetKeyWithIV(key, key.size(), iv);
                StringSource(text, true, new StreamTransformationFilter(e, new StringSink(cipher)));
                cipher.append("\n").append((char *)iv);
            } else {
                CBC_Mode<Blowfish>::Decryption d;
                d.SetKeyWithIV(key, key.size(), iv);
                StringSource(text, true, new StreamTransformationFilter(d, new StringSink(cipher)));
            }
        } catch(const CryptoPP::Exception & e) {
            cerr << e.what() << endl;
            exit(1);
        }
        return cipher;
    }

    /** --------------------------------------------------------------------------------------------------------------- **/

    static string DES3(const string & text, const char * passwd = "", const char * stored_iv = "", const bool & encryption = true) {
        const char * enhPwd(enhancePasswd(passwd, int(DES_EDE3::DEFAULT_KEYLENGTH)));
        SecByteBlock key(strlen(enhPwd));
        byte iv[DES_EDE3::BLOCKSIZE];

        for(int i(0); i < strlen(enhPwd); ++i)
            key[i] = enhPwd[i];

        if(stored_iv == "") {
            AutoSeededRandomPool prng;
            prng.GenerateBlock(iv, sizeof(iv));
        } else
            for(int i(0); i < DES_EDE3::BLOCKSIZE; ++i)
                iv[i] = (byte)stored_iv[i];

        string cipher("");
        try {
            if(encryption) {
                CBC_Mode< DES_EDE3 >::Encryption e;
                e.SetKeyWithIV(key, key.size(), iv);
                StringSource(text, true, new StreamTransformationFilter(e, new StringSink(cipher)));
                cipher.append("\n").append((char *)iv);
            } else {
                CBC_Mode< DES_EDE3 >::Decryption d;
                d.SetKeyWithIV(key, key.size(), iv);
                StringSource(text, true, new StreamTransformationFilter(d, new StringSink(cipher)));
            }
        } catch(const CryptoPP::Exception & e) {
            cerr << e.what() << endl;
            exit(1);
        }
        return cipher;
    }
};

#endif // CRYPTO_HPP
