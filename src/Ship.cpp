/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Ship.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdelpey <bdelpey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/10 16:28:55 by bdelpey           #+#    #+#             */
/*   Updated: 2015/01/12 03:59:54 by ffourati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <string>
#include "Ship.hpp"


const int				Ship::_DEFAULT_X = 20;
const int				Ship::_DEFAULT_Y = 5;
const std::string		Ship::_DEFAULT_ART = ">";

Ship::Ship(void) :
	GameEntity(_DEFAULT_X, _DEFAULT_Y, _DEFAULT_ART)
{
	return;
}

Ship::Ship(int x, int y, std::string str) :
	GameEntity(x, y, str)
{
	return;
}

Ship::Ship(Ship const & src):
	GameEntity(src)
{
	*this = src;
	return;
}

Ship::~Ship(void) {
	return;
}

void	Ship::fire(void) {
	for (int i=0; i < 150;i++) {
		if ((this->m_slots)[i] == 0)
		{
			(this->m_slots)[i] = 1;
			(this->missile)[i] = GameEntity(this->getX(), this->getY() + 1, "-");
			break;
		}
	}
}

Ship &	Ship::operator=(Ship const & rhs)
{

	if (this != &rhs)
	{
		this->setX(rhs.getX());
		this->setY(rhs.getY());
		this->setArt(rhs.getArt());
	}
	for (int i = 0; i < 150; i++)
	{
		this->missile[i] = rhs.missile[i];
		this->m_slots[i] = rhs.m_slots[i];
	}

	return *this;
}

void					Ship::die(void)
{
	this->setAlive(false);
	this->setArt("R");
}

