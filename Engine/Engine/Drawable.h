/**
Written by:  Smyth Chang
Description:  The Drawable class holds all of the information needed for the Graphics class to use
*/

#pragma once

#include <d3d9.h>
#include <d3dx9.h>
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

#include <string>

typedef D3DXVECTOR3 dVec3;
typedef D3DCOLOR dColor;

class Drawable
{
	//Transform vectors
	dVec3 scale;
	dVec3 translate;
	dVec3 rotate;

	//color
	dColor color;

	RECT rect;

	int height;
	int width;

	//mouse over
	bool isOn;
	//if the image is a spritesheet
	bool isSpritesheet;
	//if the object is 2D or 3D
	bool is3D;
	//draw the object
	bool draw;

	std::string handle;

public:
	Drawable();
	~Drawable();

	/**
	Name:			setIsOn
	Parameters:		bool a_isOn
	Return:			void
	Description:	Set the isOn boolean value.
	*/
	void setIsOn(bool a_isOn);

	/**
	Name:			getIsOn
	Parameters:		none
	Return:			bool
	Description:	Return isOn
	*/
	bool getIsOn();

	/**
	Name:			getTranslate
	Parameters:		none
	Return:			D3DXVECTOR3
	Description:	Returns the translate vector
	*/
	dVec3 getTranslate();

	/**
	Name:			getScale
	Parameters:		none
	Return:			D3DXVECTOR3
	Description:	Returns the Scale vector
	*/
	dVec3 getScale();

	/**
	Name:			getRotate
	Parameters:		none
	Return:			D3DXVECTOR3
	Description:	Returns the rotation vector
	*/
	dVec3 getRotate();
	
	/**
	Name:			setTranslate
	Parameters:		float x - the x position
					float y - the y position
					float z - the z position
	Return:			void
	Description:	Sets the translation vector.
	*/
	void setTranslate(float x, float y, float z);

	/**
	Name:			setScale
	Parameters:		float x - the x scale
					float y - the y scale
					float z - the z scale
	Return:			void
	Description:	Sets the scale vector.
	*/
	void setScale(float x, float y, float z);

	/**
	Name:			setRotate
	Parameters:		float x - the x rotation
					float y - the y rotation
					float z - the z rotation
	Return:			void
	Description:	Sets the translation vector.
	*/
	void setRotate(float x, float y, float z);

	/**
	Name:			setRect
	Parameters:		RECT r - the new RECT
	Return:			void
	Description:	Sets rect with the given rect
	*/
	void setRect(RECT r);

	/**
	name:			getRect
	parameters:		none
	Return:			RECT
	Description:	Returns the RECT
	*/
	RECT getRect();

	/**
	Name:			checkOn
	Parameters:		float x - the x position
					float y - the y position
					int scale - scale the object due
	Return:			bool
	Description:	Checks if the mouse position is on the drawable's position.
					For 2D objects.
	*/
	bool checkOn(float x, float y, int scale);

	/**
	Name:			setColor
	Parameters:		D3DCOLOR a_color - the new color
	Return:			void
	Description:	Sets the current color to the new color
	*/
	void setColor(dColor a_color);

	/**
	Name:			getColor
	Parameters:		none
	Return:			D3DCOLOR
	Description:	returns the current color
	*/
	dColor getColor();

	/**
	Name:			init
	Parameters:		none
	Return:			void
	Description:	Initializes the drawable object
	*/
	virtual void init();

	/**
	Name:			init
	Parameters:		D3DVECTOR3 translate
					D3DVECTOR3 scale
					D3DVECTOR3 rotate
					D3DCOLOR color
					RECT rect
					bool isSpriteSheet
					bool is3D
					bool draw
	Return:			void
	Description:	Initializes drawable with the given parameters.
	*/
	void init( dVec3 translate, dVec3 scale, dVec3 rotate, dColor color, RECT rect, bool isSpriteSheet, bool is3D, bool draw);

	/**
	Name:			update
	Parameters:		none
	Return:			void
	Description:	Update the drawable
	*/
	virtual void update();

	/**
	Name:			reset
	Parameters:		none
	Return:			void
	Description:	resets the members of drawable
	*/
	virtual void reset();

	/**
	Name:			getWidth
	Parameters:		none
	Return:			int
	Description:	returns the width
	*/

	int getWidth();

	/**
	Name:			getHeight
	Parameters:		none
	Return:			int
	Description:	returns the height
	*/

	int getHeight();

	/**
	name:			getIsSpriteSheet
	Parameters:		none
	Return:			bool
	Description:	returns the boolean isSpriteSheet
	*/
	bool getIsSpriteSheet();

	/**
	Name:			get3D
	Parameters:		none
	Return:			bool
	Description:	Returns the is3D boolean
	*/
	bool get3D();

	/**
	Name:			getDraw
	Parameters:		none
	Return:			bool
	Description:	Returns the boolean draw
	*/
	bool getDraw();

	/**
	Name:			setDraw
	Parameters:		bool arg
	Return:			void
	Description:	Sets the boolean draw
	*/
	void setDraw(bool arg);
	
	/**
	Name:			setHandle
	Parameters:		string
	Return;			void
	Description:	sets the handle
	*/
	void setHandle(std::string name);

	/**
	Name:			getHandle
	Parameters:		none
	Return:			string
	Description:	Returns the handle.
	*/
	std::string getHandle();

	void set3D(bool arg){ is3D = arg;}
};