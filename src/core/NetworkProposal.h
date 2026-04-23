/**
 * @file NetworkProposal.h
 * @brief Definicja klasy NetworkProposal reprezentującej wynikowy projekt sieci.
 * @author Twój Numer Indeksu
 * @date 2026
 */

#ifndef NETWORKPROPOSAL_H
#define NETWORKPROPOSAL_H

#include <QString>
#include <QDateTime>
#include <QJsonObject>
#include "CompanyProfile.h"

/**
 * @class NetworkProposal
 * @brief Model danych przechowujący kompletną propozycję konfiguracji sieciowej.
 * * Klasa integruje dane wejściowe klienta (CompanyProfile) z wynikiem generowania AI.
 * Obsługuje mechanizmy serializacji i deserializacji JSON, co umożliwia elastyczne
 * przechowywanie danych w bazach NoSQL lub polach tekstowych SQL.
 */
class NetworkProposal {
public:
    /**
     * @brief Domyślny konstruktor obiektu propozycji.
     */
    NetworkProposal() = default;

    /**
     * @brief Surowa treść odpowiedzi wygenerowanej przez model językowy.
     * Zawiera szczegółowe specyfikacje urządzeń, adresację IP i uzasadnienie projektowe.
     */
    QString rawContent;

    /**
     * @brief Profil firmy powiązany z daną propozycją.
     * Przechowuje parametry wejściowe takie jak liczba pracowników i budżet.
     */
    CompanyProfile profile;

    /**
     * @brief Znacznik czasu określający moment utworzenia propozycji.
     */
    QDateTime timestamp;

    /**
     * @brief Unikalny identyfikator propozycji (zazwyczaj UUID).
     */
    QString id;

    /**
     * @brief Konwertuje stan obiektu na format JSON.
     * Metoda umożliwia trwałe zapisanie projektu w bazie danych przy zachowaniu
     * pełnej struktury obiektowej.
     * @return QJsonObject Reprezentacja danych propozycji w formacie klucz-wartość.
     */
    QJsonObject toJson() const;

    /**
     * @brief Fabryka tworząca obiekt propozycji na podstawie danych JSON.
     * Wykorzystywana przy odczycie historycznych projektów z bazy danych.
     * @param json Obiekt JSON pobrany z warstwy storage.
     * @return NetworkProposal Kompletnie zainicjalizowany obiekt propozycji.
     */
    static NetworkProposal fromJson(const QJsonObject &json);
};

#endif // NETWORKPROPOSAL_H