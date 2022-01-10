#ifndef PASSENGERITEM_HH
#define PASSENGERITEM_HH

#include "actoritem.hh"

/**
 * @file
 * @brief Defines a QGraphicsItem for Passenger class.
 */

class PassengerItem : public ActorItem
{

public:
    PassengerItem(int x, int y);
    ~PassengerItem();
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

private:
    int width_;
    int height_;
    int type_;
};

#endif // PASSENGERITEM_HH
