#ifndef OBJECTGENERATOR_HH
#define OBJECTGENERATOR_HH

#include "../CourseLib/core/logic.hh"
#include "city.hh"
#include "mainwindow.hh"
#include "gamelogic.hh"
#include "pulsu.hh"
#include "home.hh"

/**
 * @file
 * @brief Defines ObjetGenerator class that creates all actors needed in the game.
 */


class ObjectGenerator: public QObject
{
    Q_OBJECT
public:

    /**
     * @brief ObjectGenerator constructs ObjectGenerator object,
     *        and creates all actors needed in the game.
     * @pre -
     * @post pulsu_, pulsu2_, window_, city_, home_, logic_,
     *       and statistics_ are created and made ready for the game.
     */
    ObjectGenerator();
    ~ObjectGenerator();

    /**
     * @brief returnWindow returns MainWindow.
     * @pre window_ has been set.
     * @return window_
     * @post window_ returned.
     */
    MainWindow* returnWindow();

private slots:

    /**
     * @brief startGame starts game.
     * @pre Everything that was done in ObjectGenerator constructor
     *      needs to be done here.
     * @post finalizeGameStart() is called for logic_.
     */
    void startGame();

private:
    std::shared_ptr<City> city_;
    MainWindow* window_;
    GameLogic* logic_;
    Pulsu* pulsu_;
    Pulsu* pulsu2_;
    Home* home_;
    Statistics* statistics_;

};

#endif // OBJECTGENERATOR_HH
