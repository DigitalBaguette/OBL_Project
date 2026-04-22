#include "OllamaClient.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QUrl>
#include <QNetworkRequest>

/**
 * @brief Konstruktor klasy OllamaClient.
 * Inicjalizuje menedżera sieci, który zarządza cyklem życia żądań HTTP.
 */
OllamaClient::OllamaClient(QObject *parent)
    : QObject(parent)
{
    m_networkManager = new QNetworkAccessManager(this);
}

/**
 * @brief Formatuje dane wejściowe do formatu JSON i wysyła zapytanie do API Ollama.
 * Wykorzystuje model Llama 3.2, który jest zoptymalizowany pod kątem kart RTX 3060 Mobile.
 * * @param prompt Treść zapytania wygenerowana na podstawie profilu firmy.
 */
void OllamaClient::sendPrompt(const QString &prompt) {
    // Adres lokalnego serwera Ollama (standardowy port 11434)
    QUrl url("http://localhost:11434/api/generate");
    QNetworkRequest request(url);

    // Ustawienie nagłówka informującego o przesyłaniu danych w formacie JSON
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    // Przygotowanie struktury JSON zgodnie ze specyfikacją Ollama API
    QJsonObject json;
    json["model"] = "llama3.2"; // Wybrany model (lekki i wydajny dla 6GB VRAM)
    json["prompt"] = prompt;    // Tekst instrukcji dla modelu
    json["stream"] = false;     // Odbieramy kompletną odpowiedź w jednej paczce danych

    // Wykonanie asynchronicznego żądania POST
    QNetworkReply *reply = m_networkManager->post(request, QJsonDocument(json).toJson());

    // Obsługa zakończenia transmisji danych
    connect(reply, &QNetworkReply::finished, this, [this, reply]() {
        onReplyFinished(reply);
    });
}

/**
 * @brief Przetwarza odpowiedź zwrotną z serwera.
 * Wyodrębnia tekst odpowiedzi z formatu JSON lub przekazuje informacje o błędach.
 */
void OllamaClient::onReplyFinished(QNetworkReply *reply) {
    // Sprawdzenie, czy żądanie HTTP zakończyło się sukcesem
    if (reply->error() == QNetworkReply::NoError) {
        // Odczyt surowej odpowiedzi z bufora sieciowego
        QByteArray responseData = reply->readAll();

        // Parsowanie otrzymanych danych do dokumentu JSON
        QJsonDocument doc = QJsonDocument::fromJson(responseData);

        if (!doc.isNull() && doc.isObject()) {
            // Wyciągnięcie wygenerowanego tekstu z pola "response"
            QString responseText = doc.object().value("response").toString();
            emit responseReceived(responseText);
        } else {
            // Obsługa sytuacji, gdy serwer zwrócił nieprawidłowy format danych
            emit errorOccurred("Serwer zwrócił nieprawidłowy format JSON.");
        }
    } else {
        // Obsługa błędów sieciowych (np. serwer Ollama nie jest uruchomiony)
        QString errorMessage = "Błąd sieciowy: " + reply->errorString();
        emit errorOccurred(errorMessage);
    }

    // Zwolnienie pamięci zarezerwowanej dla obiektu odpowiedzi
    reply->deleteLater();
}