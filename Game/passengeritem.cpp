#include "passengeritem.hh"

PassengerItem::PassengerItem(int x, int y) : ActorItem(x, y)
{
    width_ = 8;
    height_ = 8;
    type_ = 120;
}

PassengerItem::~PassengerItem()
{

}

QRectF PassengerItem::boundingRect() const
{
    return QRectF(0, 0, width_, height_);
}

void PassengerItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
      QRectF bounds = boundingRect();
      QColor color(type_%256, type_%256, type_%256);
      QBrush brush(color);
      painter->setBrush(brush);
      painter->drawEllipse(bounds);
}
