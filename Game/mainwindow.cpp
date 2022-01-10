#include "mainwindow.hh"
#include "ui_mainwindow.h"

const int PADDING = 10;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->gameView->setFixedSize(width_, height_);
    ui->centralwidget->setFixedSize((width_ + ui->startButton->width() + PADDING) * 1.1, (height_ + PADDING) * 1.2);
    ui->startButton->move(width_ + PADDING , PADDING);

    MainWindow::setWindowTitle("Pulsupeli");

    ui->staminaLcd->setStyleSheet("background-color: black");
    ui->beerAmountLcd->setStyleSheet("background-color: black");
    ui->staminaLcd2->setStyleSheet("background-color: black");
    ui->beerAmountLcd2->setStyleSheet("background-color: black");

    map = new QGraphicsScene(this);
    ui->gameView->setScene(map);
    map->setSceneRect(0,0,width_,height_);

    resize(minimumSizeHint());
    ui->gameView->fitInView(0, 0, MAPWIDTH, MAPHEIGHT, Qt::KeepAspectRatio);

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, map, &QGraphicsScene::advance);
    timer->start(tick_);

    gameRunning_ = false;
    gameEndedWell_ = false;

    ui->getOnButton->setDisabled(true);
    ui->getOffButton->setDisabled(true);
    ui->drinkBeerButton->setDisabled(true);

    ui->getOnButton2->setDisabled(true);
    ui->getOffButton2->setDisabled(true);
    ui->drinkBeerButton2->setDisabled(true);

    int seed = time(0);
    randomEng.seed(seed);
    notGettingIntoBusDistr = std::uniform_int_distribution<int>(0, NOT_GETTING_INTO_BUS_PROBABILITY);
    findingNikesDistr = std::uniform_int_distribution<int>(0, FINDING_NIKES_PROBABILITY);
    findingBeerDistr = std::uniform_int_distribution<int>(0, FINDING_BEER_PROBABILITY);

    //eliminate first rng as it's most likely 0
    notGettingIntoBusDistr(randomEng);

    Dialog* mdialog = new Dialog(this);
    connect(mdialog,SIGNAL(sendPulsuType(int)),this,
            SLOT(setPulsuType(int)));
    connect(mdialog,SIGNAL(sendTwoPlayerMode(bool)),this,
            SLOT(setTwoPlayerMode(bool)));
    connect(mdialog,SIGNAL(dontStart()),this,
            SLOT(dontStartGame()));

    twoPlayerMode_ = false;

    readFile();
    mdialog->exec();

    if (! twoPlayerMode_)
    {
        ui->textBrowser->setText("You wake up cold and hungry and want to go home. But not without beer.");
    }
    else
    {
        ui->textBrowser->setText("You wake up cold and lonely and see that your significant pulsu (SP) is not by your side. You need to find them. But not without beer.");
    }

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateMap()
{
    map->update();
}

QGraphicsItem* MainWindow::returnActor(int index)
{
    return actors_.at(index);
}

void MainWindow::setSize(int w, int h)
{
    width_ = w;
    height_ = h;
}

void MainWindow::setTick(int t)
{
    tick_ = t;
}

void MainWindow::addNysse(int locX, int locY)
{
    NysseItem* nActor = new NysseItem(locX, locY);
    actors_.push_back(nActor);
    map->addItem(nActor);
}

void MainWindow::addPassenger(int locX, int locY)
{
    PassengerItem* nActor = new PassengerItem(locX, locY);
    actors_.push_back(nActor);
    map->addItem(nActor);
}

void MainWindow::setPicture(QImage &img)
{
    map->setBackgroundBrush(img);
}

void MainWindow::addPulsu(Pulsu* p1, Pulsu* p2)
{
    pulsu_ = p1;
    pulsu2_ = p2;
    PulsuItem* nActor = new PulsuItem(pulsu_->getX(), pulsu_->getY());
    pulsu_->takeActor(nActor);
    map->addItem(nActor);
}

void MainWindow::addHome(Home* h)
{
    home_ = h;
    HomeItem* nActor = new HomeItem(home_->getLocation().at(0), home_->getLocation().at(1));
    home_->takeActor(nActor);
    map->addItem(nActor);
}

void MainWindow::givePulsuType(int type)
{
    pulsu_->setPulsuType(type);
}

void MainWindow::takeStatistics(Statistics* s)
{
    statistics_ = s;
}

void MainWindow::addBothPulsus(Pulsu* p1, Pulsu* p2)
{
    pulsu_ = p1;
    pulsu2_ = p2;
    PulsuItem* nActor = new PulsuItem(pulsu_->getX(), pulsu_->getY());
    pulsu_->takeActor(nActor);
    map->addItem(nActor);

    pulsu2_->changeGender();
    pulsu2_->movePulsu(800, 400);   // starting point for player2
    PulsuItem* nActor2 = new PulsuItem(pulsu2_->getX(), pulsu2_->getY());
    nActor2->changeGender();
    pulsu2_->takeActor(nActor2);
    map->addItem(nActor2);
}

int MainWindow::getPulsuType()
{
    return pulsuType_;
}

void MainWindow::addBeer()
{
    for (auto beer: BEERS) {
        int x = beer.at(0);
        int y = beer.at(1);
        BeerItem* nBeer = new BeerItem(x,y);
        beeritems_.push_back(nBeer);
        map->addItem(nBeer);
    }
}

std::vector<BeerItem *> MainWindow::returnBeerItems()
{
    return beeritems_;
}

void MainWindow::removeItem(BeerItem * beer)
{
    map->removeItem(beer);
}

bool MainWindow::getTwoPlayerMode()
{
    return twoPlayerMode_;
}

void MainWindow::setPulsuType(int type)
{
    pulsuType_ = type;
}

void MainWindow::setTwoPlayerMode(bool onko)
{
    twoPlayerMode_ = onko;
}

void MainWindow::dontStartGame()
{
    exit(0);
}

void MainWindow::on_startButton_clicked()
{
    ui->startButton->setDisabled(true);
    ui->drinkBeerButton->setEnabled(true);
    if (twoPlayerMode_)
    {
        ui->drinkBeerButton2->setEnabled(true);
    }
    emit gameStarted();
    ui->staminaLcd->display(pulsu_->getStamina());
    ui->beerAmountLcd->display(pulsu_->getBeer());
    ui->staminaLcd2->display(pulsu2_->getStamina());
    ui->beerAmountLcd2->display(pulsu2_->getBeer());
    gameRunning_ = true;
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if ((gameRunning_) && (pulsu_->getStamina() > 0) && (! pulsu_->getBusStatus()))
    {
        if(event->key() == Qt::Key_A)
        {
            pulsu_->moveLeft();
            pulsu_->decreaseStamina();
            statistics_->pulsu1MoveTaken();
        }

        if(event->key() == Qt::Key_D)
        {
            pulsu_->moveRight();
            pulsu_->decreaseStamina();
            statistics_->pulsu1MoveTaken();
        }

        if(event->key() == Qt::Key_W)
        {
            pulsu_->moveUp();
            pulsu_->decreaseStamina();
            statistics_->pulsu1MoveTaken();
        }

        if(event->key() == Qt::Key_S)
        {
            pulsu_->moveDown();
            pulsu_->decreaseStamina();
            statistics_->pulsu1MoveTaken();
        }
        pulsu_->drawPulsu();

        if((event->key() == Qt::Key_A) || (event->key() == Qt::Key_D) || (event->key() == Qt::Key_W) || (event->key() == Qt::Key_S))
        {
            int randomInt = findingNikesDistr(randomEng);
            if ((randomInt == FINDING_NIKES_PROBABILITY) && (! pulsu_->getShoeStatus()))
            {
                MainWindow::findShoes(pulsu_);
            }
            int randomInt2 = findingBeerDistr(randomEng);
            if (randomInt2 == FINDING_BEER_PROBABILITY)
            {
                MainWindow::findBeer(pulsu_);
            }
        }
    }

    if ((gameRunning_) && (pulsu2_->getStamina() > 0) && (! pulsu2_->getBusStatus()) && (twoPlayerMode_))
    {
        if(event->key() == Qt::Key_J)
        {
            pulsu2_->moveLeft();
            pulsu2_->decreaseStamina();
            statistics_->pulsu2MoveTaken();
        }

        if(event->key() == Qt::Key_L)
        {
            pulsu2_->moveRight();
            pulsu2_->decreaseStamina();
            statistics_->pulsu2MoveTaken();
        }

        if(event->key() == Qt::Key_I)
        {
            pulsu2_->moveUp();
            pulsu2_->decreaseStamina();
            statistics_->pulsu2MoveTaken();
        }

        if(event->key() == Qt::Key_K)
        {
            pulsu2_->moveDown();
            pulsu2_->decreaseStamina();
            statistics_->pulsu2MoveTaken();
        }
        pulsu2_->drawPulsu();

        if((event->key() == Qt::Key_J) || (event->key() == Qt::Key_L) || (event->key() == Qt::Key_I) || (event->key() == Qt::Key_K))
        {
            int randomInt3 = findingNikesDistr(randomEng);
            if ((randomInt3 == FINDING_NIKES_PROBABILITY) && (! pulsu2_->getShoeStatus()))
            {
                MainWindow::findShoes(pulsu2_);
            }
            int randomInt4 = findingNikesDistr(randomEng);
            if (randomInt4 == FINDING_BEER_PROBABILITY)
            {
                MainWindow::findBeer(pulsu2_);
            }
        }
    }

    if (gameRunning_)
    {
        if((event->key() == Qt::Key_Q) && (ui->getOnButton->isEnabled() == true) && (ui->getOffButton->isEnabled() == false))
        {
            MainWindow::on_getOnButton_clicked();
        }
        else if((event->key() == Qt::Key_Q) && (ui->getOnButton->isEnabled() == false) && (ui->getOffButton->isEnabled() == true))
        {
            MainWindow::on_getOffButton_clicked();
        }

        if((event->key() == Qt::Key_U) && (ui->getOnButton2->isEnabled() == true) && (ui->getOffButton2->isEnabled() == false))
        {
            MainWindow::on_getOnButton2_clicked();
        }
        else if((event->key() == Qt::Key_U) && (ui->getOnButton2->isEnabled() == false) && (ui->getOffButton2->isEnabled() == true))
        {
            MainWindow::on_getOffButton2_clicked();
        }

        if ((event->key() == Qt::Key_E) && (ui->drinkBeerButton->isEnabled() == true))
        {
            MainWindow::on_drinkBeerButton_clicked();
        }
        else if ((event->key() == Qt::Key_O) && (ui->drinkBeerButton2->isEnabled() == true))
        {
            MainWindow::on_drinkBeerButton2_clicked();
        }

        MainWindow::updateStats();
    }

    if ((pulsu_->getStamina() == 0) && (pulsu_->getBeer() == 0) && (gameRunning_))
    {
        MainWindow::finishGameBad(pulsu_);
    }
    else if ((pulsu2_->getStamina() == 0) && (pulsu2_->getBeer() == 0) && (gameRunning_) && (twoPlayerMode_))
    {
        MainWindow::finishGameBad(pulsu2_);
    }
}

void MainWindow::updateStats()
{
    ui->staminaLcd->display(pulsu_->getStamina());
    ui->beerAmountLcd->display(pulsu_->getBeer());
    ui->staminaLcd2->display(pulsu2_->getStamina());
    ui->beerAmountLcd2->display(pulsu2_->getBeer());
}

void MainWindow::setGetOnButtonEnabled()
{
    ui->getOnButton->setEnabled(true);
}

void MainWindow::setGetOnButtonDisabled()
{
    ui->getOnButton->setDisabled(true);
}

void MainWindow::setGetOnButton2Enabled()
{
    ui->getOnButton2->setEnabled(true);
}

void MainWindow::setGetOnButton2Disabled()
{
    ui->getOffButton2->setDisabled(true);
}

void MainWindow::finishGameBad(Pulsu* p)
{
    gameRunning_ = false;
    QString name;
    if (p->getPulsuType() == 1)
    {
        name = "Jan-Eerik";
    }
    else
    {
        name = "Raija";
    }
    ui->gameStatusLabel->setText("Game over, RIP");
    ui->nameLabel->setText(name);
    ui->drinkBeerButton->setDisabled(true);
    p->killPulsu();
}

void MainWindow::finishGameGood()
{
    gameRunning_ = false;
    gameEndedWell_ = true;
    pulsu_->getOffBus();
    pulsu2_->getOffBus();
    QString name;
    if (pulsu_->getPulsuType() == 1)
    {
        name = "Jan-Eerik!";
    }
    else
    {
        name = "Raija!";
    }
    if (twoPlayerMode_)
    {
        name = "Jan-Eerik and Raija!";
    }
    ui->gameStatusLabel->setText("Congratulations");
    ui->nameLabel->setText(name);
    ui->beerLabel->setText("Final score:");
    ui->drinkBeerButton->setDisabled(true);
    ui->drinkBeerButton2->setDisabled(true);
    ui->getOnButton->setDisabled(true);
    ui->getOnButton2->setDisabled(true);
    ui->getOffButton->setDisabled(true);
    ui->getOffButton2->setDisabled(true);
    ui->beerLabel2->setText("");
    if (! twoPlayerMode_)
    {
        ui->textBrowser->setText("You made it home alive!");
    }
    else
    {
        ui->textBrowser->setText("You found each other and made sweet pulsu love!");
        ui->beerAmountLcd->display(pulsu_->getBeer() + pulsu2_->getBeer());
        ui->beerAmountLcd2->display(0);
    }
}

void MainWindow::enableDrinkButton()
{
    ui->drinkBeerButton->setEnabled(true);
}

void MainWindow::enableDrinkButton2()
{
    ui->drinkBeerButton2->setEnabled(true);
}

bool MainWindow::getRunning()
{
    return gameRunning_;
}

bool MainWindow::gameEndedWell()
{
    return gameEndedWell_;
}

void MainWindow::writeScore()
{
    std::ofstream obj;
    obj.open("scorename1.txt", std::ofstream::app);
    QString newname = "";
    int inparts = 0;
    for (auto i: playername_) {
        if (i == ' ') {
           inparts += 1;
         }
    }

    if (inparts != 0) {
        std::vector<QString> name = split(playername_, ' ');
        for (int j = 0; j <= inparts; j++) {
             newname = newname.append(name.at(j));
           }
        }
    else {
         newname = playername_;
     }


    if (! twoPlayerMode_)
    {
        obj << newname.toStdString() << " " << pulsu_->getBeer() << std::endl;
    }
    else
    {
        obj << newname.toStdString() << " " << pulsu_->getBeer()
            +pulsu2_->getBeer() << std::endl;
    }

    std::ofstream obj2;
    obj2.open("score1.txt", std::ofstream::app);
    if (! twoPlayerMode_)
        {
            obj2 << pulsu_->getBeer() << std::endl;
        }
        else
        {
            obj2 << pulsu_->getBeer() +pulsu2_->getBeer() << std::endl;
        }

    obj.close();
    obj2.close();
}

void MainWindow::readFile()
{
    ui->scoreTextBrowser->clear();
    QFile file("scorename1.txt");
    file.open(QIODevice::ReadOnly);
    QTextStream in(&file);
    QFile file2("score1.txt");
    file2.open(QIODevice::ReadOnly);
    QTextStream in2(&file2);
    std::vector<QString> vec = {};
    std::vector<std::vector<QString>> scoresandnames = {};
    std::vector<int> scores = {};

    while (! in.atEnd())
    {
        QString line = in.readLine();
        vec = MainWindow::split(line, ' ');
        std::vector<QString> scoreandnamepair = {vec.at(0), vec.at(1)};
        scoresandnames.push_back(scoreandnamepair);
    }

    while (! in2.atEnd())
    {
        QString line = in2.readLine();
        int score = line.toInt();
        scores.push_back(score);
    }
    std::sort(scores.begin(), scores.end(), std::greater<>());
    if (scores.size() > TOP_LIST_LENGTH)
    {
        scores.erase(scores.begin() + TOP_LIST_LENGTH, scores.end());
    }

    for (int score : scores)
    {
        bool alreadyAdded = false;
        for (unsigned long int i = 0; i < scoresandnames.size(); ++i)
        {
            std::vector<QString> pair = scoresandnames.at(i);
            if ((score == pair.at(1).toInt()) && (alreadyAdded == false))
            {
                ui->scoreTextBrowser->append(pair.at(0) + " " + pair.at(1));
                scoresandnames.erase(scoresandnames.begin() + i);
                --i;
                alreadyAdded = true;
            }
        }
    }
    file.close();
    file2.close();
}

std::vector<QString> MainWindow::split(QString& str, char delim)
{
    QString working_space;
    std::vector<QString> final_result;
    for (QChar x : str)
    {
        if (x == delim)
        {
            if (working_space != "")
            {
                final_result.push_back(working_space);
                working_space = "";
            }
        }
        else
        {
            working_space += x;
        }
    }

    if (working_space != "")
    {
        final_result.push_back(working_space);
    }
    return final_result;
}

void MainWindow::clearScoreBoard()
{
    ui->scoreTextBrowser->clear();
}

void MainWindow::findBeer(Pulsu* p)
{
    p->increaseBeer();
    if (twoPlayerMode_)
    {
        QString name;
        if (p->getPulsuType() == 1)
        {
            name = "Jan-Eerik";
            ui->drinkBeerButton->setEnabled(true);
        }
        else
        {
            name = "Raija";
            ui->drinkBeerButton2->setEnabled(true);
        }
        ui->textBrowser->setText(name);
        ui->textBrowser->append("found a half-drunk can of Lappari. But for");
        ui->textBrowser->append(name);
        ui->textBrowser->append("it is a full one.");
    }
    else
    {
        ui->textBrowser->setText("You found a half-drunk can of Lappari. But for you it is a full one.");
        ui->drinkBeerButton->setEnabled(true);
    }
}

void MainWindow::findShoes(Pulsu* p)
{
    p->findShoes();
    if (twoPlayerMode_)
    {
        QString name;
        if (p->getPulsuType() == 1)
        {
            name = "Jan-Eerik";
        }
        else
        {
            name = "Raija";
        }
        ui->textBrowser->setText(name);
        ui->textBrowser->append("randomly stumbles upon a pair of Nikes with flames on them.");
        ui->textBrowser->append(name);
        ui->textBrowser->append("now moves incredibly fast!");
    }
    else
    {
        ui->textBrowser->setText("You randomly stumble upon a pair of Nikes with flames on them. You now move incredibly fast!");
    }
}

void MainWindow::changeBeerFoundText(Pulsu* p)
{
    QString name;
    if (p->getPulsuType() == 1)
    {
        name = "Jan-Eerik";
    }
    else
    {
        name = "Raija";
    }
    ui->textBrowser->setText(name);
    ui->textBrowser->append("found a beer!");
}

void MainWindow::on_getOnButton_clicked()
{
    int randInt = notGettingIntoBusDistr(randomEng);
    if (randInt == NOT_GETTING_INTO_BUS_PROBABILITY)
    {
        ui->textBrowser->clear();
        if (twoPlayerMode_)
        {
            ui->textBrowser->append("Jan-Eerik's beautiful smile didn't work this time, as the driver didn't let him ride the nysse for free.");
        }
        else
        {
            ui->textBrowser->setText("Your beautiful smile didn't work this time, as the driver didn't let you ride the nysse for free.");
        }

    }
    else
    {
        pulsu_->getOnBus();
        ui->getOnButton->setDisabled(true);
        ui->getOffButton->setEnabled(true);
    }

}

void MainWindow::on_getOffButton_clicked()
{
    pulsu_->getOffBus();
    ui->getOffButton->setDisabled(true);
}

void MainWindow::on_getOnButton2_clicked()
{
    int randInt = notGettingIntoBusDistr(randomEng);
    if (randInt == NOT_GETTING_INTO_BUS_PROBABILITY)
    {
        ui->textBrowser->clear();
        ui->textBrowser->append("Raija's beautiful bosom didn't work this time, as the driver didn't let her ride the nysse for free.");
    }
    else
    {
        pulsu2_->getOnBus();
        ui->getOnButton2->setDisabled(true);
        ui->getOffButton2->setEnabled(true);
    }

}

void MainWindow::on_getOffButton2_clicked()
{
    pulsu2_->getOffBus();
    ui->getOffButton2->setDisabled(true);
}

void MainWindow::on_drinkBeerButton_clicked()
{
    bool drunk = pulsu_->drinkBeer();
    statistics_->beerDrunk();
    MainWindow::updateStats();
    if (pulsu_->getBeer() == 0)
    {
        ui->drinkBeerButton->setDisabled(true);
    }
    if (pulsu_->getBusStatus())
    {
        finishGameBad(pulsu_);
        pulsu_->getOffBus();
        ui->drinkBeerButton->setDisabled(true);
        ui->drinkBeerButton2->setDisabled(true);
        ui->getOffButton->setDisabled(true);
        if (twoPlayerMode_)
        {
            ui->textBrowser->setText("Jan-Eerik drank beer in a bus and a Poliisi-setä came and took him to jail :(");
        }
        else
        {
            ui->textBrowser->setText("You drank beer in a bus and a Poliisi-setä came and took you to jail :(");
        }
    }
    else if (drunk)
    {
        if (twoPlayerMode_)
        {
            ui->textBrowser->setText("Jan-Eerik has drunk a respectable amount of beer and starts to move in interesting ways. Jan-Eerik now moves slower.");
        }
        else
        {
            ui->textBrowser->setText("You have drunk a respectable amount of beer and start to move in interesting ways. You now move slower.");
        }
    }
}

void MainWindow::on_drinkBeerButton2_clicked()
{
    bool drunk = pulsu2_->drinkBeer();
    statistics_->beerDrunk();
    MainWindow::updateStats();
    if (pulsu2_->getBeer() == 0)
    {
        ui->drinkBeerButton2->setDisabled(true);
    }
    if (pulsu2_->getBusStatus())
    {
        finishGameBad(pulsu2_);
        pulsu_->getOffBus();
        pulsu2_->getOffBus();
        ui->drinkBeerButton->setDisabled(true);
        ui->getOffButton->setDisabled(true);
        ui->drinkBeerButton2->setDisabled(true);
        ui->getOffButton2->setDisabled(true);
        ui->textBrowser->setText("Raija drank beer in a bus and a Poliisi-setä came and took her to jail :(");
    }
    else if (drunk)
    {
        ui->textBrowser->setText("Raija has drunk a respectable amount of beer and starts to move in interesting ways. Raija now moves slower.");
    }
}

void MainWindow::on_nameLineEdit_editingFinished()
{
    playername_ = ui->nameLineEdit->text();
}
