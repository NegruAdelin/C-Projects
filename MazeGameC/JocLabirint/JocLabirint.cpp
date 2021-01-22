#include "Map.h"
#include <conio.h>
#include "Player.h"
#include "Frame.h"




int main() {
	//Initialization of variables========================================================================
	char key_input;
	int ascii_code;

	Player player(20);
	Frame frame;

	int width, height, numberTraps, numberWalls;
	std::cout << "width: "; std::cin >> width;
	std::cout << "height: "; std::cin >> height;
	std::cout << "numberTraps: "; std::cin >> numberTraps;
	std::cout << "numberWalls: "; std::cin >> numberWalls;

	Map map;
	map.setColumn(width);
	map.setLine(height);
	
	map.setNumberTraps(numberTraps);
	map.setNumberWalls(numberWalls);
	map.setStart(player.getPosition());

	map.createMap();
	map.createWalls();
	map.createTraps();
	//End of initialization========================================================================

	//Generating of Map with Traps, Walls========================================================================
	PRINT("\tGenerating map");
	while (map.mapHasAnExit() == false) {
		map.createMap();
		map.createWalls();
		map.createTraps();

		system("cls");
		PRINT("\tGenerating map.");
		Sleep(300);
		
		system("cls");
		PRINT("\tGenerating map..");
		Sleep(300);
		
		system("cls");
		PRINT("\tGenerating map...");
		Sleep(300);
	}
	//End of Generating========================================================================

	//Display the game========================================================================
	int mapLine = map.getLine();
	std::vector<int> mapTraps = map.getTraps();

	system("cls");
	PRINT("\tPress Enter to start the game");

	do {
		key_input = _getch();
		ascii_code = key_input;
		
		//If esc is pressed the game is over
		if (ascii_code == 27)
			break;

		//If enter is pressed clear the screen
		if (ascii_code == 13)
			system("cls");


		player.playerMove(ascii_code, map);
		frame.refreshFrame(map, player);
		PRINT(' ');
		PRINT("                                                                       ");
		PRINT("                                                                       ");
		PRINT("                                                                       ");
		if ((player.isAtrap(player.getPosition() - 1, mapTraps) && (((player.getPosition() - 1) % mapLine) != (mapLine - 1))) ||
			(player.isAtrap(player.getPosition() + 1, mapTraps) && (((player.getPosition() + 1) % mapLine) != 0)) ||
			player.isAtrap(player.getPosition() - mapLine, mapTraps) ||
			player.isAtrap(player.getPosition() + mapLine, mapTraps)) {

			frame.refreshFrame(map, player);
			std::cout << "\t\n\n Near is one or more traps\t\nPress 'D' to disarm it\n";
		}

		if (key_input == 'D' || key_input == 'd') {
			frame.refreshFrame(map, player);

			if (player.isAtrap(player.getPosition() - 1, mapTraps) && (((player.getPosition() - 1) % mapLine) != (mapLine - 1)))
				player.disarmTrap(player.getPosition() - 1, mapTraps);
			
			if (player.isAtrap(player.getPosition() + 1, mapTraps) && (((player.getPosition() + 1) % mapLine) != 0))
				player.disarmTrap(player.getPosition() + 1, mapTraps);
			
			player.disarmTrap(player.getPosition() - mapLine, mapTraps);
			player.disarmTrap(player.getPosition() + mapLine, mapTraps);
			std::cout << "\t\n\n The trap/s was disarmed  \n                          ";
		}

	} while (!player.isDead(mapTraps) && !player.playerWin(map.getExit()));
	
	if (player.isDead(map.getTraps())) {
		PRINT("\n\n\n\t\tYou Dead\n\n\n");
	}
	else {
		PRINT("\n\n\n\t\tYou Won\n\n\n");
	}
	//End of the game========================================================================
	return 0;
}