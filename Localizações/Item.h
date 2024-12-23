//
// Created by rodrigo on 08-12-2024.
//

#ifndef ITEM_H
#define ITEM_H
#include <set>

class Mapa;
class Caravana;

class Item {
public:
    virtual ~Item();

    Item(int lifeTime = 20);
    Item(const Item &outro);
    Item &operator=(const Item &outro);

    int getId() const;
    int getTimeLeft() const;

    Item &operator--();
    virtual void action(Caravana *car) = 0;
    std::pair<int, int> getCoordenadas(const Mapa *mapa) const;

private:
    int id;
    int timeLeft;

    static std::set <int> usedIds;
    static int manageIds();
};



#endif //ITEM_H
