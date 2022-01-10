#include "gamelogic.hh"

GameLogic::GameLogic()
{
    updateInterval = 100;
    connect(&checkertimer_, SIGNAL(timeout()), this, SLOT(checkGameStatus()));
    checkertimer_.start(updateInterval);
    mountedBusSet_ = false;
    mountedBusSet2_ = false;
}

GameLogic::~GameLogic()
{

}
void GameLogic::checkGameStatus()
{
    // Check proximity to BUS
    bool nysseFoundClose = false;
    bool closestNysseInitialized = false;

    std::vector<CourseSide::Nysse*> nysses = city_->getNysses();
    for (CourseSide::Nysse* nysse : nysses)
    {
        if (! closestNysseInitialized)
        {
            closestNysse_ = nysse;      // make first Nysse the closest
            closestNysseInitialized = true;
        }

        int x = nysse->giveLocation().giveX() - pulsu_->getX();
        // - 15 because we want proximity to be checked from legs
        int y = nysse->giveLocation().giveY() - pulsu_->getY() - 15;

        int x2 = closestNysse_->giveLocation().giveX() - pulsu_->getX();
        int y2 = closestNysse_->giveLocation().giveY() - pulsu_->getY() - 15;

        float contenderhypotenuse = sqrt(x * x + y * y);
        float closesthypotenuse = sqrt(x2 * x2 + y2 * y2);

        if ((contenderhypotenuse < closesthypotenuse))      // compare two Nysse distances
        {
            closestNysse_ = nysse;                          // if new Nysse is closer, make it closest
        }


        // if Nysse is close enough, and Pulsu is not on a bus, and game is running
        if ((abs(x) < DETECTION_RANGE) && (abs(y) < DETECTION_RANGE) && (! pulsu_->getBusStatus()) && (mainwindow_->getRunning()))
        {
            mainwindow_->setGetOnButtonEnabled();
            nysseFoundClose = true;
        }
    }
    if ((! nysseFoundClose) && (! pulsu_->getBusStatus()))
    {
        mainwindow_->setGetOnButtonDisabled();
    }

    if (pulsu_->getBusStatus())     // pulsu is on a bus..
    {
        if (! mountedBusSet_)       // .. but the specific bus hasn't been set yet
        {
            nysseThatPulsuIsOn_ = closestNysse_;
            mountedBusSet_ = true;
        }

        // move according to the Nysse, move pulsu a bit upwards so their feet are on the bus (- 15)
        pulsu_->movePulsu(nysseThatPulsuIsOn_->giveLocation().giveX(), nysseThatPulsuIsOn_->giveLocation().giveY() - 15);
        pulsu_->drawPulsu();
    }
    else
    {
        mountedBusSet_ = false;
    }


    // Check proximity to HOME
    if ((abs(pulsu_->getX() - home_->getLocation().at(0)) < DETECTION_RANGE) && (abs(pulsu_->getY() - home_->getLocation().at(1)) < DETECTION_RANGE))
    {
        mainwindow_->finishGameGood();
    }

    // Check proximity to BEER
    int ind = 0;
    for (auto beer: beers_) {
        if ((abs(pulsu_->getX() - beer->giveX()) < DETECTION_RANGE) && (abs(pulsu_->getY() - beer->giveY()) < DETECTION_RANGE)) {
            int before = pulsu_->getBeer();
            pulsu_->increaseBeer();
            mainwindow_->updateStats();
            int after = pulsu_->getBeer();
            if ((before == 0) && (after == 1))
            {
                mainwindow_->enableDrinkButton();
            }
            mainwindow_->removeItem(beer);
            beers_.erase(beers_.begin()+ind);
            mainwindow_->changeBeerFoundText(pulsu_);
        }
        ind += 1;
    }

    // Second player status
    if (twoPlayerMode_)
    {
        bool nysseFoundClose2 = false;
        bool closestNysseInitialized2 = false;
        std::vector<CourseSide::Nysse*> nysses2 = city_->getNysses();
        for (CourseSide::Nysse* nysse2 : nysses2)
        {
            if (! closestNysseInitialized2)
            {
                closestNysse2_ = nysse2;
                closestNysseInitialized2 = true;
            }

            int x3 = nysse2->giveLocation().giveX() - pulsu2_->getX();
            int y3 = nysse2->giveLocation().giveY() - pulsu2_->getY() - 15;

            int x4 = closestNysse2_->giveLocation().giveX() - pulsu2_->getX();
            int y4 = closestNysse2_->giveLocation().giveY() - pulsu2_->getY() - 15;

            float contenderhypotenuse2 = sqrt(x3 * x3 + y3 * y3);
            float closesthypotenuse2 = sqrt(x4 * x4 + y4 * y4);

            if ((contenderhypotenuse2 < closesthypotenuse2))
            {
                closestNysse2_ = nysse2;
            }

            if ((abs(x3) < DETECTION_RANGE) && (abs(y3) < DETECTION_RANGE) && (! pulsu2_->getBusStatus()) && (mainwindow_->getRunning()))
            {
                mainwindow_->setGetOnButton2Enabled();
                nysseFoundClose2 = true;
            }
        }
        if ((! nysseFoundClose2) && (! pulsu2_->getBusStatus()))
        {
            mainwindow_->setGetOnButton2Disabled();
        }

        if (pulsu2_->getBusStatus())
        {
            if (! mountedBusSet2_)
            {
                nysseThatPulsu2IsOn_ = closestNysse2_;
                mountedBusSet2_ = true;
            }
            pulsu2_->movePulsu(nysseThatPulsu2IsOn_->giveLocation().giveX(), nysseThatPulsu2IsOn_->giveLocation().giveY() - 15);
            pulsu2_->drawPulsu();
        }
        else
        {
            mountedBusSet2_ = false;
        }

        if ((abs(pulsu_->getX() - pulsu2_->getX()) < DETECTION_RANGE) && (abs(pulsu_->getY() - pulsu2_->getY()) < DETECTION_RANGE))
        {
            mainwindow_->finishGameGood();
        }

        int ind2 = 0;
        for (auto beer: beers_) {
            if ((abs(pulsu2_->getX() - beer->giveX()) < DETECTION_RANGE) && (abs(pulsu2_->getY() - beer->giveY()) < DETECTION_RANGE)) {
                int before2 = pulsu2_->getBeer();
                pulsu2_->increaseBeer();
                int after2 = pulsu2_->getBeer();
                if ((before2 == 0) && (after2 == 1))
                {
                    mainwindow_->enableDrinkButton2();
                }
                mainwindow_->removeItem(beer);
                beers_.erase(beers_.begin()+ind2);
                mainwindow_->changeBeerFoundText(pulsu2_);
            }
            ind2 += 1;
        }
    }
}

void GameLogic::takeCityAgain(std::shared_ptr<City> city)
{
    city_ = city;
}

void GameLogic::takePulsus(Pulsu* pulsu, Pulsu* pulsu2)
{
    pulsu_ = pulsu;
    pulsu2_ = pulsu2;
}

void GameLogic::takeMainWindow(MainWindow* mainwindow)
{
    mainwindow_ = mainwindow;
}

void GameLogic::takeHome(Home* home)
{
    home_ = home;
}

void GameLogic::takeBeers(std::vector<BeerItem*> beers)
{
    beers_ = beers;
}

void GameLogic::setTwoPlayerMode(bool x)
{
    twoPlayerMode_ = x;
}

bool GameLogic::getTwoPlayerMode()
{
    return twoPlayerMode_;
}

