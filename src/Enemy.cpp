/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Enemy.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffourati <ffourati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/12 01:56:09 by ffourati          #+#    #+#             */
/*   Updated: 2015/01/12 03:27:21 by ffourati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string>
#include "Enemy.hpp"


const int				Enemy::_DEFAULT_X = 20;
const int				Enemy::_DEFAULT_Y = 5;
const std::string		Enemy::_DEFAULT_ART = "#";

Enemy::Enemy(void) :
	GameEntity(_DEFAULT_X, _DEFAULT_Y, _DEFAULT_ART)
{
	return;
}

Enemy::Enemy(int x, int y, std::string str) :
	GameEntity(x, y, str)
{
	return;
}

Enemy::Enemy(Enemy const & src) :
	GameEntity(src)
{
	return;
}

Enemy::~Enemy(void) {
	return;
}

void	Enemy::fire(void) {
	for (int i=0; i < 150;i++) {
		if ((this->m_slots)[i] == 0)
		{
			(this->m_slots)[i] = 1;
			(this->missile)[i] = GameEntity(this->getX(), this->getY() - 1, "*");
			break;
		}
	}
}

Enemy &	Enemy::operator=(Enemy const & rhs) {

	if (this != &rhs)
	{
		this->setX(rhs.getX());
		this->setY(rhs.getY());
		this->setArt(rhs.getArt());

		for (int i = 0; i < 150; i++)
		{
			this->missile[i] = rhs.missile[i];
			this->m_slots[i] = rhs.m_slots[i];
		}
	}

	return *this;
}

