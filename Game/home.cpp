#include "home.hh"

Home::Home()
{
    int seed = time(0);
    random_eng.seed(seed);
    int amount = POSSIBLE_LOCATIONS.size();
    distr = std::uniform_int_distribution<int>(0, amount - 1);
    distr(random_eng);
    int x = distr(random_eng);
    location_ = POSSIBLE_LOCATIONS.at(x);
}

std::vector<int> Home::getLocation()
{
    return location_;
}

void Home::takeActor(HomeItem* homeitem)
{
    homeItem_ = homeitem;
}

HomeItem *Home::returnHomeItem()
{
    return homeItem_;
}
