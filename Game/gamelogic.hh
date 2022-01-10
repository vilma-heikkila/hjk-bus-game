#ifndef GAMELOGIC_HH
#define GAMELOGIC_HH

#include "../CourseLib/core/logic.hh"
#include "beeritem.hh"
#include "city.hh"
#include <cmath>
#include <math.h>
#include <random>

/**
 * @file
 * @brief Defines GameLogic class that keeps track of game status.
 */

const int DETECTION_RANGE = 15;

class GameLogic: public CourseSide::Logic
{
    Q_OBJECT
public:
    GameLogic();
    ~GameLogic();

    /**
     * @brief takeCityAgain gives GameLogic object a city.
     * @param Pointer to City object.
     * @pre City exists.
     * @post city_ is set to City.
     */
    void takeCityAgain(std::shared_ptr<City>);

    /**
     * @brief takePulsus
     * @param Pointers to two Pulsu objects.
     * @pre Two Pulsu objects exist.
     * @post pulsu_ is set to Pulsu* (1), pulsu2_ is set to Pulsu* (2).
     */
    void takePulsus(Pulsu*, Pulsu*);

    /**
     * @brief takeMainWindow gives GameLogic object a main window.
     * @param Pointer to MainWindow object.
     * @pre MainWindow exists.
     * @post mainwindow_ is set to MainWindow*.
     */
    void takeMainWindow(MainWindow*);

    /**
     * @brief takeHome gives GameLogic object a home.
     * @param Pointer to Home object.
     * @pre Home exists.
     * @post home_ is set to Home*.
     */
    void takeHome(Home*);

    /**
     * @brief takeBeers gives GameLogic object BeerItems.
     * @param A vector containing pointers to BeerItems.
     * @pre The vector exists.
     * @post beers_ is set to vector.
     */
    void takeBeers(std::vector<BeerItem *>);

    /**
     * @brief setTwoPlayerMode sets game mode.
     * @pre -
     * @post twoPlayerMode_ is set to true or false.
     */
    void setTwoPlayerMode(bool);

    /**
     * @brief getTwoPlayerMode returns game mode.
     * @return twoPlayerMode_
     */
    bool getTwoPlayerMode();

public slots:

    /**
     * @brief checkGameStatus checks the proximity of Nysses, home and beers.
     * @pre City has Nysses, GameLogic has Pulsu objects, Home and BeerItems.
     * @post If 1) Nysse is near, Pulsu can get on it,
     *       or 2) Home is near, the game is won,
     *       or 3) BeerItem is near, Pulsu picks it up.
     */
    void checkGameStatus();

private:
    std::shared_ptr<City> city_;
    Pulsu* pulsu_;
    Pulsu* pulsu2_;
    MainWindow* mainwindow_;
    Home* home_;
    std::vector<BeerItem*> beers_;

    QTimer checkertimer_;
    int updateInterval;

    CourseSide::Nysse* closestNysse_;
    CourseSide::Nysse* closestNysse2_;
    CourseSide::Nysse* nysseThatPulsuIsOn_;
    CourseSide::Nysse* nysseThatPulsu2IsOn_;
    bool mountedBusSet_;
    bool mountedBusSet2_;

    bool twoPlayerMode_;


};

#endif // GAMELOGIC_HH
