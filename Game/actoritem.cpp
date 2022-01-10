#include "actoritem.hh"


ActorItem::ActorItem(int x, int y):x_(x), y_(y)
{
    setPos(mapToParent(x_, y_ ));
    width_ = 200;
    height_ = 200;
}

ActorItem::~ActorItem()
{

}

QRectF ActorItem::boundingRect() const
{
    return QRectF(0, 0, width_, height_);
}

void ActorItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QRectF bounds = boundingRect();
    QColor color(type_%256, type_%256, type_%256);
    QBrush brush(color);
    painter->setBrush(brush);
    painter->drawEllipse(bounds);
}

void ActorItem::setCoord(int x, int y)
{
    setX(x);
    setY(y);
}
