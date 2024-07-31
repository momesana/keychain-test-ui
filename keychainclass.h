#ifndef KEYCHAINCLASS_H
#define KEYCHAINCLASS_H

#include <QObject>

// #include <qtkeychain/keychain.h>

class KeyChainClass: public QObject
{
    Q_OBJECT
public:
    KeyChainClass(QObject* parent = nullptr);

    void readKey(const QString& key, const QString& serviceName = {});
    void writeKey(const QString& key, const QString& value, const QString& serviceName = {});
    void deleteKey(const QString& key, const QString& serviceName = {});

Q_SIGNALS:
    void keyStored(const QString& key);
    void keyRestored(const QString& key, const QString& value);
    void keyDeleted(const QString& key);
    void error(const QString& errorText);
};

#endif // KEYCHAINCLASS_H
