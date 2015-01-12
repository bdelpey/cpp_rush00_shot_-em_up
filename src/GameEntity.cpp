/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GameEntity.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdelpey <bdelpey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/10 16:16:32 by bdelpey           #+#    #+#             */
/*   Updated: 2015/01/12 03:43:36 by ffourati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "GameEntity.hpp"

const int						GameEntity::_DEFAULT_X = 0;
const int						GameEntity::_DEFAULT_Y = 0;
const std::string				GameEntity::_DEFAULT_ART = "*";

GameEntity::GameEntity(void) :
	_x(_DEFAULT_X),
	_y(_DEFAULT_Y),
	_art(_DEFAULT_ART),
	_live(1)
{
	return;
}

GameEntity::GameEntity(int x, int y, std::string str) :
   	_x(x),
   	_y(y),
   	_art(str),
   	_live(1)
{
	return;
}

GameEntity::GameEntity(GameEntity const & src) {
	*this = src;
	return;
}

GameEntity::~GameEntity(void) {
	return;
}

GameEntity &	GameEntity::operator=(GameEntity const & rhs) {
	if (this != &rhs)
	{
		this->_x = rhs._x;
		this->_y = rhs._y;
		this->_art = rhs._art;
		this->_live = rhs._live;
	}

	return *this;
}

int				GameEntity::getX(void) const {
	return this->_x;
}

int				GameEntity::getY(void) const {
	return this->_y;
}

std::string		GameEntity::getArt(void) const {
	return this->_art;
}

void			GameEntity::setX(int x) {
	this->_x = x;
	if (this->_x < 0)
		this->_x = 0;
	if (this ->_x > 30)
		this->_x = 30;
	return;
}

void			GameEntity::setY(int y) {
	this->_y = y;
	if (this->_y < 0)
		this->_y = 0;
	if (this ->_y > 104)
		this->_y = 104;
	return;
}

void			GameEntity::setArt(std::string const s) {
	this->_art = s;
	return;
}

bool					GameEntity::collidesWith(GameEntity const& other) const
{
	return (other.getX() == this->getX()
			&& (other.getY() == this->getY() || other.getY() + 1 == this->getY()));
}

void					GameEntity::die(void)
{
	this->_live = false;
}

bool					GameEntity::isAlive(void) const
{
	return this->_live;
}

void								GameEntity::setAlive(bool live)
{
	_live = live;
}
