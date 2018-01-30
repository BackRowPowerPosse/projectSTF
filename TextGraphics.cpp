//----------------------------------------------------------------------------
// File:	  TextGraphics.cpp
// 
// Functions:
//			  boxTop()
//			  boxBottom()
//			  boxLine()
//----------------------------------------------------------------------------

#include "textGraphics.h"

//----------------------------------------------------------------------------
// Function:	boxTop()
//
// Title:		Box Top
//
// Description: Draws a a line for the top of the box
//
// Programmer:	Paul Bladek
// 
// Date:		10/3/2006
//
// Version:		1.01
// 
// Environment: 
//				Hardware: PC
//              Software: Windows 10 
//              Compiles under Microsoft Visual C++ 2017
//
// Output:		Formatted line to sout
//
// Called By:	
//				header()
//				endbox()
//
// Parameters:	sout: ostream& -- stream to print to
//				length: unsigned short -- length of the box
// 
// Returns:		Void
//
// History Log:	
//				10/3/2006 PB completed v 1.01
//   
//----------------------------------------------------------------------------
void boxTop(ostream& sout, unsigned short length)
{
	if(length > MAX_LINE_LENGTH)
		length = MAX_LINE_LENGTH;
	sout.put(UL);
	for(int i = 0; i < length - OFFSET; i++)
		sout.put(HORIZ);
	sout.put(UR);
	sout << endl;
}

//----------------------------------------------------------------------------
// Function:	boxBottom()
//
// Title:		Box Bottom
//
// Description: Draws a a line for the bottom of the box
//
// Programmer:	Paul Bladek
// 
// Date:		10/3/2006
//
// Version:		1.01
// 
// Environment: Hardware: PC
//              Software: Windows 10 
//              Compiles under Microsoft Visual C++ 2017
//
// Output:		Formatted line to sout
//
// Called By:	
//				header()
//				endbox()
//
// Parameters:
//				sout: ostream& -- stream to print to
//				length: unsigned short -- length of the box
// 
// Returns:		Void
//
// History Log:	
//				10/3/2006 PB completed v 1.01
//   
//----------------------------------------------------------------------------
void boxBottom(ostream& sout, unsigned short length)
{
	if(length > MAX_LINE_LENGTH)
		length = MAX_LINE_LENGTH;
	sout.put(LL);
	for(int i = 0; i < length - OFFSET; i++)
		sout.put(HORIZ);
	sout.put(LR);
	sout << endl;
}

//----------------------------------------------------------------------------
// Function:	boxLine()
// Title:	Box Line
// Description:
//		draws a a line of text aligned in the middle of the box
// Programmer:	Paul Bladek
// 
// Date:	10/3/2006
//
// Version:	1.01
// 
// Environment: Hardware: PC
//              Software: Windows 10 
//              Compiles under Microsoft Visual C++ 2017
//
// Output:	Formatted text to sout
//
// Called By:	header()
//		endbox()
//
// Parameters:	sout: ostream&;	stream to print to
//		text: const string&; text to print
//		length: unsigned short;	length of the box
//		alignment: unsigned char;   'L' (left), 'C'(center),'R'(right)
//		fillc: char; fill character
// 
// Returns:	void
//
// History Log:	
//		10/3/2006 PB completed v 1.01
//   
//----------------------------------------------------------------------------
void boxLine(ostream& sout, const string& text, unsigned short length,
			 unsigned char alignment, char fillc)
{
	long originalformat = sout.flags(); // saves original format
	alignment = toupper(alignment);
	if(alignment != LEFT && alignment != RIGHT && alignment != CENTER)
		throw exception();
	if(length > MAX_LINE_LENGTH)
		length = MAX_LINE_LENGTH;
	sout << setfill(fillc); // change fill character
	sout.put(VERT);
	if(alignment == CENTER)
	{
		sout <<
			setw((length + static_cast<streamsize>(text.length()))
				/ 2 - 1)
			<< text 
			<< setw((length - static_cast<streamsize>
				(text.length())) / 2 - 1) 
			<< fillc;
		if(text.length() % 2 == 0)
			sout << fillc; 
	}
	else
	{ 
		if(alignment == LEFT)
			sout << left;
		sout << setw(length - OFFSET) << text;
	}
    	sout.flags(originalformat); //  reset flags
	sout.put(VERT);
	sout << endl;
}
