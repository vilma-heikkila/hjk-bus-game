#ifndef STATISTICS_HH
#define STATISTICS_HH

#include "../CourseLib/interfaces/istatistics.hh"

/**
 * @file
 * @brief Defines the Statistics class which keeps track of beers drunk
 *        and moves taken.
 */

class Statistics : public Interface::IStatistics
{
public:
    Statistics();
    ~Statistics();
    void morePassengers(int num) override;
    void nysseRemoved() override;
    void newNysse() override;
    void nysseLeft() override;

    /**
     * @brief beerDrunk keeps track of beers drunk.
     * @pre -
     * @post beersDrunk_ increased by 1.
     */
    void beerDrunk();

    /**
     * @brief pulsu1MoveTaken keeps track of Pulsu1 moves.
     * @pre -
     * @post pulsu1MovesTaken_ increased by 1.
     */
    void pulsu1MoveTaken();

    /**
     * @brief pulsu2MoveTaken keeps track of Pulsu2 moves.
     * @pre -
     * @post pulsu2MovesTaken_ increased by 1.
     */
    void pulsu2MoveTaken();

    /**
     * @brief howManyBeers returns amount of beers drunk.
     * @pre -
     * @return beersDrunk_
     * @post beersDrunk_ returned.
     */
    int howManyBeers();

    /**
     * @brief howManyPulsu1Moves returns number of Pulsu1 moves.
     * @pre -
     * @return pulsu1MovesTaken_
     * @post pulsu1MovesTaken_ returned.
     */
    int howManyPulsu1Moves();

    /**
     * @brief howManyPulsu2Moves returns number of Pulsu2 moves.
     * @pre -
     * @return pulsu2MovesTaken_
     * @post pulsu2MovesTaken_ returned.
     */
    int howManyPulsu2Moves();

private:
    int beersDrunk_;
    int pulsu1MovesTaken_;
    int pulsu2MovesTaken_;
};

#endif // STATISTICS_HH
