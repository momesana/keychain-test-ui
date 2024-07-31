#include <QDebug>

#include "keychainclass.h"
#include "qtkeychain/keychain.h"

KeyChainClass::KeyChainClass(QObject* parent) :
    QObject(parent)
{
}

void KeyChainClass::readKey(const QString &key, const QString &serviceName)
{

    const auto job = new QKeychain::ReadPasswordJob(serviceName, this);
    job->setKey(key);

    QObject::connect(job, &QKeychain::ReadPasswordJob::finished, this, [=](){
        if (job->error()) {
            emit error(tr("Read key failed: %1").arg(qPrintable(job->errorString())));
            return;
        }
        emit keyRestored(key, job->textData());
    });

    job->start();
}

void KeyChainClass::writeKey(const QString &key, const QString &value, const QString &serviceName)
{
    const auto job = new QKeychain::WritePasswordJob(serviceName, this);
    job->setKey(key);

    QObject::connect(job, &QKeychain::WritePasswordJob::finished, this, [=](){
        if (job->error()) {
            emit error(tr("Write key failed: %1").arg(qPrintable(job->errorString())));
            return;
        }

        emit keyStored(key);
    });

    job->setTextData(value);
    job->start();
}

void KeyChainClass::deleteKey(const QString &key, const QString &serviceName)
{
    const auto job = new QKeychain::DeletePasswordJob(serviceName, this);
    job->setKey(key);

    QObject::connect(job, &QKeychain::DeletePasswordJob::finished, this, [=](){
        if (job->error()) {
            emit error(tr("Delete key failed: %1").arg(qPrintable(job->errorString())));
            return;
        }
        emit keyDeleted(key);
    });

    job->start();
}
