//
// Created by rodrigo on 08-12-2024.
//

#ifndef ITEM_H
#define ITEM_H


class Caravana;

class Item {
public:
    virtual ~Item() = default;

    Item(int lifeTime = 20);
    Item(const Item &outro);
    Item &operator=(const Item &outro);

    char getId() const;
    int getTimeLeft() const;

    Item &operator--();
    virtual void action(Caravana *car) = 0;

private:
    char id;
    int timeLeft;

};



#endif //ITEM_H
