/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Ship.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdelpey <bdelpey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/10 16:26:19 by bdelpey           #+#    #+#             */
/*   Updated: 2015/01/12 03:59:34 by ffourati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#pragma once

#include <string>
#include "GameEntity.hpp"

class Ship : public GameEntity {

	public:

		Ship(void);
		Ship(int x, int y, std::string str);
		Ship(Ship const & src);
		Ship &	operator=(Ship const & rhs);
		virtual ~Ship(void);

		virtual void			fire(void);
		virtual void			die(void);
		GameEntity				missile[150];
		int						m_slots[150];

	private:

		static const int				_DEFAULT_X;
		static const int				_DEFAULT_Y;
		static const std::string		_DEFAULT_ART;

};
