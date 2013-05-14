// Pyroteknix
// Developed as coursework for Abertay University
// Based on framework by Dr. Henry Fortuna
// Copyright Sarah Herzog, 2013, all rights reserved.
//
// Firework
//      Controls everything relating to a Firework, including particle system for 
//		trail, explosion, trajectory, and lighting
#pragma once


// |----------------------------------------------------------------------------|
// |                                Includes                                    |
// |----------------------------------------------------------------------------|
#include <list>
#include <math.h>
#include "Util.h"
#include "GameObject.h"
#include "FireworkEffect.h"
#include "ParticleSystem.h"


// |----------------------------------------------------------------------------|
// |                        Class Definition: Firework                          |
// |----------------------------------------------------------------------------|
class Firework : public GameObject {


public:
    
    //|-------------------------------Public Functions--------------------------|
    
	// Constructors and Destructors
	Firework();
	Firework(const Firework&);
	virtual ~Firework();

    // Initialization and shutdown
	virtual bool  Initialize();
	virtual bool  Shutdown();
    
    // Performs logic functions for the object
    virtual bool  Logic();
    
    // Renders camera
    bool virtual Render();
	
	// Setters
	void virtual SetTexture(std::string name) {m_texture = AssetManager::GetSingleton().GetRedAlphaTexture(name);}
	void virtual SetTarget(Coord val);
	
	// Firework
	void Explode();

protected:
    
    //|---------------------------Protected Data Members-----------------------|

    // Firework parameters
	FireworkEffect* m_explosion;
	ParticleSystem* m_trail;
	Coord m_target;
	float m_speed;
	bool m_hasExploded;
};