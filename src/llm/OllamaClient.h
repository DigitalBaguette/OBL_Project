#ifndef OLLAMACLIENT_H
#define OLLAMACLIENT_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>

class OllamaClient : public QObject {
    Q_OBJECT
public:
    explicit OllamaClient(QObject *parent = nullptr);

    // Ta deklaracja musi tu być, aby uniknąć błędu "Out-of-line definition"
    void sendPrompt(const QString &prompt);

signals:
    void responseReceived(const QString &response);
    void errorOccurred(const QString &error);

private slots:
    void onReplyFinished(QNetworkReply *reply);

private:
    // Upewnij się, że nazwa to m_networkManager
    QNetworkAccessManager *m_networkManager;
};

#endif // OLLAMACLIENT_H