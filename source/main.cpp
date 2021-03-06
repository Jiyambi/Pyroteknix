/*
* "PS2" Application Framework
*
* University of Abertay Dundee
* May be used for educational purposed only
*
* Author - Dr Henry S Fortuna
*
* $Revision: 1.5 $
* $Date: 2007/08/27 20:22:34 $
*
*/

#include <sps2lib.h>
#include <sps2tags.h>
#include <sps2util.h>
#include <sps2regstructs.h>
#include <assert.h>
#include <memory.h>
#include <signal.h>
#include "PS2Defines.h"
#include "ps2maths.h"
#include "ps2matrix4x4.h"
#include "pad.h"
#include "sps2wrap.h"
#include "dma.h"
#include "texture.h"
#include "font.h"
#include "pipeline.h"
#include "entities.h"
#include "vumanager.h"
#include "timer.h"
#include "ms3dmodel.h"
#include "terrain.h"

// My includes
#include "AssetManager.h"
#include "GameObject.h"
#include "Image2D.h"
#include "Billboard.h"
#include "ParticleSystem.h"
#include "TitleScreen.h"
#include "GameManager.h"

/*
	Look at the start of the vcl code to get the positions
	and layout of the packet data in VU data memory.
	Remember that the data sent to the VU must be in 
	the specified format of the PS2 WILL CRASH

*/


// These two external function pointers are exported by the VU code
// and we can now use them as pointers to the compiled VU data
extern "C" uint64 VU_vu1code_start;
extern "C" uint64 VU_vu1code_end;


bool g_bLoop = true;

void sig_handle(int sig)
{
	g_bLoop = false;
}


int main(void)
{	
	// Make sure these four lines are put first since some of the 
	// other classes need the managers to be initialised so they 
	// can pick up the correct data.	
	SPS2Manager.Initialise(4096);	// 4096 * 4K Pages = 16MB Total
	VIFStaticDMA.Initialise(3072);	// 1536 * 4K Pages = 6MB Static DMA
	VIFDynamicDMA.Initialise(256);	// 256 * 4K Pages * 2 Buffers =
									// 2MB Dynamic DMA
	Pipeline.Initialise();			// Initialise graphics pipline class
	
	
	// Initialise Lighting
	// Three lights and Ambient light
	//							Direction vector				  Colour	
	Pipeline.SetLight1(Vector4( 0.0f, 0.5f, -1.0f, 0.0f),  Vector4( 0.0f, 0.0f, 128.0f, 0.0f));
	Pipeline.SetLight2(Vector4( 1.0f, -0.5f, -1.0f, 0.0f),  Vector4( 0.0f, 128.0f, 0.0f, 0.0f));
	Pipeline.SetLight3(Vector4( -1.0f, -0.5f, -1.0f, 0.0f), Vector4( 128.0f, 0.0f, 0.0f, 0.0f));
	//                            Colour
	Pipeline.SetAmbient(Vector4(50.0f,50.0f,50.0f,50.0f));
	
	// Terrain to render
	CTerrain Terrain;
	
	// Performance timer - call after SPS2Manager.Initialise()
	CTimer Timer;
	
	// Set up audio devices
	AudioDevice DSP0(0);
	// Set up music in sound buffer 0
	SoundSample music("go_cart", &DSP0);
	// Play the music!
	music.Play();
	
	// Initialise control pad 0
	if(!pad_init(PAD_0, PAD_INIT_LOCK | PAD_INIT_ANALOGUE | PAD_INIT_PRESSURE))
	{
		printf("Failed to initialise control pad\n");
		pad_cleanup(PAD_0);
		exit(0);
	}	
	enable_actuator(0, 1, 1);
	
	// Initialise the VU1 manager class
	CVU1MicroProgram VU1MicroCode(&VU_vu1code_start, &VU_vu1code_end);
	
	// Upload the microcode
	VU1MicroCode.Upload();

	// Register our signal function for every possible signal (i.e. ctrl + c)
	for(int sig=0; sig<128; sig++)
		signal(sig, sig_handle);
		
		
	// Set up the DMA packet to clear the screen. We want to clear to blue.
	SPS2Manager.InitScreenClear(0, 0x25, 0x50);
	
	// Set Up Camera --------------------------------------------------------------
	
	Pipeline.PositionCamera(Vector4(0.0f, 55.0f, 80.0f, 1.0f), Vector4(0.0f, 40.0f, 0.0f, 1.0f));
	
	// Load in texture and models ----------------------------------------------
	
	// Set up asset loader
	AssetManager assetManager;
	assetManager.Initialize();
	
	// Terrain texture
	CTexture* terrainTexture = assetManager.GetTexture("terrain");
	
	// Set up game manager
	GameManager* gameManager = new GameManager;
	gameManager->Initialize();
		
	// The main Render loop -------------------------------------------------------
	while(g_bLoop)
	{
		
		// Process Audio
		DSP0.HandleAudio();
		
		VIFDynamicDMA.Fire();
		
		// Update Control Pad
		pad_update(PAD_0);
		Pipeline.Update(0, 0, 0, 0, 0);
		
		// Logic
		g_bLoop = gameManager->Logic();
	
		// Render
		SPS2Manager.BeginScene();
		
		// Render terrain
		AssetManager::GetSingleton().LoadTexture(terrainTexture);
		Matrix4x4 matWorld, matTrans, matScale;
		matTrans.Translation(0.0f, -30.0f, 0.0f);
		matScale.Scaling(20.0f);
		matWorld =  matScale * matTrans;
		Terrain.SetWorldMatrix(matWorld);
		Terrain.Render();
		
		// Render scene
		gameManager->Render();
		SPS2Manager.EndScene();	
		
		// Dump screenshot if requested
		if(pad[0].pressed & PAD_R2)SPS2Manager.ScreenShot();		
	}

	// Shutdown Audio
	DSP0.Close();
	
	// Shutdown control pad
	set_actuator(0, 0, 0);
	pad_cleanup(PAD_0);
	
	// Shutdown game manager
	gameManager->Shutdown();
	
	// Shutdown asset manager
	assetManager.Shutdown();
	
	return 0;
}

