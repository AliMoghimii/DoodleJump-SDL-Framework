#include "stdafx.h"
#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include <ctime>
//#include <SDL_mixer.h>
#include "hash.h"
#undef main
using namespace std;

SDL_Surface*screen;
//---------------State Variables

int GameState = 0;
int SoundState = 1;
int	MusicState = 1;
int DoodleState = 0;
int FakeState = 0;
int PicSetMusic = 1;
int PicSetSound = 1;
int ThemeState = 0;

//----------------Player Variables

int PlayerX = 100;
int PlayerY = 250;
int PlayerXM = 100;
int PlayerYM = 250;
int RandomY;
int RandomX;
int FirstPlatX = 100;
int FirstPlatY = 500;
double Vy = -1; //Velocity of The Player
double VyM = -6; //Velocity of The Player (in menu)
int Vp = 15; //Velocity of The Platforms
double Xsub = 200;
double Xsp = 400;
double Xf = 300;
double VballY = -50;
double Gy = 1; //Acceleration of the Player

//----------------Structs

struct Platform {

	int GreenX;
	int GreenY;
	int BlueX, BlueVx;
	int BlueY;
	int DarkBlueX;
	int DarkBlueY, DarkBlueVy;
	int FakeX;
	int FakeY;
	int HoleX;
	int HoleY;
	bool showing = false;
}PL;


//SDL_BlitSurface(back_ground, screen, 10,20);//ADDS A 10*20 IMAGE TO THE BACKGROUND
//-------------------------------------------------------Character and Enemies
SDL_Surface*BackG = ImgLoader("images/bck_X.png", 0, 0, 255);
SDL_Surface*BackGjungle = ImgLoader("images/junglebck_X.png", 0, 0, 255);
SDL_Surface*DecorJungle1 = ImgLoader("images/jungledecor.png", 0, 0, 255);
SDL_Surface*DecorJungle2 = ImgLoader("images/jungledecor2.png", 0, 0, 255);
SDL_Surface*BackGunderw = ImgLoader("images/underwaterbck_X.png", 0, 0, 255);
SDL_Surface*DecorUnderW = ImgLoader("images/underwaterdecor.png", 0, 0, 255);
SDL_Surface*Submarine = ImgLoader("images/Submarine.png", 0, 0, 255);
SDL_Surface*Fish = ImgLoader("images/Fish.png", 0, 0, 255);
SDL_Surface*SharkPack = ImgLoader("images/SharkPack.png", 0, 0, 255);
SDL_Surface*BackGice = ImgLoader("images/icebck_X.png", 0, 0, 255);
SDL_Surface*DecorIce = ImgLoader("images/icedecor.png", 0, 0, 255);
SDL_Surface*BackGspace = ImgLoader("images/spacebck_X.png", 0, 0, 255);
SDL_Surface*DecorSpace = ImgLoader("images/spacedecor.png", 0, 0, 255);
SDL_Surface*BackGeaster = ImgLoader("images/hopbck_X.png", 0, 0, 255);
SDL_Surface*DecorEaster = ImgLoader("images/hopbottom_X.png", 0, 0, 255);
SDL_Surface*BackGhalloween = ImgLoader("images/ghostbck_X.png", 0, 0, 255);
SDL_Surface*DecorHalloween = ImgLoader("images/ghostland_X.png", 0, 0, 255);
SDL_Surface*Moon = ImgLoader("images/ghostmoon_X.png", 0, 0, 255);
SDL_Surface*BackGchristmas = ImgLoader("images/snowbck_X.png", 0, 0, 255);
SDL_Surface*DecorChristmas = ImgLoader("images/snowbottom_X.png", 0, 0, 255);
SDL_Surface*DecorPirate = ImgLoader("images/DecorPirate.png", 0, 0, 255);
SDL_Surface*PlayerR = ImgLoader("images/likright_X.png", 0, 0, 255);
SDL_Surface*PlayerL = ImgLoader("images/likleft_X.png", 0, 0, 255);
SDL_Surface*PlayerRJ = ImgLoader("images/jungleright_X.png", 0, 0, 255);
SDL_Surface*PlayerLJ = ImgLoader("images/jungleleft_X.png", 0, 0, 255);
SDL_Surface*PlayerRU = ImgLoader("images/underwaterright_X.png", 0, 0, 255);
SDL_Surface*PlayerLU = ImgLoader("images/underwaterleft_X.png", 0, 0, 255);
SDL_Surface*PlayerRI = ImgLoader("images/iceright_X.png", 0, 0, 255);
SDL_Surface*PlayerLI = ImgLoader("images/iceleft_X.png", 0, 0, 255);
SDL_Surface*PlayerRS = ImgLoader("images/spaceright_X.png", 0, 0, 255);
SDL_Surface*PlayerLS = ImgLoader("images/spaceleft_X.png", 0, 0, 255);
SDL_Surface*PlayerRE = ImgLoader("images/bunnyright_X.png", 0, 0, 255);
SDL_Surface*PlayerLE = ImgLoader("images/bunnyleft_X.png", 0, 0, 255);
SDL_Surface*PlayerRH = ImgLoader("images/ghostright_X.png", 0, 0, 255);
SDL_Surface*PlayerLH = ImgLoader("images/ghostleft_X.png", 0, 0, 255);
SDL_Surface*PlayerRC = ImgLoader("images/snowright_X.png", 0, 0, 255);
SDL_Surface*PlayerLC = ImgLoader("images/snowleft_X.png", 0, 0, 255);
SDL_Surface*PlayerRP = ImgLoader("images/pirates-captain-right_X.png", 0, 0, 255);
SDL_Surface*PlayerLP = ImgLoader("images/pirates-captain-left_X.png", 0, 0, 255);
//SDL_Surface*PlayerRH1 = ImgLoader("images/likrightHAT1.png", 0, 0, 255);
//SDL_Surface*PlayerRH2 = ImgLoader("images/likrightHAT2.png", 0, 0, 255);
//SDL_Surface*PlayerRH3 = ImgLoader("images/likrightHAT3.png", 0, 0, 255);
//SDL_Surface*Ball = ImgLoader("images/Ball.png", 0, 0, 255);
SDL_Surface*Greenplat = ImgLoader("images/normal platform.png", 0, 0, 255);
SDL_Surface*Blueplat = ImgLoader("images/right left moving paltform.png", 0, 0, 255);
SDL_Surface*DarkBlueplat = ImgLoader("images/up down moving platform.png", 0, 0, 255);
SDL_Surface*Fakeplat1 = ImgLoader("images/fake platform f1.png", 0, 0, 255);
SDL_Surface*Fakeplat2 = ImgLoader("images/fake platform f2.png", 0, 0, 255);
SDL_Surface*Fakeplat3 = ImgLoader("images/fake platform f3.png", 0, 0, 255);
SDL_Surface*Fakeplat4 = ImgLoader("images/fake platform f4.png", 0, 0, 255);
SDL_Surface*Hole = ImgLoader("images/hole_X.png", 0, 0, 255);
SDL_Surface*HoleL = ImgLoader("images/hole_L.png", 0, 0, 255);
SDL_Surface*UFO2rot = ImgLoader("images/ufo_f2rot.png", 0, 0, 255);
SDL_Surface*UFO2rotWL = ImgLoader("images/ufo_f2rotWITHOUTLIGHT.png", 0, 0, 255);
SDL_Surface*monster11 = ImgLoader("images/monster five f1.png", 0, 0, 255);
SDL_Surface*monster12 = ImgLoader("images/monster five f2.png", 0, 0, 255);
SDL_Surface*monster13 = ImgLoader("images/monster five f3.png", 0, 0, 255);
SDL_Surface*monster14 = ImgLoader("images/monster five f4.png", 0, 0, 255);
SDL_Surface*monster15 = ImgLoader("images/monster five f5.png", 0, 0, 255);
SDL_Surface*monster21 = ImgLoader("images/monster one f1.png", 0, 0, 255);
SDL_Surface*monster22 = ImgLoader("images/monster one f2.png", 0, 0, 255);
SDL_Surface*monster23 = ImgLoader("images/monster one f3.png", 0, 0, 255);
SDL_Surface*monster31 = ImgLoader("images/monster two f1.png", 0, 0, 255);
SDL_Surface*monster32 = ImgLoader("images/monster two f2.png", 0, 0, 255);
SDL_Surface*Spring = ImgLoader("images/spring f1.png", 0, 0, 255);
//-------------------------------------------------------Buttons and function
SDL_Surface*Logo = ImgLoader("images/logo.png", 0, 0, 255);
SDL_Surface*PlayB = ImgLoader("images/play_X.png", 0, 0, 255);
SDL_Surface*PlayOnB = ImgLoader("images/playon_X.png", 0, 0, 255);
SDL_Surface*OptionB = ImgLoader("images/options_X.png", 0, 0, 255);
SDL_Surface*MenuB = ImgLoader("images/menu_X.png", 0, 0, 255);
SDL_Surface*MenuOnB = ImgLoader("images/menuon_X.png", 0, 0, 255);
SDL_Surface*CreditB = ImgLoader("images/Credits.png", 0, 0, 255);
SDL_Surface*CreditOnB = ImgLoader("images/CreditsOn.png", 0, 0, 255);
SDL_Surface*ResumeB = ImgLoader("images/resume_X.png", 0, 0, 255);
SDL_Surface*ResumeOnB = ImgLoader("images/resumeon_X.png", 0, 0, 255);
SDL_Surface*PlayAgainB = ImgLoader("images/playagain_X.png", 0, 0, 255);
SDL_Surface*PlayAgainOnB = ImgLoader("images/playagainon_X.png", 0, 0, 255);
//-------------------------------------------------------Texts and Logo's
SDL_Surface*PauseText = ImgLoader("images/Pause.png", 0, 0, 255);
SDL_Surface*CreditsText = ImgLoader("images/Creditstext.png", 0, 0, 255);
SDL_Surface*CreditsLogo = ImgLoader("images/CreditsLogo.png", 0, 0, 255);
SDL_Surface*Pointer = ImgLoader("images/Mouse.png", 0, 0, 255);
SDL_Surface*OptionLogo = ImgLoader("images/options.png", 0, 0, 255);
SDL_Surface*MusicLogo = ImgLoader("images/music.png", 0, 0, 255);
SDL_Surface*SoundLogo = ImgLoader("images/sound.png", 0, 0, 255);
SDL_Surface*OnLogoGreen = ImgLoader("images/ONGN.png", 0, 0, 255);
SDL_Surface*OffLogoGreen = ImgLoader("images/OFFGN.png", 0, 0, 255);
SDL_Surface*OnLogoGrey = ImgLoader("images/ONGY.png", 0, 0, 255);
SDL_Surface*OffLogoGrey = ImgLoader("images/OFFGY.png", 0, 0, 255);
SDL_Surface*OptionsDoodle = ImgLoader("images/options_doodle.png", 0, 0, 255);
SDL_Surface*GameOverLogo = ImgLoader("images/GameOver.png", 0, 0, 255);
SDL_Surface*Bug1 = ImgLoader("images/bottombugtiles_L2.png", 0, 0, 255);
SDL_Surface*Bug2 = ImgLoader("images/bottombugtiles_L3.png", 0, 0, 255);
SDL_Surface*Bug3 = ImgLoader("images/bottombugtiles_L4.png", 0, 0, 255);
SDL_Surface*Bug4 = ImgLoader("images/bottombugtiles_L5.png", 0, 0, 255);
SDL_Surface*Bug5 = ImgLoader("images/bottombugtiles_L6.png", 0, 0, 255);


//Sound //TWO SOUNDS PLAY AT THE SAME TIME //Sound*shotSound=LoadSound(//adress) //LOAD 

//Mix_Chunk*Jump = Mix_LoadWAV("sounds/jump.wav");
Sound*Jump = LoadSound("sounds/jump.ogg");
Music*BgMusic = LoadMusic("sounds/Sonic_Runners_End_of_Summer.ogg");


//----------------------------------------------------------------------------------------------------------------------------------------Collision Detect Function

bool CollisionDetection(int X0, int Y0, int DoodleX, int DoodleY, int V) {
	if (DoodleX + 80 >= X0 && DoodleX <= X0 + 80 && DoodleY + 100 >= Y0 && DoodleY + 100 <= Y0 + 25 && V > 0)
	{
		PlaySound(Jump, 2);
		return true;
	}
	else
		return false;
}
//----------------------------------------------------------------------------------------------------------------------------------------Collision Detect Function for Hole

bool CollisionDetectionHole(int X0, int Y0, int DoodleX, int DoodleY, int V) {
	if (DoodleX + 90 >= X0 && DoodleX <= X0 + 90 && DoodleY + 90 >= Y0 && DoodleY + 90 <= Y0 + 90 && V >= 0 || DoodleX + 80 >= X0 && DoodleX <= X0 + 90 && DoodleY + 90 >= Y0 && DoodleY + 90 <= Y0 + 144 && V <= 0)
	{
		return true;
	}
	else
		return false;
}
//----------------------------------------------------------------------------------------------------------------------------------------Starter Platform
void FirstPlat()
{
	SDL_BlitSurface(Greenplat, screen, FirstPlatX, FirstPlatY);
}
//----------------------------------------------------------------------------------------------------------------------------------------Generate Random Wallpapers and etc ...

void GenerateW()
{
	int RandomBG = rand() % 9;
	if (RandomBG == 0)
		ThemeState = 0;
	if (RandomBG == 1)
		ThemeState = 1;
	if (RandomBG == 2)
		ThemeState = 2;
	if (RandomBG == 3)
		ThemeState = 3;
	if (RandomBG == 4)
		ThemeState = 4;
	if (RandomBG == 5)
		ThemeState = 5;
	if (RandomBG == 6)
		ThemeState = 6;
	if (RandomBG == 7)
		ThemeState = 7;
	if (RandomBG == 8)
		ThemeState = 8;
}
void DoodlePic()
{
	if (ThemeState == 0)
	{
		if (DoodleState == 1) //related to the DoodleXMovement() function
		{
			SDL_BlitSurface(PlayerR, screen, PlayerX, PlayerY);
		}
		if (DoodleState == 2)
			SDL_BlitSurface(PlayerL, screen, PlayerX, PlayerY);
		else
			SDL_BlitSurface(PlayerR, screen, PlayerX, PlayerY);
	}
	if (ThemeState == 1)
	{
		if (DoodleState == 1) //related to the DoodleXMovement() function
		{
			SDL_BlitSurface(PlayerRJ, screen, PlayerX, PlayerY);
		}
		if (DoodleState == 2)
			SDL_BlitSurface(PlayerLJ, screen, PlayerX, PlayerY);
		else
			SDL_BlitSurface(PlayerRJ, screen, PlayerX, PlayerY);
	}
	if (ThemeState == 2)
	{
		if (DoodleState == 1) //related to the DoodleXMovement() function
		{
			SDL_BlitSurface(PlayerRU, screen, PlayerX, PlayerY);
		}
		if (DoodleState == 2)
			SDL_BlitSurface(PlayerLU, screen, PlayerX, PlayerY);
		else
			SDL_BlitSurface(PlayerRU, screen, PlayerX, PlayerY);
	}
	if (ThemeState == 3)
	{
		if (DoodleState == 1) //related to the DoodleXMovement() function
		{
			SDL_BlitSurface(PlayerRI, screen, PlayerX, PlayerY);
		}
		if (DoodleState == 2)
			SDL_BlitSurface(PlayerLI, screen, PlayerX, PlayerY);
		else
			SDL_BlitSurface(PlayerRI, screen, PlayerX, PlayerY);
	}
	if (ThemeState == 4)
	{
		if (DoodleState == 1) //related to the DoodleXMovement() function
		{
			SDL_BlitSurface(PlayerRS, screen, PlayerX, PlayerY);
		}
		if (DoodleState == 2)
			SDL_BlitSurface(PlayerLS, screen, PlayerX, PlayerY);
		else
			SDL_BlitSurface(PlayerRS, screen, PlayerX, PlayerY);
	}
	if (ThemeState == 5)
	{
		if (DoodleState == 1) //related to the DoodleXMovement() function
		{
			SDL_BlitSurface(PlayerRE, screen, PlayerX, PlayerY);
		}
		if (DoodleState == 2)
			SDL_BlitSurface(PlayerLE, screen, PlayerX, PlayerY);
		else
			SDL_BlitSurface(PlayerRE, screen, PlayerX, PlayerY);
	}
	if (ThemeState == 6)
	{
		if (DoodleState == 1) //related to the DoodleXMovement() function
		{
			SDL_BlitSurface(PlayerRH, screen, PlayerX, PlayerY);
		}
		if (DoodleState == 2)
			SDL_BlitSurface(PlayerLH, screen, PlayerX, PlayerY);
		else
			SDL_BlitSurface(PlayerRH, screen, PlayerX, PlayerY);
	}
	if (ThemeState == 7)
	{
		if (DoodleState == 1) //related to the DoodleXMovement() function
		{
			SDL_BlitSurface(PlayerRC, screen, PlayerX, PlayerY);
		}
		if (DoodleState == 2)
			SDL_BlitSurface(PlayerLC, screen, PlayerX, PlayerY);
		else
			SDL_BlitSurface(PlayerRC, screen, PlayerX, PlayerY);
	}
	if (ThemeState == 8)
	{
		if (DoodleState == 1) //related to the DoodleXMovement() function
		{
			SDL_BlitSurface(PlayerRP, screen, PlayerX, PlayerY);
		}
		if (DoodleState == 2)
			SDL_BlitSurface(PlayerLP, screen, PlayerX, PlayerY);
		else
			SDL_BlitSurface(PlayerRP, screen, PlayerX, PlayerY);
	}
}
void WallpaperStateFunc()
{
	if (ThemeState == 0)
		SDL_BlitSurface(BackG, screen, 0, 0);
	DoodlePic();
	if (ThemeState == 1)
	{
		SDL_BlitSurface(BackGjungle, screen, 0, 0);
		SDL_BlitSurface(DecorJungle1, screen, 0, 0);
		SDL_BlitSurface(DecorJungle2, screen, 0, 734);
		DoodlePic();
	}
	if (ThemeState == 2)
	{
		SDL_BlitSurface(BackGunderw, screen, 0, 0);
		SDL_BlitSurface(DecorUnderW, screen, 0, 756);
		SDL_BlitSurface(Submarine, screen, Xsub, 100);
		SDL_BlitSurface(SharkPack, screen, Xsp, 300);
		SDL_BlitSurface(Fish, screen, Xf, 700);
		DoodlePic();
	}
	if (ThemeState == 3)
	{
		SDL_BlitSurface(BackGice, screen, 0, 0);
		SDL_BlitSurface(DecorIce, screen, 0, 0);
		DoodlePic();
	}
	if (ThemeState == 4)
	{
		SDL_BlitSurface(BackGspace, screen, 0, 0);
		SDL_BlitSurface(DecorSpace, screen, 0, 0);
		DoodlePic();
	}
	if (ThemeState == 5)
	{
		SDL_BlitSurface(BackGeaster, screen, 0, 0);
		SDL_BlitSurface(DecorEaster, screen, 0, 780);
		DoodlePic();
	}
	if (ThemeState == 6)
	{
		SDL_BlitSurface(BackGhalloween, screen, 0, 0);
		SDL_BlitSurface(DecorHalloween, screen, 0, 632);
		SDL_BlitSurface(Moon, screen, 500, 100);
		DoodlePic();
	}
	if (ThemeState == 7)
	{
		SDL_BlitSurface(BackGchristmas, screen, 0, 0);
		SDL_BlitSurface(DecorChristmas, screen, 0, 652);
		DoodlePic();
	}
	if (ThemeState == 8)
	{
		SDL_BlitSurface(BackGeaster, screen, 0, 0);
		SDL_BlitSurface(DecorPirate, screen, 0, 0);
		DoodlePic();
	}

}
//----------------------------------------------------------------------------------------------------------------------------------------Generate Random Platforms (Green)

Platform* PlatformPositionGreen = new Platform[7];

void GeneratePG()
{
	for (int i = 0; i < 5; i++)
		if (!(PlatformPositionGreen[i].showing))
		{
			PlatformPositionGreen[i].GreenX = rand() % 500;
			PlatformPositionGreen[i].GreenY = rand() % 700;
			PlatformPositionGreen[i].showing = true;
		}

}

void GeneratePG0()
{
	for (int i = 0; i < 5; i++)
		if (!(PlatformPositionGreen[i].showing))
		{
			PlatformPositionGreen[i].GreenX = rand() % 500;
			PlatformPositionGreen[i].GreenY = -20;
			PlatformPositionGreen[i].showing = true;
		}

}

//----------------------------------------------------------------------------------------------------------------------------------------Show Platforms (Green)

void ShowPG()
{
	for (int i = 0; i <= 5; i++)
		if (PlatformPositionGreen[i].showing)
			SDL_BlitSurface(Greenplat, screen, PlatformPositionGreen[i].GreenX, PlatformPositionGreen[i].GreenY);
}

//----------------------------------------------------------------------------------------------------------------------------------------Generate Random Platforms (Blue)

Platform* PlatformPositionBlue = new Platform[1];

void GeneratePB()
{
	for (int i = 0; i < 1; i++)
		if (!(PlatformPositionBlue[i].showing))
		{
			PlatformPositionBlue[i].BlueX = rand() % 500;
			PlatformPositionBlue[i].BlueY = rand() % 700;
			PlatformPositionBlue[i].showing = true;
		}

}
void GeneratePB0()
{
	for (int i = 0; i < 1; i++)
		if (!(PlatformPositionBlue[i].showing))
		{
			PlatformPositionBlue[i].BlueX = rand() % 500;
			PlatformPositionBlue[i].BlueY = -30;
			PlatformPositionBlue[i].showing = true;
		}

}

//----------------------------------------------------------------------------------------------------------------------------------------Platform Movement X Axis (Blue)

void MovementBlue()
{
	static int counterB = 0;
	if (counterB > 60) {
		PlatformPositionBlue[0].BlueVx *= -1;
		counterB = 0;

	}
	PlatformPositionBlue[0].BlueX += PlatformPositionBlue[0].BlueVx;
	counterB++;
}

//----------------------------------------------------------------------------------------------------------------------------------------Show Platforms (Blue)

void ShowPB()
{
	MovementBlue();
	for (int i = 0; i <= 1; i++)
		if (PlatformPositionBlue[i].showing)
			SDL_BlitSurface(Blueplat, screen, PlatformPositionBlue[i].BlueX, PlatformPositionBlue[i].BlueY);
}

//----------------------------------------------------------------------------------------------------------------------------------------Generate Random Platforms (Dark Blue)

/*Platform* PlatformPositionDarkBlue = new Platform[1];

void GeneratePDB()
{
	for (int i = 0; i < 1; i++)
		if (!(PlatformPositionDarkBlue[i].showing))
		{
			PlatformPositionDarkBlue[i].DarkBlueX = rand() % 500;
			PlatformPositionDarkBlue[i].DarkBlueY = rand() % 700;
			PlatformPositionDarkBlue[i].showing = true;
		}

}
void GeneratePDB0()
{
	for (int i = 0; i < 1; i++)
		if (!(PlatformPositionDarkBlue[i].showing))
		{
			PlatformPositionDarkBlue[i].DarkBlueX = rand() % 500;
			PlatformPositionDarkBlue[i].DarkBlueY = -30;
			PlatformPositionDarkBlue[i].showing = true;
		}

}*/

//----------------------------------------------------------------------------------------------------------------------------------------Platform Movement Y Axis (Dark Blue)

/*void MovementDarkBlue()
{
	static int counterDB = 0;
	if (counterDB > 60)
	{
		PlatformPositionDarkBlue[0].DarkBlueVy *= -1;
		counterDB = 0;

	}
	PlatformPositionDarkBlue[0].DarkBlueY += PlatformPositionDarkBlue[0].DarkBlueVy;
	counterDB++;
}*/

//----------------------------------------------------------------------------------------------------------------------------------------Show Platforms (Dark Blue)

/*void ShowPDB()
{
	MovementDarkBlue();
	for (int i = 0; i <= 1; i++) {
		if (PlatformPositionDarkBlue[i].showing)
			SDL_BlitSurface(DarkBlueplat, screen, PlatformPositionDarkBlue[i].DarkBlueX, PlatformPositionDarkBlue[i].DarkBlueY);
	}
}*/

//----------------------------------------------------------------------------------------------------------------------------------------Generate Random Platforms (Fake)

Platform* PlatformPositionFake = new Platform[1];

void GeneratePF()
{
	for (int i = 0; i < 1; i++)
		if (!(PlatformPositionFake[i].showing))
		{
			PlatformPositionFake[i].FakeX = rand() % 500;
			PlatformPositionFake[i].FakeY = rand() % 700;
			PlatformPositionFake[i].showing = true;
		}

}
void GeneratePF0()
{
	for (int i = 0; i < 1; i++)
		if (!(PlatformPositionFake[i].showing))
		{
			PlatformPositionFake[i].FakeX = rand() % 500;
			PlatformPositionFake[i].FakeY = -30;
			PlatformPositionFake[i].showing = true;
		}

}

//----------------------------------------------------------------------------------------------------------------------------------------Show Platforms (Fake)

void ShowPF()
{
	for (int i = 0; i <= 1; i++)
		if (PlatformPositionBlue[i].showing)
			SDL_BlitSurface(Fakeplat1, screen, PlatformPositionFake[i].FakeX, PlatformPositionFake[i].FakeY);
}

//----------------------------------------------------------------------------------------------------------------------------------------Generate Random Holes

Platform* HolePosition = new Platform[1];

void GenerateH()
{
	for (int i = 0; i < 1; i++)
		if (!(HolePosition[i].showing))
		{
			HolePosition[i].HoleX = rand() % 500;
			HolePosition[i].HoleY = rand() % 700;
			HolePosition[i].showing = true;
		}

}
void GenerateH0()
{
	for (int i = 0; i < 1; i++)
		if (!(HolePosition[i].showing))
		{
			HolePosition[i].HoleX = rand() % 500;
			HolePosition[i].HoleY = -30;
			HolePosition[i].showing = true;
		}

}

//----------------------------------------------------------------------------------------------------------------------------------------Show Platforms (Fake)

void ShowH()
{
	for (int i = 0; i <= 1; i++)
		if (HolePosition[i].showing)
			SDL_BlitSurface(HoleL, screen, HolePosition[i].HoleX, HolePosition[i].HoleY);
}

//----------------------------------------------------------------------------------------------------------------------------------------Hat Physics

/*void Hat() {
if(//moktasat = hat)
static int i = 0;
if (i % 3 == 0)
SDL_BlitSurface(PlayerRH1, screen, 100, 100);
if (i % 3 == 1)
SDL_BlitSurface(PlayerRH1, screen, 100, 100);
if (i % 3 == 2)
SDL_BlitSurface(PlayerRH1, screen, 100, 100);
i++;
SDL_Delay(3);*/

//----------------------------------------------------------------------------------------------------------------------------------------Beaking Platform Animaion 
void FakePlat() {

	static int i = 0;
	if (FakeState == 0) {
		if (i % 5 == 0)
			SDL_BlitSurface(Fakeplat2, screen, PlatformPositionFake[i].FakeX, PlatformPositionFake[i].FakeY);
		if (i % 5 == 1)
			SDL_BlitSurface(Fakeplat3, screen, PlatformPositionFake[i].FakeX, PlatformPositionFake[i].FakeY);
		if (i % 5 == 2)
			SDL_BlitSurface(Fakeplat4, screen, PlatformPositionFake[i].FakeX, PlatformPositionFake[i].FakeY);
		i++;
		SDL_Delay(3);
	}
}

//----------------------------------------------------------------------------------------------------------------------------------------UFO 1 Animation

void UFO1() {
	static int i = 0;
	if (i % 2 == 0)
		SDL_BlitSurface(UFO2rot, screen, 470, 60);
	if (i % 2 == 1)
		SDL_BlitSurface(UFO2rotWL, screen, 470, 60);
	i++;
	SDL_Delay(3);
}

//----------------------------------------------------------------------------------------------------------------------------------------Monster 1 Animation

void Monster1() {
	static int i = 0;
	if (i % 5 == 0)
		SDL_BlitSurface(monster11, screen, 50, 250);
	if (i % 5 == 1)
		SDL_BlitSurface(monster12, screen, 50, 250);
	if (i % 5 == 2)
		SDL_BlitSurface(monster13, screen, 50, 250);
	if (i % 5 == 3)
		SDL_BlitSurface(monster14, screen, 50, 250);
	if (i % 5 == 4)
		SDL_BlitSurface(monster15, screen, 50, 250);
	i++;
	SDL_Delay(3);
}

//----------------------------------------------------------------------------------------------------------------------------------------Monster 2 Animation

void Monster2() {
	static int i = 0;
	if (i % 3 == 0)
		SDL_BlitSurface(monster21, screen, 10, 650);
	if (i % 3 == 1)
		SDL_BlitSurface(monster22, screen, 10, 650);
	if (i % 3 == 2)
		SDL_BlitSurface(monster23, screen, 10, 650);
	i++;
	SDL_Delay(3);
}

//----------------------------------------------------------------------------------------------------------------------------------------Monster 3 Animation

int Monster3X = 320;
int Monster3State = 0;
int Monster3V = 7;
void Monster3() {

	if (Monster3X + 75 >= 490)
	{
		Monster3V = -7;
		Monster3State = 2;
	}
	if (Monster3X <= 150)
	{
		Monster3V = 7;
		Monster3State = 1;
	}

}

//----------------------------------------------------------------------------------------------------------------------------------------On and Off pic Switch Music / Sound

void OnSwitchMusic(int OnX, int OnY)
{
	if (PicSetMusic == 1)
		SDL_BlitSurface(OnLogoGreen, screen, OnX, OnY);
	if (PicSetMusic == 0)
		SDL_BlitSurface(OnLogoGrey, screen, OnX, OnY);
}
void OffSwitchMusic(int OffX, int OffY)
{
	if (PicSetMusic == 1)
		SDL_BlitSurface(OffLogoGrey, screen, OffX, OffY);
	if (PicSetMusic == 0)
		SDL_BlitSurface(OffLogoGreen, screen, OffX, OffY);
}
//--------
void OnSwitchSound(int OnX, int OnY)
{
	if (PicSetSound == 1)
		SDL_BlitSurface(OnLogoGreen, screen, OnX, OnY);
	if (PicSetSound == 0)
		SDL_BlitSurface(OnLogoGrey, screen, OnX, OnY);
}
void OffSwitchSound(int OffX, int OffY)
{
	if (PicSetSound == 1)
		SDL_BlitSurface(OffLogoGrey, screen, OffX, OffY);
	if (PicSetSound == 0)
		SDL_BlitSurface(OffLogoGreen, screen, OffX, OffY);
}
//---------------------------------------------------------------------------------------------------------------------------------------- Doodle Direction Picture


//---------------------------------------------------------------------------------------------------------------------------------------- Doodle X Axis Movement
void DoodleXMovement()
{
	if (keyState[SDL_SCANCODE_RIGHT])
	{
		DoodleState = 1;
		PlayerX += 25;
	}
	else if (keyState[SDL_SCANCODE_LEFT])
	{
		DoodleState = 2;
		PlayerX -= 25;
	}
	if (PlayerX >= 640)
		PlayerX = -120;
	else if (PlayerX <= -120)
		PlayerX = 640;
}
//----------------------------------------------------------------------------------------------------------------------------------------Ball Y Movement
/*int BallX = PlayerX + 30;
int BallY = PlayerY;
void BallMovement()
{
SDL_BlitSurface(Ball, screen, BallX, BallY);

if (MouseRB != 0) {
BallY -= 840;
}
if (BallY == -20)
BallY = PlayerY;
}*/

//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------------------------------------------Main Function Starts here
int main()
{
	srand((unsigned int)time(NULL));

	for (int i = 0; i < 1; i++) {
		PlatformPositionBlue[i].BlueVx = 3;
	}
	/*for (int i = 0; i < 1; i++) {
		PlatformPositionDarkBlue[i].DarkBlueVy = 3;
	}*/



	//---------------------------------------------------------------

	InitEngine(screen, "Doodle", 640, 840);
	//PlaySound(shotSound , -1) //PLAY
	//PlayMusic(bgMusic , -1) //PLAY


	PlayMusic(BgMusic, -1);
	GameState = 1;
	GenerateW(); //Loads a random Wallapper for the 2nd case (Game)

				 //--------------------------------------------------------------------

	while (!ExitRequested)
	{
		Update();

		SDL_FillRect(screen, NULL, WHITE);


		//----------------------------------------------------------------------------------------------------------------------------------------switch starts here
		switch (GameState) {
			//--------------------------------------------------------------------------------------------------------------------------------  1st case (Menu)
		case 1:

			SDL_BlitSurface(BackG, screen, 0, 0);
			SDL_BlitSurface(PlayerR, screen, PlayerXM, PlayerYM);
			SDL_BlitSurface(Greenplat, screen, 100, 700);
			SDL_BlitSurface(Bug1, screen, 200, 200);
			SDL_BlitSurface(Bug2, screen, 300, 250); 
			SDL_BlitSurface(Logo, screen, 5, 50);
			SDL_BlitSurface(PlayB, screen, 300, 300);
			SDL_BlitSurface(CreditB, screen, 350, 420);
			SDL_BlitSurface(OptionB, screen, 500, 700);
			SDL_BlitSurface(HoleL, screen, 400, 600);
			SDL_BlitSurface(Pointer, screen, MouseX, MouseY);
			UFO1();//Animation for UFO

			PlayerYM += VyM;
			VyM += 6;

			if (PlayerXM >= 50 && PlayerXM <= 190 && PlayerYM >= 550 && PlayerYM <= 600)
				VyM = -60;

			if (MouseX >= 300 && MouseX <= 524 && MouseY >= 300 && MouseY <= 388 && MouseLB != 0)
			{
				SDL_BlitSurface(PlayOnB, screen, 300, 300);
				GameState = 2; //toplay
			}

			if (MouseX >= 350 && MouseX <= 574 && MouseY >= 420 && MouseY <= 508 && MouseLB != 0)
			{
				SDL_BlitSurface(CreditOnB, screen, 350, 420);
				GameState = 4; //tocredits
			}

			if (MouseX >= 500 && MouseX <= 614 && MouseY >= 700 && MouseY <= 795 && MouseLB != 0)
				GameState = 3; //tooptions

			break;
			//---------------------------------------------------------------------------------------------------------------------------------------- 2nd case (Game)
		case 2:
			//-------------------------------- Anything Picture Related
			WallpaperStateFunc();
			Xsub += 0.2;
			Xsp -= 0.1;
			Xf += 0.1;

			FirstPlat();

			GeneratePG();
			ShowPG();

			GeneratePB();
			ShowPB();

			/*GeneratePDB();
			ShowPDB();*/

			GenerateH();
			ShowH();

			GeneratePF();
			ShowPF();

			DoodlePic();

			//--------------------------------------------------------------------- Anything Physics and Control Related
			//BallMovement();
			DoodleXMovement();


			PlayerY += Vy;
			Vy += Gy;

			for (int i = 0; i < 1; i++) {
				if (CollisionDetection(FirstPlatX, FirstPlatY, PlayerX, PlayerY, Vy)) //first plat collision detection
					Vy = -25;
				//Mix_PlayChannel(1, Jump, 0);
			}


			for (int i = 0; i < 5; i++) {
				if (CollisionDetection(PlatformPositionGreen[i].GreenX, PlatformPositionGreen[i].GreenY, PlayerX, PlayerY, Vy)) //Green plats collision detection
					Vy = -25;
				//Mix_PlayChannel(1, Jump, 0);
			}

			for (int i = 0; i < 1; i++) {
				if (CollisionDetection(PlatformPositionBlue[i].BlueX, PlatformPositionBlue[i].BlueY, PlayerX, PlayerY, Vy))  //Blue plats collision detection
					Vy = -25;
				//Mix_PlayChannel(1, Jump, 0);
			}

			/*for (int i = 0; i < 1; i++) {
				if (CollisionDetection(PlatformPositionDarkBlue[i].DarkBlueX, PlatformPositionDarkBlue[i].DarkBlueY, PlayerX, PlayerY, Vy))  //Dark Blue plats collision detection
					Vy = -25;
			}*/


			for (int i = 0; i < 1; i++) {
				if (CollisionDetection(PlatformPositionFake[i].FakeX, PlatformPositionFake[i].FakeY, PlayerX, PlayerY, Vy))  //Fake plats collision detection
					FakePlat();
			}

			for (int i = 0; i < 1; i++) {
				if (CollisionDetectionHole(HolePosition[i].HoleX, HolePosition[i].HoleY, PlayerX, PlayerY, Vy))  //Fake plats collision detection
					GameState = 6;
			}


			//------------------------------------------------------

			if (PlayerY <= 250)
				PlayerY += 8;
			//------------------------------------------------------Shifts The Starter platform

			if (PlayerY <= 270)

				FirstPlatY += Vp;

			//------------------------------------------------------Shifts Green platforms

			if (PlayerY <= 270)
				for (int i = 0; i <= 5; i++)
				{
					{
						PlatformPositionGreen[i].GreenY += Vp;
						if (PlatformPositionGreen[i].GreenY >= 870)
							PlatformPositionGreen[i].showing = false;
					}
					GeneratePG0();
				}
			//------------------------------------------------------Shifts Blue platforms
			if (PlayerY <= 270)
				for (int i = 0; i <= 1; i++)
				{
					{
						PlatformPositionBlue[i].BlueY += Vp;
						if (PlatformPositionBlue[i].BlueY >= 870)
							PlatformPositionBlue[i].showing = false;
					}
					GeneratePB0();
				}
			//------------------------------------------------------Shifts Dark Blue platforms

			/*if (PlayerY <= 270)
				for (int i = 0; i <= 1; i++)
				{
					{
						PlatformPositionDarkBlue[i].DarkBlueY += 9;
						if (PlatformPositionDarkBlue[i].DarkBlueY >= 860)
							PlatformPositionDarkBlue[i].showing = false;
					}
					GeneratePDB0();
				}*/
			//------------------------------------------------------Shift Hole

			if (PlayerY <= 270)
				for (int i = 0; i <= 1; i++)
				{
					{
						HolePosition[i].HoleY += Vp;
						if (HolePosition[i].HoleY >= 870)
							HolePosition[i].showing = false;
					}
					GenerateH0();
				}
				//------------------------------------------------------Shifts Fake platforms
			if (PlayerY <= 270)
				for (int i = 0; i <= 1; i++)
				{
					{
						PlatformPositionFake[i].FakeY += Vp;
						if (PlatformPositionFake[i].FakeY >= 870)
							PlatformPositionFake[i].showing = false;
					}
					GeneratePF0();
				}

		
			//------------------------------------------------------
			if (event.key.keysym.sym == SDLK_p)
				GameState = 5;//goto Pause

			if (PlayerY >= 840)
				GameState = 6;//GameOver

			break;
			//---------------------------------------------------------------------------------------------------------------------------------------- 3rd case (Options)
		case 3: //Options
			SDL_BlitSurface(BackG, screen, 0, 0);
			SDL_BlitSurface(Logo, screen, 5, 20);
			SDL_BlitSurface(OptionLogo, screen, 430, 80);
			SDL_BlitSurface(MusicLogo, screen, 150, 350);
			SDL_BlitSurface(SoundLogo, screen, 400, 350);
			SDL_BlitSurface(Bug3, screen, 200, 150);
			SDL_BlitSurface(OptionsDoodle, screen, 350, 700);
			SDL_BlitSurface(MenuB, screen, 50, 700);
			SDL_BlitSurface(Pointer, screen, MouseX, MouseY);
			//-------------- switches for music
			OnSwitchMusic(150, 400);
			OffSwitchMusic(190, 400);
			if (MouseX >= 150 && MouseX <= 180 && MouseY >= 400 && MouseY <= 430 && MouseLB != 0)
			{
				PicSetMusic = 1; PlayMusic(BgMusic, -1);
				OnSwitchMusic(150, 400);
				OffSwitchMusic(190, 400);
			}
			if (MouseX >= 190 && MouseX <= 220 && MouseY >= 400 && MouseY <= 440 && MouseLB != 0)
			{
				PicSetMusic = 0; StopMusic();
				OnSwitchMusic(150, 400);
				OffSwitchMusic(190, 400);
			}
			//-------------	switches for sound
			OnSwitchSound(400, 400);
			OffSwitchSound(440, 400);
			if (MouseX >= 400 && MouseX <= 430 && MouseY >= 400 && MouseY <= 430 && MouseLB != 0)
			{
				PicSetSound = 1; //(function that enables all sounds)
				OnSwitchSound(400, 400);
				OffSwitchSound(440, 400);
			}
			if (MouseX >= 440 && MouseX <= 470 && MouseY >= 400 && MouseY <= 440 && MouseLB != 0)
			{
				PicSetSound = 0; StopAllSounds();
				OnSwitchSound(400, 400);
				OffSwitchSound(440, 400);
			}
			//-------------
			if (MouseX >= 50 && MouseX <= 274 && MouseY >= 700 && MouseY <= 788 && MouseLB != 0)
			{
				SDL_BlitSurface(MenuOnB, screen, 50, 700);
				GameState = 1;
			}
			break;

			//---------------------------------------------------------------------------------------------------------------------------------------- 4th case (Credits)
		case 4:
			SDL_BlitSurface(BackG, screen, 0, 0);
			SDL_BlitSurface(CreditsText, screen, 78, 10);
			SDL_BlitSurface(CreditsLogo, screen, 105, 390);
			SDL_BlitSurface(MenuB, screen, 208, 700);
			SDL_BlitSurface(Pointer, screen, MouseX, MouseY);
			Monster2();
			if (MouseX >= 208 && MouseX <= 432 && MouseY >= 700 && MouseY <= 788 && MouseLB != 0)
			{
				SDL_BlitSurface(MenuOnB, screen, 208, 700);
				GameState = 1;
			}

			break;
			//----------------------------------------------------------------------------------------------------------------------------------------5th case (Pause)
		case 5:
			SDL_BlitSurface(BackG, screen, 0, 0);
			SDL_BlitSurface(Logo, screen, 5, 20);
			SDL_BlitSurface(PauseText, screen, 430, 80);
			SDL_BlitSurface(ResumeB, screen, 208, 300);
			SDL_BlitSurface(MenuB, screen, 208, 400);
			SDL_BlitSurface(Hole, screen, 400, 600);
			Monster1();//Animation for Monster 1
			SDL_BlitSurface(Pointer, screen, MouseX, MouseY);

			if (MouseX >= 208 && MouseX <= 432 && MouseY >= 300 && MouseY <= 388 && MouseLB != 0)
			{
				SDL_BlitSurface(ResumeOnB, screen, 208, 300);
				GameState = 2;
			}
			if (MouseX >= 208 && MouseX <= 432 && MouseY >= 400 && MouseY <= 488 && MouseLB != 0)
			{
				SDL_BlitSurface(MenuOnB, screen, 208, 400);
				GameState = 1;
			}
			break;
			//----------------------------------------------------------------------------------------------------------------------------------------6th case (GameOver)
		case 6: 
			SDL_BlitSurface(BackG, screen, 0, 0);
			SDL_BlitSurface(Bug4, screen, 200, 150);
			SDL_BlitSurface(Bug5, screen, 500, 600);
			SDL_BlitSurface(Logo, screen, 5, 20);
			SDL_BlitSurface(GameOverLogo, screen, 350, 80);
			SDL_BlitSurface(PlayAgainB, screen, 208, 300);
			SDL_BlitSurface(MenuB, screen, 208, 400);

			Monster3();
			Monster3X += Monster3V;

			if (Monster3State == 1)
				SDL_BlitSurface(monster31, screen, Monster3X, 650);
			if (Monster3State == 2)
				SDL_BlitSurface(monster32, screen, Monster3X, 650);
			else
				SDL_BlitSurface(monster31, screen, Monster3X, 650);


			SDL_BlitSurface(Pointer, screen, MouseX, MouseY);

			if (MouseX >= 208 && MouseX <= 432 && MouseY >= 300 && MouseY <= 388 && MouseLB != 0)
			{
				SDL_BlitSurface(PlayAgainOnB, screen, 208, 300);
				FirstPlat();
				PlayerX = 100;
				PlayerY = 100;
				GameState = 2;
			}
			if (MouseX >= 208 && MouseX <= 432 && MouseY >= 400 && MouseY <= 488 && MouseLB != 0)
			{
				SDL_BlitSurface(MenuOnB, screen, 208, 400);
				PlayerX = 100;
				PlayerY = 100;
				GameState = 1;
			}
			break;
		}
		//----------------------------------------------------------------------------------------------------------------------------------------

		SDL_UpdateScreen();

		SDL_Delay(1);
	}
	return 0;
}

