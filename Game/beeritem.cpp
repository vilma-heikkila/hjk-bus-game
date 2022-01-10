#include "beeritem.hh"

BeerItem::BeerItem(int x, int y) : ActorItem(x, y)
{
    width_ = 10;
    height_ = 15;
    type_ = 0;
    x_ = x;
    y_ = y;
}

BeerItem::~BeerItem()
{

}

QRectF BeerItem::boundingRect() const
{
    return QRectF(0, 0, width_, height_);
}

void BeerItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
        QImage img;
        img.load(":/data/data/kalja.png");
        painter->drawImage(QRectF(0,0, width_, height_),img);
}

int BeerItem::giveX()
{
    return x_;
}

int BeerItem::giveY()
{
    return y_;
}
