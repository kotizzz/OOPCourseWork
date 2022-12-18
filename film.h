#ifndef FILM_H
#define FILM_H

#include <QString>
#include <QtAlgorithms>

class Film {
 private:
    QString film = "";
    QString prod = "";
    QString outYear = "";
    QString genre = "";
    QString profit = "";

 public:

    Film();

    explicit Film(QString nominal, QString prod, QString outYear, QString genre, QString profit);

    Film(const Film &arg);

    Film &operator=(const Film &arg);

    Film(Film &&arg) noexcept;

    Film &operator=(Film &&arg) noexcept;

    virtual ~Film();

    QString &operator[](int i);

    void clear();

    explicit operator bool();

    void setFilm(QString arg);

    const QString &getFilm();

    void setprod(QString arg);

    const QString &getprod();

    void setgenre(QString arg);

    const QString &getgenre();

    void setProfit(QString arg);

    const QString &getProfit();

    void setoutYear(QString arg);

    const QString &getoutYear();

    friend void swap(Film &first, Film &second) noexcept;
};


#endif // FILM_H
