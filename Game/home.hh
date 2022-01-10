#ifndef HOME_HH
#define HOME_HH

#include "homeitem.hh"
#include <vector>
#include <random>

/**
 * @file
 * @brief Defines Home class, which acts as the goal of the game.
 */

const std::vector<std::vector<int>> POSSIBLE_LOCATIONS =
                        {{500, 100}, {750, 100}, {1000, 100},
                        {500, 300}, {750, 300}, {1000, 300},
                        {500, 500}, {750, 500}, {1000, 500}};

class Home
{
public:

    /**
     * @brief Home generates a location randomly from POSSIBLE_LOCATIONS.
     * @pre -
     * @post Home is created.
     */
    Home();

    /**
     * @brief getLocation returns location of home.
     * @pre -
     * @return location_
     * @post location_ has been returned.
     */
    std::vector<int> getLocation();

    /**
     * @brief takeActor gives Home a HomeItem.
     * @param homeitem: pointer to HomeItem
     * @pre -
     * @post homeItem_ has been set to homeitem.
     */
    void takeActor(HomeItem*);

    /**
     * @brief returnHomeItem returns HomeItem corresponding to Home.
     * @pre homeItem_ has been set.
     * @return homeItem_
     * @post homeItem_ is returned.
     */
    HomeItem *returnHomeItem();

private:
    std::default_random_engine random_eng;
    std::uniform_int_distribution<int> distr;
    std::vector<int> location_;
    HomeItem* homeItem_;
};

#endif // HOME_HH
