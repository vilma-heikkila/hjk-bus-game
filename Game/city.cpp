#include "city.hh"

City::City()
{
    gameStarted_ = false;
}

City::~City()
{

}

void City::setBackground(QImage &basicbackground, QImage &bigbackground)
{
    mainwindow_->setPicture(bigbackground);
}

void City::setClock(QTime clock)
{
    clock_ = clock;
}

void City::addStop(std::shared_ptr<Interface::IStop> stop)
{
    stops_.push_back(stop);
}

void City::startGame()
{
    gameStarted_ = true;
}

void City::addActor(std::shared_ptr<Interface::IActor> newactor)
{
    actors_.push_back(newactor);
    if (dynamic_cast<CourseSide::Nysse*>(newactor.get()) != 0)
    {
        buses_.push_back(dynamic_cast<CourseSide::Nysse*>(newactor.get()));
        mainwindow_->addNysse(newactor->giveLocation().giveX(), newactor->giveLocation().giveY());
    }
    else if (dynamic_cast<CourseSide::Passenger*>(newactor.get()) != 0)
    {
        passengers_.push_back(dynamic_cast<CourseSide::Passenger*>(newactor.get()));
        mainwindow_->addPassenger(newactor->giveLocation().giveX(), newactor->giveLocation().giveY());
    }
}

void City::removeActor(std::shared_ptr<Interface::IActor> actor)
{
    ;
}

void City::actorRemoved(std::shared_ptr<Interface::IActor> actor)
{
    ;
}

bool City::findActor(std::shared_ptr<Interface::IActor> actor) const
{
    ;
}

void City::actorMoved(std::shared_ptr<Interface::IActor> actor)
{
    std::vector<std::shared_ptr<Interface::IActor>>::iterator it = std::find(actors_.begin(), actors_.end(), actor);
    int index = std::distance(actors_.begin(), it);
    QGraphicsItem* a = mainwindow_->returnActor(index);
    a->setX((actor->giveLocation().giveX()));
    a->setY(actor->giveLocation().giveY());
    a->update();
}

std::vector<std::shared_ptr<Interface::IActor>> City::getNearbyActors(Interface::Location loc) const
{
    ;
}

bool City::isGameOver() const
{
    if ((! mainwindow_->getRunning()) && (mainwindow_->gameEndedWell()))
    {
        mainwindow_->writeScore();
        mainwindow_->clearScoreBoard();
        mainwindow_->readFile();
    }

    return ! mainwindow_->getRunning();
}

void City::setMainWindow(MainWindow* w)
{
    mainwindow_ = w;
}

void City::updateMap()
{
    mainwindow_->updateMap();
}

void City::addPulsu(Pulsu* p)
{
    pulsu_ = p;
}

std::vector<CourseSide::Nysse*> City::getNysses()
{
    return buses_;
}


