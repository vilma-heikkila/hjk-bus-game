#include "statistics.hh"

Statistics::Statistics(): Interface::IStatistics()
{
    beersDrunk_ = 0;
    pulsu1MovesTaken_ = 0;
    pulsu2MovesTaken_ = 0;
}

Statistics::~Statistics()
{

}

void Statistics::morePassengers(int num)
{
    ;
}

void Statistics::nysseRemoved()
{
    ;
}

void Statistics::newNysse()
{
    ;
}

void Statistics::nysseLeft()
{
    ;
}

void Statistics::beerDrunk()
{
    beersDrunk_ += 1;
}

void Statistics::pulsu1MoveTaken()
{
    pulsu1MovesTaken_ += 1;
}

void Statistics::pulsu2MoveTaken()
{
    pulsu2MovesTaken_ += 1;
}

int Statistics::howManyBeers()
{
    return beersDrunk_;
}

int Statistics::howManyPulsu1Moves()
{
    return pulsu1MovesTaken_;
}

int Statistics::howManyPulsu2Moves()
{
    return pulsu2MovesTaken_;
}
