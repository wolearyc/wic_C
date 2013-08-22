// ------------------------------------------------------------------------------------------------
// File:			TextField.cpp
//-------------------------------------------------------------------------------------------------

#include "TextField.h"
namespace wick
{
	// Constructors.
	TextField::TextField(Text text, Image background, Pair location, Pair textOffset,
						 int characters, Box target)
	{
		text_ = text;
		message_ = text.getMessage();
		background_ = background;
		if(characters<1)
		{
			wickThrowError("Invalid charactor limit.");
		}
		characters_ = characters;
		offset_ = textOffset;
		target_ = HitBox(location, target);
		setLocation(location);
		active_ = false;
	}
	TextField::TextField(const TextField& other)
	{
		text_ = other.text_;
		message_ = other.message_;
		background_ = other.background_;
		characters_ = other.characters_;
		offset_ = other.offset_;
		target_ = other.target_;
		active_ = other.active_;
	}
	TextField::TextField()
	{
		text_ = Text();
		message_ = "";
		background_ = Image();
		characters_ = 0;
		offset_ = Pair();
		target_ = HitBox();
		active_ = false;
	}

	// Updates logic.
	void TextField::update(Input* input, int fps, Graphics* graphics)
	{
		if(target_.intersects(input->getMouseLocation()) && input->isKeyDown("LMB"))
		{
			active_ = true;
		}
		if(active_)
		{
			vector<string> pressed = input->getPressed();
			for(unsigned int i = 0; i<pressed.size(); i++)
			{
				string key = pressed[i];
				if(key.size()==1)
				{
					message_ += pressed[i];
				}
				else if(key == "BACK")
				{
					string temp = message_.substr(0,message_.size()-1);
					message_ = temp;
				}
			}
			if(message_.size()>characters_)
			{
				text_.setMessage(message_.substr(message_.size()-characters_)+">");
			}
			else
			{
				text_.setMessage(message_ + ">");
			}
		}
	}

	// Paints TextField to screen.
	void TextField::paint(Graphics* graphics)
	{
		background_.paint(graphics);
		text_.paint(graphics);
	}

	// Returns location.
	void TextField::setLocation(Pair location)
	{
		background_.setLocation(location);
		location.x_ += offset_.x_;
		location.y_ += offset_.y_;
		text_.setLocation(location);
		target_.setLocation(location);
	}

	// Activation methods.
	void TextField::activate()
	{
		active_ = true;
	}
	void TextField::deactivate()
	{
		active_ = false;
	}
	bool TextField::active()
	{
		return(active_);
	}

	// Message methods.
	void TextField::setMessage(string message)
	{
		message_ = message;
	}
	string TextField::getMessage()
	{
		return(message_);
	}
}
