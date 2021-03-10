#include <libyardland/gui/texture.hpp>

//Rendered texture
Texture gTextTexture;


Texture::Texture()
{
	//Initialize
	this->mTexture = NULL;
	this->transform.scale.x = 0;
	this->transform.scale.y = 0;
}

Texture::~Texture()
{
	//Deallocate
	this->FreeTexture();
}

/*int Texture::LoadFromFile(std::string path)
{
	//Get rid of preexisting texture
	this->FreeTexture();

	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if( loadedSurface == NULL )
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	}
	else
	{
		//Color key image
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));

		//Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
		if(newTexture == NULL)
		{
			printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}
		else
		{
			//Get image dimensions
			mWidth = loadedSurface->w;
			mHeight = loadedSurface->h;
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	//Return success
	mTexture = newTexture;
	return mTexture != NULL;
}*/

int Texture::LoadFromRenderedText(std::string textureText, SDL_Color textColor)
{
	//Get rid of preexisting texture
	this->FreeTexture();

	//Render text surface
	SDL_Surface* textSurface = TTF_RenderText_Solid(GuiFont, textureText.c_str(), textColor);
	if(textSurface == NULL)
	{
		printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
	}
	else
	{
		//Create texture from surface pixels
        this->mTexture = SDL_CreateTextureFromSurface(GuiRenderer, textSurface);
		if(this->mTexture == NULL)
		{
			printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
		}
		else
		{
			//Get image dimensions
			this->transform.scale.x = textSurface->w;
			this->transform.scale.y = textSurface->h;
		}

		//Get rid of old surface
		SDL_FreeSurface(textSurface);
	}
	
	//Return success
	return this->mTexture != NULL;
}

void Texture::FreeTexture()
{
	//Free texture if it exists
	if(this->mTexture != NULL)
	{
		SDL_DestroyTexture(this->mTexture);
		this->mTexture = NULL;
		this->transform.scale.x = 0;
		this->transform.scale.y = 0;
	}
}

void Texture::OnRender(SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip)
{
	//Set rendering space and render to screen
	SDL_Rect renderQuad = {this->transform.position.x, this->transform.position.y, this->transform.scale.x, this->transform.scale.y};

	//Set clip rendering dimensions
	if(clip != NULL)
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	//Render to screen
	SDL_RenderCopyEx(GuiRenderer, mTexture, clip, &renderQuad, angle, center, flip);
}
