#include "Shared.h"
#include "sprig.h"
#include <cmath>
#include <iostream>

SDL_Surface* Shared::LoadImage( std::string filename, bool key)
{
    //Temporary storage for the image that's loaded
    SDL_Surface* loadedImage = NULL;

    //The optimized image that will be used
    SDL_Surface* optimizedImage = NULL;

    //Load the image
    loadedImage = IMG_Load( filename.c_str() );

    //If nothing went wrong in loading the image
    if( loadedImage != NULL )
    {
        //Create an optimized image
        if (key)
            optimizedImage = SDL_DisplayFormat( loadedImage );
        else
            optimizedImage = SDL_DisplayFormatAlpha( loadedImage );

        //Free the old image
        SDL_FreeSurface( loadedImage );
    }
	else
		std::cout<<"Error loading file : " << filename<<std::endl;

    //Return the optimized image
    return optimizedImage;
}

void Shared::DrawSurface( int x, int y, SDL_Surface* pSource, SDL_Surface* destination, SDL_Rect* pClips )
{
    SDL_Rect offset;
    offset.x = x;
    offset.y = y;
    SDL_BlitSurface( pSource, pClips, destination, &offset );
}

void Shared::CheckClip(Timer &rTimer, int &rClip, int interval, int maxClip, int reset)
{
	if (rTimer.GetTicks() > interval)
    { 
        if (rClip < maxClip - 1)
            rClip++;
        else
            rClip = reset;
        rTimer.Start();
	}
}

void Shared::SetFrames(SDL_Rect* clips, int maxClips, int width, int height, int y)
{
	for (int i=0; i<= maxClips - 1; i++)
	{
        clips[i].x = i * width;
        clips[i].y = y;
        clips[i].w = width; 
        clips[i].h = height;
	}
}

void Shared::SetVertFrames(SDL_Rect* clips, int maxClips, int width, int height)
{
	for (int i=0; i<= maxClips - 1; i++)
	{
        clips[i].x = 0;
        clips[i].y = i * height;
        clips[i].w = width; 
        clips[i].h = height;
	}
}

SDL_Surface* Shared::CropSurface(SDL_Surface* src, int x, int y, int width, int height)
{
    SDL_Surface* temp = SPG_CreateSurface(0, width, height);
    SDL_Rect rect = {x, y, width, height};
	SPG_PushBlend(SPG_SRC_ALPHA);
    SPG_Blit(src, &rect, temp, NULL);
	SDL_Surface* dest = SDL_DisplayFormat(temp);
	SPG_PopBlend();
	SDL_FreeSurface(temp);
	return dest;
}

void Shared::SetRotationFrames(SDL_Rect* clips, SDL_Surface* pSrc, int maxClips, int width, int height,
	SDL_Surface*** pDest, int startAngle, int endAngle, int destWidth, int destHeight, 
	int pivotX, int pivotY, int rotInterval)
{
	int angle = endAngle-startAngle;
	for (int i=0; i<maxClips; i++)
	{
		pDest[i] = new SDL_Surface*[angle];
		for (int k=startAngle; k<endAngle; k+=rotInterval)
		{
			SDL_Surface* tempSrc = SPG_CreateSurface(0, width, height);
			SDL_Surface* tempDest = SPG_CreateSurface(0, width*2, height*2);
			SPG_PushBlend(SPG_SRC_ALPHA);
			SPG_Blit(pSrc, &clips[i], tempSrc, NULL);
			SPG_TransformX(tempSrc, tempDest, -k, 1, 1, pivotX, pivotY, destWidth, destHeight, SPG_TAA | SPG_TSAFE);
			SPG_PopBlend();
			pDest[i][k] = SDL_DisplayFormatAlpha(tempDest);
			SDL_FreeSurface(tempSrc);
			SDL_FreeSurface(tempDest);
		}
	}
}

void Shared::DeleteRotationFrames(SDL_Surface*** surface, int maxClips, int startAngle, int endAngle, int rotInterval)
{
	int mAngle = endAngle-startAngle;
	for (int i=0; i<maxClips; i++)
	{
		for (int k=startAngle; k<endAngle; k+=rotInterval)
		{
			SDL_FreeSurface(surface[i][k]);
		}
	}
}

int Shared::Mod(int a, int b)
{
   int ret = a % b;
   if(ret < 0)
     ret+=b;
   return ret;
}

double Shared::Distance( int x1, int y1, int x2, int y2 )
{	//Return the distance between the two points
    return sqrt( pow( (double)x2 - x1, (int)2 ) + pow( (double)y2 - y1, (int)2 ) );
}
