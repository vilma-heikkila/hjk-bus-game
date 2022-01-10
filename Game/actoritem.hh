#ifndef ACTORITEM_HH
#define ACTORITEM_HH

#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QPainter>

/**
 * @file
 * @brief Defines a base class for QGraphicsItems used in the game,
 *        and their operations.
 */

class ActorItem : public QGraphicsItem
{
public:

    /**
     * @brief ActorItem constructs an ActorItem (a QGraphicsItem).
     * @param x coordinate on map
     * @param y coordinate on map
     */
    ActorItem(int x, int y);

    /**
     * @brief ~ActorItem destructor.
     */
    virtual ~ActorItem();
    virtual QRectF boundingRect() const;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    /**
     * @brief setCoord sets the coordinates of the graphcisitem to (x,y).
     * @param x
     * @param y
     */

    void setCoord(int x, int y);

private:
    int x_;
    int y_;
    int type_;
    int width_;
    int height_;
};

#endif // ACTORITEM_HH
