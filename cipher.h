#ifndef CIPHER_H
#define CIPHER_H

#include <QObject>
#include <QDebug>
#include <QFile>
#include <openssl/rsa.h>
#include <openssl/engine.h>
#include <openssl/pem.h>
#include <openssl/conf.h>
#include <openssl/evp.h>
#include <openssl/err.h>
#include <openssl/aes.h>
#include <openssl/rand.h>

#define PADDING RSA_PKCS1_PADDING

class Cipher : public QObject
{
    Q_OBJECT
public:
    explicit Cipher(QObject *parent = nullptr);
    ~Cipher();

    RSA *getPublicKey(QByteArray &data);
    RSA *getPublicKey(QString filename);


    QByteArray encryptRSA(RSA *key, QByteArray &data);

    void freeRSAKey(RSA *key);



signals:

private:
    void initalize();
    void finalize();

    QByteArray readFile(QString filename);


};

#endif // CIPHER_H
