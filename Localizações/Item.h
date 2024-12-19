//
// Created by rodrigo on 08-12-2024.
//

#ifndef ITEM_H
#define ITEM_H


class Caravana;

class Item {
public:
    virtual ~Item() = default;

    Item();
    Item(const Item &outro);
    Item &operator=(const Item &outro);
    virtual Item *duplica() const = 0;

    char getId() const;
    int getTimeLeft() const;

    Item &operator--();
    virtual void action(Caravana *car) = 0;
    static int setLifeTime(int time);

private:
    char id;
    int timeLeft;

    static int lifetime;
};



#endif //ITEM_H
