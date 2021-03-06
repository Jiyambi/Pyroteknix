// Pyroteknix
// Developed as coursework for Abertay University
// Based on framework by Dr. Henry Fortuna
// Copyright Sarah Herzog, 2013, all rights reserved.
//
// Image2D
//      Contains model data for a 2D image, renders it to screen.
#ifndef __IMAGE2D_H__
#define __IMAGE2D_H__


// |----------------------------------------------------------------------------|
// |                                Includes                                    |
// |----------------------------------------------------------------------------|
#include <stdio.h>
#include <stdarg.h>
#include "Util.h"
#include "Coord.h"
#include "GameObject.h"


// |----------------------------------------------------------------------------|
// |                              Class: Image2D                                |
// |----------------------------------------------------------------------------|
class Image2D : public GameObject
{
public:

    //|-------------------------------Public Functions--------------------------|
	
	// Constructor
	Image2D();

	// Render Image2D to screen
	bool Render();
	
	// Getters
	int GetX() {return m_x;}
	int GetY() {return m_y;}
	uint32 GetWidth() {return m_width;}
	uint32 GetHeight() {return m_height;}
	uint32 GetDepth() {return m_depth;}
	uint8 GetTintR() {return m_r; }
	uint8 GetTintG() {return m_g; }
	uint8 GetTintB() {return m_b; }
	uint8 GetTintA() {return m_a; }
	
	// Setters
	void SetX(int val) {m_x = val;}
	void SetY(int val) {m_y = val;}
	void SetSize(uint32 w, uint32 h) {m_width = w; m_height = h;}
	void SetWidth(uint32 val) {m_width = val;}
	void SetHeight(uint32 val) {m_height = val;}
	void SetDepth(uint32 val) {m_depth = val;}
	void SetTint(uint8 r,uint8 g,uint8 b,uint8 a) {m_r = r; m_g = g; m_b = b; m_a = a; }
	void SetTintR(uint8 val) {m_r = val;}
	void SetTintG(uint8 val) {m_g = val;}
	void SetTintB(uint8 val) {m_b = val;}
	void SetTintA(uint8 val) {m_a = val;}
	
	void virtual SetTexture(std::string name) {m_texture = AssetManager::GetSingleton().GetRedAlphaTexture(name);}
	void virtual SetTexture(CTexture* val) {m_texture = val;}

private:

    //|-----------------------------Private Data Members------------------------|
	
	// Positioning
	int m_x;
	int m_y;
	uint32 m_width;
	uint32 m_height;
	uint32 m_depth;
	
	// Color / aplha
	uint8 m_r;
	uint8 m_b;
	uint8 m_g;
	uint8 m_a;
	
};

#endif