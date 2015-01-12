/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Enemy.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffourati <ffourati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/12 01:55:41 by ffourati          #+#    #+#             */
/*   Updated: 2015/01/12 02:59:30 by ffourati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>
#include "GameEntity.hpp"

class Enemy : public GameEntity {

	public:

		Enemy(void);
		Enemy(int x, int y, std::string str);
		Enemy(Enemy const & src);
		Enemy &	operator=(Enemy const & rhs);
		virtual ~Enemy(void);

		virtual void			fire(void);
		GameEntity				missile[150];
		int						m_slots[150];

	private:

		static const int				_DEFAULT_X;
		static const int				_DEFAULT_Y;
		static const std::string		_DEFAULT_ART;

};
