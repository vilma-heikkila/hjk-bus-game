#include "objectgenerator.hh"

ObjectGenerator::ObjectGenerator()
{
    Pulsu* p1 = new Pulsu;
    pulsu_ = p1;
    Pulsu* p2 = new Pulsu;
    pulsu2_ = p2;

    MainWindow* w = new MainWindow;
    window_ = w;
    if (! window_->getTwoPlayerMode())
    {
        pulsu2_->setBeer(0);
        pulsu2_->setStamina(0);
        window_->addPulsu(pulsu_, pulsu2_);
    }
    else
    {
        window_->addBothPulsus(pulsu_, pulsu2_);
    }
    window_->givePulsuType(window_->getPulsuType());
    window_->addBeer();
    std::vector<BeerItem*> beeritems = window_->returnBeerItems();

    city_ = std::make_shared <City>();
    city_->addPulsu(p1);
    city_->setMainWindow(w);


    Home* h = new Home;
    home_ = h;
    if (! window_->getTwoPlayerMode())
    {
        window_->addHome(home_);
    }

    GameLogic* l = new GameLogic;
    logic_ = l;
    l->readOfflineData(CourseSide::DEFAULT_BUSES_FILE, CourseSide::DEFAULT_STOPS_FILE);
    l->takeCity(city_);
    l->takeCityAgain(city_);
    l->takePulsus(pulsu_, pulsu2_);
    l->setTwoPlayerMode(window_->getTwoPlayerMode());
    l->takeMainWindow(window_);
    l->takeHome(home_);
    l->takeBeers(beeritems);
    l->setTime(9,0);    // starting time 9 AM

    Statistics* s = new Statistics;
    statistics_ = s;
    window_->takeStatistics(s);

    QImage img_basic;
    QImage img_big;
    img_basic.load(":/offlinedata/offlinedata/kartta_pieni_500x500.png");
    img_big.load(":/offlinedata/offlinedata/kartta_iso_1095x592.png");
    city_->setBackground(img_basic, img_big);

    connect(window_,SIGNAL(gameStarted()),this,
            SLOT(startGame()));
}

ObjectGenerator::~ObjectGenerator()
{
    delete pulsu_;
    delete pulsu2_;
    delete window_;
    delete logic_;
    delete statistics_;
    delete home_;
}

MainWindow* ObjectGenerator::returnWindow()
{
    return window_;
}


void ObjectGenerator::startGame()
{
    logic_->finalizeGameStart();
}
