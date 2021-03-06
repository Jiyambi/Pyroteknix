// Pyroteknix
// Developed as coursework for Abertay University
// Based on framework by Dr. Henry Fortuna
// Copyright Sarah Herzog, 2013, all rights reserved.
//
// Text
//      Text that can be rendered to the screen
#ifndef __TEXT_H__
#define __TEXT_H__


// |----------------------------------------------------------------------------|
// |                                Includes                                    |
// |----------------------------------------------------------------------------|
#include <string>
#include <math.h>
#include "Util.h"
#include "GameObject.h"


// |----------------------------------------------------------------------------|
// |                           Class Definition: Text                           |
// |----------------------------------------------------------------------------|
class Text : public GameObject
{

public:
    
    //|-------------------------------Public Functions--------------------------|
    
	// Constructor
	Text();

    // Initialization
	bool virtual Initialize();
	
    // Sends any models associated with the object to the renderer
    bool virtual Render();
	
	// Setters
	void virtual SetFont(CFont* value) {m_font = value;}
	void virtual SetFont(std::string name) {m_font = AssetManager::GetSingleton().GetFont(name);}
	void virtual SetTexture(CTexture* value) {m_fontTexture = value;}
	void virtual SetTexture(std::string name) {m_fontTexture = AssetManager::GetSingleton().GetRedAlphaTexture(name);}
	void virtual SetString(std::string name) {m_string = name;}
	
	// Getters
	string virtual GetString() {return m_string;}
	
protected:
    
    //|---------------------------Protected Data Members-----------------------|
	
	// Text data
	std::string m_string;
	CFont* m_font;
	CTexture* m_fontTexture;

};

#endif