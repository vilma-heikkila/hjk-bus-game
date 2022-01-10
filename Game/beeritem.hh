#ifndef BEERITEM_HH
#define BEERITEM_HH

#include "actoritem.hh"

/**
 * @file
 * @brief Defines a QGraphicsItem for the Beer class.
 */


class BeerItem: public ActorItem
{
public:
    BeerItem(int x, int y);
    ~BeerItem();
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    /**
     * @return x_
     */
    int giveX();

    /**
     * @return y_
     */
    int giveY();

private:
    int width_;
    int height_;
    int type_;

    int x_;
    int y_;
};

#endif // BEERITEM_HH
