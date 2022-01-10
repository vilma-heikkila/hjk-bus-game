#ifndef NYSSEITEM_HH
#define NYSSEITEM_HH

#include "actoritem.hh"

/**
 * @file
 * @brief Defines a QGraphicsItem for the Nysse class.
 */

class NysseItem : public ActorItem
{

public:
    NysseItem(int x, int y);
    ~NysseItem();
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

private:
    int width_;
    int height_;
    int type_;
};

#endif // NYSSEITEM_HH
