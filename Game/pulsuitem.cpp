#include "pulsuitem.hh"

PulsuItem::PulsuItem(int x, int y) : ActorItem(x, y)
{
    width_ = 21;
    height_ = 30;
    pulsuType_ = 1;
}

PulsuItem::~PulsuItem()
{

}

QRectF PulsuItem::boundingRect() const
{
    return QRectF(0, 0, width_, height_);
}

void PulsuItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QImage img;
    if (pulsuType_ == 1)
    {
        img.load(":/data/data/pulsu1.png");
    }

    if (pulsuType_ == 2)
    {
        img.load(":/data/data/pulsu2.png");
    }

    painter->drawImage(QRectF(0,0, width_, height_),img);
}

void PulsuItem::getType(int type)
{
    pulsuType_ = type;
}

void PulsuItem::changeGender()
{
    if (pulsuType_ == 1)
    {
        pulsuType_ = 2;
    }
    else if (pulsuType_ == 2)
    {
        pulsuType_ = 1;
    }
}
