#include "nysseitem.hh"

NysseItem::NysseItem(int x, int y) : ActorItem(x, y)
{
    width_ = 25;
    height_ = 15;
    type_ = 0;
}

NysseItem::~NysseItem()
{

}

QRectF NysseItem::boundingRect() const
{
    return QRectF(0, 0, width_, height_);
}

void NysseItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
        QImage img;
        img.load(":/data/data/nysse.png");
        painter->drawImage(QRectF(0,0, width_, height_),img);
}
