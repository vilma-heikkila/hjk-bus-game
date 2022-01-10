#ifndef HOMEITEM_HH
#define HOMEITEM_HH

#include "actoritem.hh"

/**
 * @file
 * @brief Defines a QGraphicsItem for the Home class.
 */

class HomeItem : public ActorItem
{

public:
    HomeItem(int x, int y);
    ~HomeItem();
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

private:
    int width_;
    int height_;
};

#endif // HOMEITEM_HH
