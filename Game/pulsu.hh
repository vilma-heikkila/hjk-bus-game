#ifndef PULSU_HH
#define PULSU_HH

#include "pulsuitem.hh"
#include <QObject>

/**
 * @file
 * @brief Defines the Pulsu class, which creates the main actor object(s) of the game.
 */

class Pulsu: public QObject
{
    Q_OBJECT
public:
    Pulsu();

    /**
     * @brief getX returns x coordinate.
     * @pre -
     * @return x_
     * @post x_ returned.
     */
    int getX();

    /**
     * @brief getY returns y coordinate.
     * @pre -
     * @return y_
     * @post y_ returned.
     */
    int getY();

    /**
     * @brief setX sets x coordinate.
     * @param x: x coordinate
     * @pre -
     * @post x_ set to x.
     */
    void setX(int x);

    /**
     * @brief setY sets y coordinate.
     * @param y: y coordinate
     * @pre -
     * @post y_ set to y.
     */
    void setY(int y);

    /**
     * @brief takeActor sets PulsuItem.
     * @param Pointer to PulsuItem.
     * @pre -
     * @post pulsuItem_ set to item.
     */
    void takeActor(PulsuItem*);

    /**
     * @brief moveUp changes y coordinate.
     * @pre -
     * @post y_ changed.
     */
    void moveUp();

    /**
     * @brief moveUp changes y coordinate.
     * @pre -
     * @post y_ changed.
     */
    void moveDown();

    /**
     * @brief moveRight changes x coordinate.
     * @pre -
     * @post x_ changed.
     */
    void moveRight();

    /**
     * @brief moveRight changes x coordinate.
     * @pre -
     * @post x_ changed.
     */
    void moveLeft();

    /**
     * @brief drawPulsu draws PulsuItem.
     * @pre pulsuItem_ has been set.
     * @post pulsuItem_ coordinates are changed and the
     *       item is updated (drawn again).
     */
    void drawPulsu();

    /**
     * @brief setPulsuType sets pulsuType_.
     * @param type: Pulsu type.
     * @pre -
     * @post pulsuType_ set to type, giveTypeToItem() called.
     */
    void setPulsuType(int type);

    /**
     * @brief getStamina returns pulsuStamina_.
     * @pre -
     * @return pulsuStamina_
     * @post pulsuStamina_ returned.
     */
    int getStamina();

    /**
     * @brief getPulsuType returns pulsuType_.
     * @pre -
     * @return pulsuType_
     * @post pulsuType_ returned.
     */
    int getPulsuType();

    /**
     * @brief giveTypeToItem gives type to PulsuItem.
     * @pre pulsuItem_ has been set.
     * @post getType() is called for pulsuItem.
     */
    void giveTypeToItem();

    /**
     * @brief getBeer returns beer amount.
     * @pre -
     * @return pulsuBeer_
     * @post pulsuBeer_ returned.
     */
    int getBeer();

    /**
     * @brief drinkBeer increases beer amount.
     * @pre -
     * @return true if Pulsu is drunk, false if not.
     * @post pulsuBeer_ decreased, pulsuStamina_ increased,
     *       alreadyDrunk_ might be set to true and speed_
     *       decreased.
     */
    bool drinkBeer();

    /**
     * @brief increaseBeer increases beer amount.
     * @pre -
     * @post pulsuBeer_ increased by 1.
     */
    void increaseBeer();

    /**
     * @brief killPulsu performs Pulsu death "animation".
     * @pre The game is in bad game ending state.
     * @post pulsuItem_ is rotated and drawn again.
     */
    void killPulsu();

    /**
     * @brief getOnBus makes Pulsu get on bus.
     * @pre A Nysse is near.
     * @post isOnBus_ is set to true.
     */
    void getOnBus();

    /**
     * @brief getOffBus makes Pulsu get off bus.
     * @pre Pulsu is on a bus.
     * @post isOnBus_ is set to false.
     */
    void getOffBus();

    /**
     * @brief getBusStatus notifies if Pulsu is on a bus.
     * @pre -
     * @return isOnBus_
     * @post isOnBus_ returned.
     */
    bool getBusStatus();

    /**
     * @brief movePulsu moves Pulsu to given coordinates.
     * @param x: x coordinate
     * @param y: y coordinate
     * @pre -
     * @post x_ is set to x, y_ is set to y.
     */
    void movePulsu(int x, int y);

    /**
     * @brief decreaseStamina decreases stamina.
     * @pre -
     * @post pulsuStamina_ decreased by 1, if possible.
     */
    void decreaseStamina();

    /**
     * @brief changeGender takes care of Pulsu type issue in
     *        two player mode, switches types around.
     * @pre -
     * @post pulsuType_ is set to 1 or 2.
     */
    void changeGender();

    /**
     * @brief setStamina sets stamina.
     * @param x: amount of stamina
     * @pre -
     * @post pulsuStamina_ set to x.
     */
    void setStamina(int);

    /**
     * @brief setBeer sets beer amount.
     * @param x: amount of beer
     * @pre -
     * @post pulsuBeer_ set to x.
     */
    void setBeer(int);

    /**
     * @brief returnPulsuItem returns PulsuItem.
     * @pre pulsuItem_ has been set.
     * @return pulsuItem_
     * @post pulsuItem_ returned.
     */
    PulsuItem *returnPulsuItem();

    /**
     * @brief findShoes changes Pulsu movement speed.
     * @pre -
     * @post speed_ is increasedd by 5, shoesFound_ set to true.
     */
    void findShoes();

    /**
     * @brief getShoeStatus returns Pulsu shoe status.
     * @pre -
     * @return shoesFound_
     * @post shoesFound_ returned.
     */
    bool getShoeStatus();

private:
    int x_;
    int y_;
    float speed_;
    PulsuItem* pulsuItem_;
    // pulsujuice attribuutti
    int pulsuStamina_;
    int pulsuBeer_; // vaikuttaa loppupisteisiin
    int pulsuType_;
    bool isOnBus_;
    int beersDrunk_;
    bool shoesFound_;
    bool alreadyDrunk_;

};

#endif // PULSU_HH
