//----------------------------------------------------------------------------
// File:		fleet.h
// 
// Description: Sink the Fleet declarations
//	
// Programmer:	Paul Bladek
//
// Modified by: 
//				Albert Shymanskyy
//				Cameron Stevenson
// 
// Environment: Hardware: PC
//              Software: Windows 10 
//              Compiles under Microsoft Visual C++ 2017
//----------------------------------------------------------------------------

#ifndef FLEET_H
#define FLEET_H

#include <iostream>
#include <fstream>
#include <cctype>
#include <iomanip>
#include <string>
#include <sstream>
#include "textGraphics.h"
#include "safeio.h"

using namespace std;

// Number of players in game
const short NUMPLAYERS = 2;
// Number of rows/columns in small sea array
const short SMALLROWS = 8;
// Number of rows/columns in large sea array
const short LARGEROWS = 10;
// Number of rows/columns in small sea array
const short SMALLCOLS = 12;
// Number of rows/columns in large sea array
const short LARGECOLS = 24;
// Maximum screen line length
const short BOXWIDTH = 79;
// Size of the shipSize array
const int SHIP_SIZE_ARRAYSIZE = 6; 
// Number of elements for each ship
const short shipSize[SHIP_SIZE_ARRAYSIZE] = {0, 2, 3, 3, 4, 5}; 

//----------------------------------------------------------------------------
// Enumerated type for ships
//----------------------------------------------------------------------------
enum Ship
{
	NOSHIP,		 // 0
	MINESWEEPER, // 1 (1-5) -- used only for owner
	SUB,		 // 2
	FRIGATE,	 // 3
	BATTLESHIP,	 // 4
	CARRIER,	 // 5
	HIT,		 // 6 (6-7)-- used only for other side
	MISSED,		 // 7 
}; 

//----------------------------------------------------------------------------
// Enumerated type for direction on grid
//----------------------------------------------------------------------------
enum Direction
{
	HORIZONTAL, // 0
	VERTICAL	// 1
};

//----------------------------------------------------------------------------
// Row and column location
//----------------------------------------------------------------------------
struct Cell
{
	// Row
	unsigned short m_row;
	// Column
	unsigned short m_col;
}; 

//----------------------------------------------------------------------------
// Needed info about each ship
//----------------------------------------------------------------------------
struct ShipInfo
{
	// Which ship?
	Ship m_name;
	// Which direction is the ship facing? 
	Direction m_orientation;
	// Which cell is the bow location?
	Cell m_bowLocation;
	// How many sections are left undestroyed?
	short m_piecesLeft;
};

//----------------------------------------------------------------------------
// Needed info about each player
//----------------------------------------------------------------------------
struct Player
{
	// One 2-d array for each player
	Ship ** m_gameGrid[NUMPLAYERS]; 
		// [0] is player's grid;
		// [1] is opponent's grid

	// Ships in fleet
	ShipInfo m_ships[SHIP_SIZE_ARRAYSIZE];
		// [0] is blank	

	// How many sections of fleet are left?
	short m_piecesLeft;
};

//----------------------------------------------------------------------------
// Function prototypes for ship
//----------------------------------------------------------------------------

// Prints to sout one individual ship
void printShip(ostream & sout, Ship thisShip);

// Prints a specific game grid
void printGrid(ostream& sout, Ship** grid, char size); 

//----------------------------------------------------------------------------
// Function prototypes for ShipInfo
//----------------------------------------------------------------------------

// Sets ShipInfo fields
void setShipInfo(ShipInfo * shipInfoPtr, Ship name = NOSHIP,
	Direction orientation = HORIZONTAL, unsigned short row = 0,
	unsigned short col = 0);

//----------------------------------------------------------------------------
// Function prototypes for Player
//----------------------------------------------------------------------------

// Sets initial values for m_ships and m_piecesLeft
void initializePlayer(Player* playerPtr);

// Allocates memory for grids
void allocMem(Player players[], char size);

// Deletes memory for grids
void deleteMem(Player players[], char size);

// Saves the ship grid to a file
void saveGrid(Player players[], short whichPlayer, char size);

// Reads grid from a file	
bool loadGridFromFile(Player players[], short whichPlayer, char size,
	string fileName);

// Allows user to put ships in grid
void setShips(Player players[], char size, short whichPlayer);

// Returns a cell with coordinates set by user
Cell getCoord(istream& sin, char size);

// Can the ship go there?
bool isValidLocation(const Player& player, short shipNumber, char size);
	
//----------------------------------------------------------------------------
// Other function prototypes
//----------------------------------------------------------------------------

// Prints opening graphic
void header(ostream& sout);

// Prints closinging graphic
void endBox(short player);

// Converts a character to a ship
Ship loadShip(char characterRead);

// Uses .get() on an ifstream grab amount of times.
void streamGrab(ifstream& ifs, int grabs);

#endif
