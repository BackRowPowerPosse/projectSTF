//----------------------------------------------------------------------------
// File:	    SinkTheFleetleet.cpp
// 
// Functions:   main()
//----------------------------------------------------------------------------

#include <iostream>
#include <iomanip>
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include "fleet.h"

#ifdef _DEBUG
#define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define new DEBUG_NEW
#endif

using namespace std;
extern const char* shipNames[7];

//----------------------------------------------------------------------------
// Function:	main()
//
// Title:		Main
//
// Description: Runs the "Sink the Fleet" Game
//
// Programmer:	Paul Bladek
// 
// Modified by: 
//				Albert Shymanskyy
//				Cameron Stevenson
// 
// Date:		01/30/2018
//
// Version:		1.0.0
// 
// Environment: 
//				Hardware: Variable
//				Software: OS: Windows 10;
//				Compiles under Microsoft Visual C++ 2017
//
// Input:		Grid files
//
// Output:		A game
//
// Calls:		
//				initializePlayer()
//				allocMem()
//				safeChoice()
//				loadGridFromFile()
//				printGrid()
//				resetGrid()
//				setships()
//				header()
//				getCoord()
//				deleteMem()
//				endBox()
//
// Called By:	None
//
// Parameters:	None
// 
// Returns:		EXIT_SUCCESS of type integer upon successful completion
//
// History Log: 
//				12/09/2010 PB completed v0.5.0
//				01/30/2018 Game completed v1.0.0
//   
//----------------------------------------------------------------------------
int main()
{
	// Total number of rows in the array
	short numRows = SMALLROWS;
	// Total number of columns in the array
	short numCols = SMALLCOLS;
	char again = 'N';
	char gridSize = 'S';
	short whichPlayer = 0;
	bool gameOver = false;
	bool reshot = false;
	Cell coord = {0, 0};
	string message = ", would you like to read starting grid from a file?";
	string filename;
	Ship shipHit = NOSHIP;
	// The two players in an array
	Player game[NUMPLAYERS];
	ostringstream outSStream;

	do
	{
		system("cls");
		cout << endl;
		header(cout);
		gridSize = safeChoice("Which size grid to you want to use", 'S', 'L');
		numRows = (toupper(gridSize) == 'L') ? LARGEROWS : SMALLROWS;
		numCols = (toupper(gridSize) == 'L') ? LARGECOLS : SMALLCOLS;

		initializePlayer(game);		
		initializePlayer(game + 1);
		// Dynamically create the rows of the array
		allocMem(game, gridSize);
		
		for(whichPlayer = 0; whichPlayer < NUMPLAYERS; whichPlayer++)
		{
			outSStream.str("");
			outSStream.clear();
			// Enter grid files or let users enter ships
			outSStream << "Player " << whichPlayer + 1 << message;

			if (safeChoice(outSStream.str(), 'Y', 'N') == 'Y')
			{
				cout << "Enter file name: ";
				std::cin >> filename;
				cin.get();
				filename.append(".shp");

				if (!loadGridFromFile(game, whichPlayer, gridSize,
					filename))
				{
					system("cls");
					--whichPlayer;
					continue;
				}

				if (safeChoice("OK?", 'Y', 'N') == 'N')
					--whichPlayer;

				system("cls");
			}
			else
				setShips(game, gridSize, whichPlayer);
		}

		// Pre-game header
		system("cls");
		cout << endl;
		header(cout);
		cout << "Press <Enter> to start the battle..." << endl;
		cin.get();
		whichPlayer = 0;
		
		// Gameplay
		while (!gameOver)
		{
			bool shipSunk = false;
			Ship whichShip;

			system("cls");
			printGrid(cout, game[whichPlayer].m_gameGrid[1], gridSize);
			cout << "Player " << whichPlayer + 1 << ", enter coordinates for"
				"firing:" << endl;
			coord = getCoord(cin, gridSize);

			// Check if player shot at this cell
			while (game[whichPlayer].m_gameGrid[1][coord.m_row][coord.m_col]
				!= NOSHIP)
			{
				cout << "You have already shot at " << static_cast<char>
					(coord.m_row + 'A') << coord.m_col + 1 << endl;
				cout << "Player " << whichPlayer + 1 << ", enter coordinates"
					<< "for firing:" << endl;
				coord = getCoord(cin, gridSize);
			} 

			whichShip = game[whichPlayer].m_gameGrid[0][coord.m_row]
				[coord.m_col];

			// Check if the coordinates contain a ship
			if (whichShip != NOSHIP)
			{
				// Decrements the amount of pieces left
				game[!whichPlayer].m_ships[whichShip].m_piecesLeft--;
				game[!whichPlayer].m_piecesLeft--;

				// Check if there are no more pieces of a ship left
				if (game[!whichPlayer].m_ships[whichShip].m_piecesLeft == 0)
					shipSunk = true;

				shipHit = game[whichPlayer].m_gameGrid[1][coord.m_row]
					[coord.m_col] = HIT;
				reshot = true;
				// Alert the player of a hit
				cout << '\a';
			}
			else
			{
				shipHit = game[whichPlayer].m_gameGrid[1][coord.m_row]
					[coord.m_col] = MISSED;

				if (reshot) reshot = false;
			}

			system("cls");
			printGrid(cout, game[whichPlayer].m_gameGrid[1], gridSize);
			cout << ((shipHit == 6) ? "HIT" : "MISSED") << endl;

			// Print which ship sank
			if (shipSunk) cout << shipNames[whichShip] << " SUNK" << endl;

			cout << "Press <Enter> to continue...";
			cin.get();

			// Check if other player lost
			if (!game[!whichPlayer].m_piecesLeft)
				gameOver = true;
			else
				// Switch players if cannot reshoot
				if (!reshot) whichPlayer = !whichPlayer;
		}
		
		endBox(whichPlayer);
		// Clean up memory
		deleteMem(game, gridSize);
		again = safeChoice("Would you like to play again?", 'Y', 'N');
	}
	while(again == 'Y');

	_CrtDumpMemoryLeaks();

	return EXIT_SUCCESS;
} 
