#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include "../CourseLib/graphics/simpleactoritem.hh"
#include "../CourseLib/interfaces/iactor.hh"
#include "passengeritem.hh"
#include "nysseitem.hh"
#include "pulsuitem.hh"
#include "beeritem.hh"
#include "dialog.hh"
#include "statistics.hh"
#include "pulsu.hh"
#include "home.hh"
#include "homeitem.hh"
#include <QMainWindow>
#include <QGraphicsScene>
#include <QTimer>
#include <QKeyEvent>
#include <iostream>
#include <QTextStream>
#include <memory>
#include <QVector>
#include <fstream>
#include <QFile>
#include <string>


//We really don't know :(
const float MAPWIDTH = 24.1;
const float MAPHEIGHT = 24.1;

//RNG for random events
const int NOT_GETTING_INTO_BUS_PROBABILITY = 9;
const int FINDING_NIKES_PROBABILITY = 69;
const int FINDING_BEER_PROBABILITY = 49;

const int TOP_LIST_LENGTH = 10;

const std::vector<std::vector<int>> BEERS = {{260,200}, {400,300}, {130, 150}, {550, 150},
                                             {150,400}, {300,400}, {700,200}, {900,400},
                                             {680,300}, {500,400}};

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    /**
     * @brief addNysse adds a Nysse to MainWindow.
     * @param locX: x coordinate of Nysse
     * @param locY: y coordinate of Nysse
     * @pre -
     * @post new NysseItem created, added to actors_ and drawn on map.
     */
    void addNysse(int locX, int locY);

    /**
     * @brief addPassenger adds a Passenger to MainWindow.
     * @param locX: x coordinate of Passenger
     * @param locY: y coordinate of Passenger
     * @pre -
     * @post new PassengerItem created, added to actors_ and drawn on map.
     */
    void addPassenger(int locX, int locY);

    /**
     * @brief updateMap updates map.
     * @pre map has been set.
     * @post update() is called for map.
     */
    void updateMap();

    /**
     * @brief returnActor
     * @param index of Actor wanted
     * @pre actors_ is at least index + 1 long.
     * @return QGraphicsItem* at index
     * @post Item in actors_ at index is returned.
     */
    QGraphicsItem* returnActor(int index);

    /**
     * @brief setSize sets the size of the MainWindow.
     * @param w width
     * @param h height
     * @pre -
     * @post width_ is set to w, height_ is set to h.
     */
    void setSize(int w, int h);

    /**
     * @brief setTick sets the timeout duration for timer_.
     * @param t timeout duration.
     * @pre -
     * @post tick_ is set to t.
     */
    void setTick(int t);

    /**
     * @brief setPicture sets the background for MainWindow.
     * @param img QImage
     * @pre map has been set.
     * @post setBackgroundBrush(img) is called for map.
     */
    void setPicture(QImage &img);


    /**
     * @brief addHome adds home to MainWindow.
     * @param pointer to Home
     * @pre map has been set.
     * @post home_ is set to Home*, a HomeItem is created
     *      and given to home_, home_ is drawn on map.
     */
    void addHome(Home*);

    /**
     * @brief addPulsu adds Pulsu1 and Pulsu2 to MainWindow.
     * @param pointers to Pulsu1 and Pulsu2
     * @pre map has been set.
     * @post pulsu_ is set to p1, pulsu2_ is set to p2, a PulsuItem
     *      is created and given to pulsu_, and drawn on map.
     */
    void addPulsu(Pulsu*, Pulsu*);

    /**
     * @brief givePulsuType sets  Pulsu type.
     * @param type: integer denoting type
     * @pre pulsu_ has been set.
     * @post setPulsuType(type) is called for pulsu_.
     */
    void givePulsuType(int type);

    /**
     * @brief addBothPulsus
     * @param pointers to Pulsu1 and Pulsu2
     * @pre map has been set.
     * @post pulsu_ is set to p1, pulsu2_ is set to p2, PulsuItems
     *      are created and drawn on map.
     */
    void addBothPulsus(Pulsu*, Pulsu*);

    /**
     * @brief getPulsuType returns Pulsu type.
     * @pre -
     * @return pulsuType_
     * @post pulsuType_ is returned.
     */
    int getPulsuType();


    /**
     * @brief takeStatistics sets Statistics for MainWindow.
     * @param s pointer to Statistics object
     * @pre -
     * @post statistics_ is set to s.
     */
    void takeStatistics(Statistics*);

    /**
     * @brief addBeer adds beer to MainWindow.
     * @pre map has been set and beeritems_ is empty.
     * @post beeritems_ is set to a vector of BeerItem*s
     *      and beers are drawn on map.
     */
    void addBeer();

    /**
     * @brief returnBeerItems returns BeerItems.
     * @pre addBeer() has been called.
     * @return beeritems_
     * @post vector containing BeetItem*s is returned.
     */
    std::vector<BeerItem*> returnBeerItems();

    /**
     * @brief removeItem removes item from map.
     * @param pointer to BeerItem
     * @pre addBeer() has been called and beer exists on map.
     * @post BeerItem is removed from map.
     */
    void removeItem(BeerItem* beer);

    /**
     * @brief getTwoPlayerMode return game mode.
     * @pre -
     * @return twoPlayerMode_
     * @post Game mode is returned.
     */
    bool getTwoPlayerMode();

    /**
     * @brief keyPressEvent handles characters moving and random events.
     * @param event keypress
     * @pre Game is running.
     * @post Character moves to wanted direction, stamina decreases.
     */
    void keyPressEvent(QKeyEvent* event);

    /**
     * @brief updateStats updates MainWindow Lcd numbers.
     * @pre pulsu_ and pulsu2_ have been set.
     * @post Lcd numbers show new stamina and new beer amount.
     */
    void updateStats();

    /**
     * @brief setGetOnButtonEnabled enables getOnButton for.
     * @pre GameLogic::checkGameStatus() has been called
     *      and a Nysse is close enough.
     * @post getOnButton enabled.
     */
    void setGetOnButtonEnabled();

    /**
     * @brief setGetOnButtonDisabled disables getOnButton.
     * @pre GameLogic::checkGameStatus() has been called
     *      and no Nysse is close enough.
     * @post getOnButton disabled.
     */
    void setGetOnButtonDisabled();

    /**
     * @brief setGetOnButton2Enabled enables getOnButton2 for.
     * @pre GameLogic::checkGameStatus() has been called
     *      and a Nysse is close enough. Two player game mode.
     * @post getOnButton2 enabled.
     */
    void setGetOnButton2Enabled();

    /**
     * @brief setGetOnButton2Disabled disables getOnButton2.
     * @pre GameLogic::checkGameStatus() has been called
     *      and no Nysse is close enough. Two player game mode.
     * @post getOnButton2 disabled.
     */
    void setGetOnButton2Disabled();

    /**
     * @brief finishGameBad ends game (loss).
     * @param pointer to Pulsu object.
     * @pre Game is running.
     * @post gameRunning_ set to false, killPulsu() called.
     */
    void finishGameBad(Pulsu*);

    /**
     * @brief finishGameGood ends game (win).
     * @pre Game is running.
     * @post gameRunning_ set to false, gameEndedWell_ set to true,
     *      getOffBus() called for pulsu_ and pulsu2_,
     *      final score displayed in MainWindow.
     */
    void finishGameGood();

    /**
     * @brief enableDrinkButton enables drinkBeerButton.
     * @pre Pulsu has beer and game is running.
     * @post drinkBeerButton enabled.
     */
    void enableDrinkButton();

    /**
     * @brief enableDrinkButton2 enables drinkBeerButton2.
     * @pre Pulsu2 has beer.
     * @post drinkBeerButton2 enabled.
     */
    void enableDrinkButton2();

    /**
     * @brief findShoes gives shoes to Pulsu.
     * @param pointer to Pulsu object
     * @pre Game is running.
     * @post findShoes() is called for Pulsu, ui text changes.
     */
    void findShoes(Pulsu*);

    /**
     * @brief findBeer gives beer to Pulsu.
     * @param pointer to Pulsu object.
     * @pre Game is running.
     * @post increaseBeer() is called for Pulsu, ui text changes.
     */
    void findBeer(Pulsu*);

    /**
     * @brief changeBeerFoundText changes ui text.
     * @pre Game is running.
     * @post Ui text is changed.
     */
    void changeBeerFoundText(Pulsu*);

    /**
     * @brief readFile reads scores and names from file to textBrowser.
     * @pre The files exist and are in the right format.
     * @post File is read and displayed in scoreTextBrowser.
     */
    void readFile();

    /**
     * @brief writeScore writes scores and names in files.
     * @pre The files exist.
     * @post playername_ and Pulsu beer amount are written in file.
     */
    void writeScore();

    /**
     * @brief split splits given string by delimeter.
     * @param str: string
     * @param delim: delimeter character
     * @pre -
     * @return vector containing separated QStrings
     * @post separated string is returned.
     */
    std::vector<QString> split(QString&, char);

    /**
     * @brief clearScoreBoard empties scoreTextBrowser.
     * @pre -
     * @post scoreTextBrowser empty.
     */
    void clearScoreBoard();

    /**
     * @brief getRunning returns game state.
     * @pre -
     * @return gameRunning_
     * @post game state (running or not) returned.
     */
    bool getRunning();

    /**
     * @brief gameEndedWell returns game ending.
     * @pre -
     * @return gameEndedWell_
     * @post gameEndedWell_ returned.
     */
    bool gameEndedWell();

private slots:
    /**
     * @brief setPulsuType sets Pulsu type.
     * @pre -
     * @post pulsuType_ set to type.
     */
    void setPulsuType(int);

    /**
     * @brief setTwoPlayerMode sets game mode.
     * @pre -
     * @post twoPlayerMode_ set to true or false.
     */
    void setTwoPlayerMode(bool);

    /**
     * @brief dontStartGame exits program.
     * @pre Dialog is rejected.
     * @post Exit program.
     */
    void dontStartGame();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *map;
    QTimer *timer;
    QVector <QGraphicsItem*> actors_;
    CourseSide::SimpleActorItem* last_;
    Pulsu* pulsu_;
    Pulsu* pulsu2_;
    Home* home_;
    Statistics* statistics_;
    std::vector<BeerItem*> beeritems_;

    std::default_random_engine randomEng;
    std::uniform_int_distribution<int> notGettingIntoBusDistr;
    std::uniform_int_distribution<int> findingNikesDistr;
    std::uniform_int_distribution<int> findingBeerDistr;

    bool damnFineNikesFound_;

    int pulsuType_;
    bool twoPlayerMode_;

    int width_ = 1095;
    int height_ = 592;
    int tick_ = 500;

    bool gameRunning_;
    bool gameEndedWell_;

    QString playername_ = "player";


signals:
    void gameStarted();

private slots:
    /**
     * @brief on_startButton_clicked starts game.
     * @pre -
     * @post gameRunning_ set to true, buttons set ready
     *       for playing.
     */
    void on_startButton_clicked();

    /**
     * @brief on_getOnButton_clicked makes Pulsu get on bus.
     * @pre Pulsu is not on bus and a Nysse is near.
     * @post getOnBus() is called for Pulsu, or not. getOnButton
     *       disabled, getOffButton enabled.
     */
    void on_getOnButton_clicked();

    /**
     * @brief on_getOffButton_clicked makes Pulsu get off bus.
     * @pre Pulsu is on bus.
     * @post getOffBus() is called for Pulsu, getOffButton is
     *       disabled.
     */
    void on_getOffButton_clicked();

    /**
     * @brief on_drinkBeerButton_clicked makes Pulsu drink beer.
     * @pre Game is running, pulsu_ has been set.
     * @post drinkBeer() is called for Pulsu, drinkBeerButton is
     *       disabled if beer amount is 0,
     *       finishGameBad() is called if Pulsu is on bus.
     */
    void on_drinkBeerButton_clicked();

    /**
     * @brief on_drinkBeerButton2_clicked makes Pulsu2 drink beer.
     * @pre Game is running, pulsu2_ has been set.
     * @post drinkBeer() is called for Pulsu2, drinkBeerButton2 is
     *       disabled if beer amount is 0,
     *       finishGameBad() is called if Pulsu2 is on bus.
     */
    void on_drinkBeerButton2_clicked();

    /**
     * @brief on_getOnButton2_clicked makes Pulsu2 get on bus.
     * @pre Pulsu2 is not on bus and a Nysse is near.
     * @post getOnBus() is called for Pulsu2, or not. getOnButton2
     *       disabled, getOffButton2 enabled.
     */
    void on_getOnButton2_clicked();

    /**
     * @brief on_getOffButton2_clicked makes Pulsu2 get off bus.
     * @pre Pulsu2 is on bus.
     * @post getOffBus() is called for Pulsu2, getOffButton2 is
     *       disabled.
     */
    void on_getOffButton2_clicked();

    /**
     * @brief on_nameLineEdit_editingFinished takes player name.
     * @pre -
     * @post playername_ is set.
     */
    void on_nameLineEdit_editingFinished();
};
#endif // MAINWINDOW_HH
