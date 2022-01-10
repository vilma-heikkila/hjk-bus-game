#ifndef PULSUITEM_HH
#define PULSUITEM_HH

#include "actoritem.hh"

/**
 * @file
 * @brief Defines QGraphicsItem for Pulsu class.
 */

class PulsuItem : public ActorItem
{

public:
    PulsuItem(int x, int y);
    ~PulsuItem();
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void getType(int type);
    void changeGender();

private:
    int width_;
    int height_;
    int pulsuType_; // 1 Jan-Erik, 2 Raija
};

#endif // PULSUITEM_HH
