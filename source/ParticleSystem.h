// Pyroteknix
// Developed as coursework for Abertay University
// Based on framework by Dr. Henry Fortuna
// Copyright Sarah Herzog, 2013, all rights reserved.
//
// ParticleSystem
//      Manages a set of particles, emitted and handled based on set parameters
#ifndef __PARTICLESYSTEM_H__
#define __PARTICLESYSTEM_H__


// |----------------------------------------------------------------------------|
// |                                Includes                                    |
// |----------------------------------------------------------------------------|
#include <list>
#include "Util.h"
#include "Billboard.h"


// |----------------------------------------------------------------------------|
// |                     Class Definition: ParticleSystem                       |
// |----------------------------------------------------------------------------|
class ParticleSystem : public Billboard {

public:

    //|-------------------------------Public TypeDefs---------------------------|

    struct ParticleType
	{
		Coord position;
		float red, green, blue, alpha;
        float lifetime;
        float maxLife;
		Coord velocity;

        bool operator<(const ParticleType& rhs);
	};

public:
    
    //|-------------------------------Public Functions--------------------------|
    
	// Constructors and Destructors
	ParticleSystem();
	ParticleSystem(const ParticleSystem&);
	virtual ~ParticleSystem();

    // Initialization and shutdown
	virtual bool  Initialize();
	virtual bool  Shutdown();
    
    // Performs logic functions for the object
    virtual bool  Logic();
    
    // Renders camera
    bool virtual Render();

    // Setters
    void SetParticleDeviation(Coord particleDeviation) { m_particleDeviation = particleDeviation; }
    void SetParticleVelocity(Coord particleVelocity) { m_particleVelocity = particleVelocity; }
    void SetParticleVelocityVariation(Coord particleVelocityVariation) { m_particleVelocityVariation = particleVelocityVariation; }
    void SetParticleSize(float particleSize) { m_particleSize = particleSize; }
    void SetParticleSpawnFrequency(float particleSpawnFrequency) { m_particleSpawnFrequency = particleSpawnFrequency; }
    void SetParticleLifetime(float particleLifetime) { m_particleLifetime = particleLifetime; }
    void SetParticleFadeout(float particleFadeout) { m_particleFadeout = particleFadeout; }
    void SetMaxParticles(int maxParticles) { m_maxParticles = maxParticles; }
	void SetSpawnParticles(bool val) {m_spawnParticles = val;}
    
	void virtual SetTexture(std::string name) {m_texture = AssetManager::GetSingleton().GetRedAlphaTexture(name);}
	
    void SetTint(float r, float g, float b, float a = 1.0f) {
        m_tintR = r;
        m_tintG = g;
        m_tintB = b;
        m_alpha = a;
    }
    void SetTintVar(float r, float g, float b, float a = 1.0f) {
        m_tintRVar = r;
        m_tintGVar = g;
        m_tintBVar = b;
        m_alphaVar = a;
    }

protected:
   
    //|----------------------------Protected Functions-------------------------|

	void EmitParticles();
	void UpdateParticles();
	void KillParticles();

protected:
    
    //|---------------------------Protected Data Members-----------------------|

    // Particle system parameters
    float m_tintR, m_tintG, m_tintB, m_alpha;
    float m_tintRVar, m_tintGVar, m_tintBVar, m_alphaVar;
    Coord m_particleDeviation;
    Coord m_particleVelocity;
    Coord m_particleVelocityVariation;
    float m_particleSize;
    float m_particleSpawnFrequency;
    float m_particleFadeout;
    float m_particleLifetime;
    int m_maxParticles;

    // Particle management data members
	bool m_spawnParticles;
    float m_accumulatedTime;
	float m_frameTime;
	CTimer m_timer;
    std::list<ParticleType> m_particles;
};

#endif