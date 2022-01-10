# Programming 3 course project
Authors: Vilma Heikkilä and Matias Jokinen (27.11.2020)

This is a bus game (Nyssepeli) made as a group project for the Programming 3 course. The purpose of this project was to practice 
inheritance, GUI making, unit tests, and event-based programming. From the course's side the files and abstract classes in the Course folder were already implemented. The complete documentation for the game can be found in the "Dokumentaatio" folder (in Finnish). 

# Game rules
In the single-player mode you are a drunkard waking up cold and thirsty in the center of Tampere, and you want to go home. You must find your way to the home visible on the map, using both your own feet and free bus rides. You can drink beer to get extra stamina for walking, but beware of drinking too much; your final points once you reach home are based on the number of beers you have left. On the map you can also see beer bottles that you collect by walking over them. There are also random events in the game: you can find a beer, find faster shoes, go to jail (not so random), and you may not be let on the bus. In the two-player mode your goal is not to get home, but to get to your lovely drunk partner.



# Instructions
When the game first starts you are greeted with a dialog where you can choose your character and game mode. To play single mode, choose one of the two characters available (Jan-Eerik or Raija). To play two-player mode, choose "Both". The exit button ends the game without opening the main window, and the OK button starts the game.
When the main window opens the game doesn't start right away, and the player can enter their name for the top 10 list, read the lore of the game, and check out the top 10 list. The start button starts the game and the buses and the player character can get moving.
In the single-player mode the move keys are WASD, and drinking beer and boarding the bus happens either by pressing their respective buttons, or via keyboard (Q for entering and exiting a bus, E for drinking). In the two-player mode Jan-Eerik has the same controls and Raija moves with IJKL, and interacts with buses with the U key and drinks with the O key.

The characters can move as long as they have stamina, and each move consumes one stamina point. By drinking beer you can get some extra stamina. You can collect the beers on the map by walking over them. You can enter a bus when you are near one. In the single-player mode you win the game by walking to the home icon, and in the two-player mode you win by walking to the other player.

If you drink beer on the bus, the game ends and you lose. There are three random events. Two of them can activate after moving (find shoes -> walk faster, find beer -> +1 beer). The third event can activate when you try to enter a bus, and the bus driver won't let the player enter. After drinking a certain amount of beer, the player character gets drunk and walks slower. Almost all events will have a notification in the text field in the upper corner.

Once the game is over, the player can no longer move and the number of beers equals the final points. If your points are high enough, they will be listed on the top 10 list. You can also lose the game by drinking in the bus, or having both your stamina and number of beers drop to zero.


Note (10.1.2022): writing to the top 10 list doesn't seem to work anymore.

- Built with Qt Creator (version number?)
