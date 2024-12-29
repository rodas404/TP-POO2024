//
// Created by rodrigo on 08-12-2024.
//

#ifndef ITEM_H
#define ITEM_H
#include <set>
#include <string>

class Mapa;
class Caravana;

class Item {
public:
    virtual ~Item();

    Item(int lifeTime);
    Item(const Item &outro);
    Item &operator=(const Item &outro);

    int getId() const;
    int getTimeLeft() const;

    void setTimeLeft(int tl);
    Item &operator--();

    virtual void action(Caravana *car) = 0;
    std::pair<int, int> getCoordenadas(const Mapa *mapa) const;
    virtual std::string getDescricao() const = 0;

private:
    int id;
    int timeLeft;

    static std::set <int> usedIds;
    static int manageIds();
};

std::ostream &operator<<(std::ostream &output, const Item &item);


#endif //ITEM_H
