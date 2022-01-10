#include "homeitem.hh"

HomeItem::HomeItem(int x, int y) : ActorItem(x, y)
{
    width_ = 21;
    height_ = 30;
}

HomeItem::~HomeItem()
{

}

QRectF HomeItem::boundingRect() const
{
    return QRectF(0, 0, width_, height_);
}

void HomeItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QImage img;
    img.load(":/data/data/koti.png");
    painter->drawImage(QRectF(0,0, width_, height_),img);
}
