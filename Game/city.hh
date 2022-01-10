#ifndef CITY_HH
#define CITY_HH

#include "../CourseLib/interfaces/icity.hh"
#include "../CourseLib/interfaces/iactor.hh"
#include "../CourseLib/interfaces/istop.hh"
#include "../CourseLib/interfaces/ipassenger.hh"
#include "../CourseLib/interfaces/ivehicle.hh"
#include "../CourseLib/core/location.hh"
#include "../CourseLib/actors/stop.hh"
#include "../CourseLib/actors/nysse.hh"
#include "../CourseLib/actors/passenger.hh"
#include "../CourseLib/offlinereader.hh"
#include "../CourseLib/graphics/simpleactoritem.hh"
#include "pulsu.hh"
#include "mainwindow.hh"
#include <vector>
#include <typeinfo>

/**
 * @file
 * @brief Defines the City class that keeps track of buses and passengers.
 */


class City : public Interface::ICity
{
public:
    City();
    ~City();
    void setBackground(QImage& basicbackground, QImage& bigbackground) override;
    void setClock(QTime clock) override;
    void addStop(std::shared_ptr<Interface::IStop> stop) override;
    void startGame() override;
    void addActor(std::shared_ptr<Interface::IActor> newactor) override;
    void removeActor(std::shared_ptr<Interface::IActor> actor) override;
    void actorRemoved(std::shared_ptr<Interface::IActor> actor) override;
    bool findActor(std::shared_ptr<Interface::IActor> actor) const override;

    /**
     * @brief actorMoved moves a graphics item corresponding to actor.
     * @param actor: a pointer to IActor object that has moved
     * @pre actors_ is not empty and is the same size as actors_ in mainwindow_.
     * @post Coordinates of graphics item are changed.
     */
    void actorMoved(std::shared_ptr<Interface::IActor> actor) override;
    std::vector<std::shared_ptr<Interface::IActor>> getNearbyActors(Interface::Location loc) const override;

    /**
     * @brief isGameOver checks if game is running.
     * @pre mainwindow_ exists.
     * @return true if game is not running, false if game is running.
     * @post Score is written in a file and read, if game ended well.
     */
    bool isGameOver() const override;

    /**
     * @brief setMainWindow gives city object a main window.
     * @pre MainWindow object exists.
     * @post mainwindow_ is set to Mainwindow*.
     */
    void setMainWindow(MainWindow*);

    /**
     * @brief updateMap calls updateMap() for mainwindow_.
     */
    void updateMap();

    /**
     * @brief addPulsu sets pulsu_ to Pulsu*
     */
    void addPulsu(Pulsu*);

    /**
     * @return buses_ vector containing Nysse pointers
     */
    std::vector<CourseSide::Nysse*> getNysses();


private:
    bool gameStarted_;
    QTime clock_;

    MainWindow* mainwindow_;
    Pulsu* pulsu_;

    std::vector<std::shared_ptr<Interface::IActor>> actors_;
    std::vector<std::shared_ptr<Interface::IStop>> stops_;

    std::vector<CourseSide::Passenger*> passengers_;
    std::vector<CourseSide::Nysse*> buses_;
};

#endif // CITY_HH
