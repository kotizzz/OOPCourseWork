#include "film.h"
#include <QtAlgorithms>

Film::Film() {}

Film::Film(QString film, QString prod, QString outYear, QString genre, QString profit)
    : film(film), prod(prod), outYear(outYear), genre(genre), profit(profit) {

}

Film::Film(const Film &arg) : Film(arg.film, arg.prod, arg.outYear, arg.genre, arg.profit) {

}

Film & Film::operator=(const Film &arg) {
    Film temp(arg);
    swap(*this, temp);
    return *this;
}

Film::Film(Film &&arg) noexcept {
    film = std::move(arg.film);
    prod = std::move(arg.prod);
    genre = std::move(arg.genre);
    profit = std::move(arg.profit);
    outYear = std::move(arg.outYear);
    arg.film = arg.prod = arg.outYear = arg.genre = arg.profit = "";
}

Film & Film::operator=(Film &&arg) noexcept {
    if (this != &arg) {
        swap(*this, arg);
        arg.film = arg.prod = arg.outYear = arg.genre = arg.profit = "";
    }
    return *this;
}

Film::~Film() {}


void Film::clear() {
    film = prod = outYear = genre = profit = "";

}

Film::operator bool() {
    return !film.isEmpty() || !prod.isEmpty() || !outYear.isEmpty() || !genre.isEmpty() || !profit.isEmpty();
}

void Film::setFilm(QString arg) {
    film = arg;
}

const QString & Film::getFilm() {
    return film;
}

void Film::setgenre(QString arg) {
    genre = arg;
}

const QString & Film::getgenre() {
    return genre;
}

void Film::setProfit(QString arg) {
    profit = arg;
}

const QString & Film::getProfit() {
    return profit;
}

void Film::setprod(QString arg) {
    prod = arg;
}

const QString & Film::getprod() {
    return prod;
}

void Film::setoutYear(QString arg) {
    outYear = arg;
}

const QString & Film::getoutYear() {
    return outYear;
}

void swap(Film &first, Film &second) noexcept {
    std::swap(first.film, second.film);
    std::swap(first.prod, second.prod);
    std::swap(first.profit, second.profit);
    std::swap(first.genre, second.genre);
    std::swap(first.outYear, second.outYear);
}
