#include "pulsu.hh"


Pulsu::Pulsu()
{
    x_ = 250;
    y_ = 250;
    speed_ = 5;
    pulsuStamina_ = 50;
    pulsuType_ = 1;
    pulsuBeer_ = 3;
    isOnBus_ = false;
    beersDrunk_ = 0;
    shoesFound_ = false;
    alreadyDrunk_ = false;
}

int Pulsu::getX()
{
    return x_;
}

int Pulsu::getY()
{
    return y_;
}

void Pulsu::setX(int x)
{
    x_ = x;
}

void Pulsu::setY(int y)
{
    y_ = y;
}

void Pulsu::takeActor(PulsuItem* item)
{
    pulsuItem_ = item;
}

void Pulsu::moveUp()
{
    y_ -= 1 * speed_;
}

void Pulsu::moveDown()
{
    y_ += 1 * speed_;
}

void Pulsu::moveRight()
{
    x_ += 1 * speed_;
}

void Pulsu::moveLeft()
{
    x_ -= 1 * speed_;
}

void Pulsu::drawPulsu()
{
    pulsuItem_->setCoord(x_, y_);
    pulsuItem_->update();
}

void Pulsu::setPulsuType(int type)
{
    pulsuType_ = type;
    giveTypeToItem();
}

int Pulsu::getStamina()
{
    return pulsuStamina_;
}

int Pulsu::getPulsuType()
{
    return pulsuType_;
}

void Pulsu::giveTypeToItem()
{
    pulsuItem_->getType(pulsuType_);
}

int Pulsu::getBeer()
{
    return pulsuBeer_;
}

bool Pulsu::drinkBeer()
{
    if (pulsuBeer_ > 0)
    {
        pulsuBeer_ -= 1;
        pulsuStamina_ += 30;
    }
    beersDrunk_ += 1;
    if ((beersDrunk_ > 3) && (! alreadyDrunk_))
    {
        speed_ -= 2;
        alreadyDrunk_ = true;
        return true;
    }
    return false;
}

void Pulsu::increaseBeer()
{
    pulsuBeer_ += 1;
}

void Pulsu::killPulsu()
{
    x_ += 20;
    y_ += 10;
    drawPulsu();
    pulsuItem_->setRotation(90);
}

void Pulsu::getOnBus()
{
    isOnBus_ = true;
}

void Pulsu::getOffBus()
{
    isOnBus_ = false;
}

bool Pulsu::getBusStatus()
{
    return isOnBus_;
}

void Pulsu::movePulsu(int x, int y)
{
    x_ = x;
    y_ = y;
}

void Pulsu::decreaseStamina()
{
    if (pulsuStamina_ > 0)
    {
        pulsuStamina_ -= 1;
    }
}

void Pulsu::changeGender()
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

void Pulsu::setStamina(int x)
{
    pulsuStamina_ = x;
}

void Pulsu::setBeer(int x)
{
    pulsuBeer_ = x;
}

PulsuItem *Pulsu::returnPulsuItem()
{
    return pulsuItem_;
}

void Pulsu::findShoes()
{
    speed_ += 5;
    shoesFound_ = true;
}

bool Pulsu::getShoeStatus()
{
    return shoesFound_;
}
