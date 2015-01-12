/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GameEntity.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdelpey <bdelpey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/10 15:52:24 by bdelpey           #+#    #+#             */
/*   Updated: 2015/01/12 03:40:43 by ffourati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_ENTITY_H
# define GAME_ENTITY_H

#include <string>

class GameEntity {
	public:

		GameEntity(void);
		GameEntity(int x, int y, std::string str);
		GameEntity(GameEntity const & src);
		GameEntity &	operator=(GameEntity const & rhs);
		virtual ~GameEntity(void);
		
		int						getX(void) const;
		int						getY(void) const;
		std::string				getArt(void) const;

		void					setX(int x); 
		void					setY(int y);
		void					setArt(std::string const s);

		virtual bool			collidesWith(GameEntity const& other) const;
		virtual void			die(void);
		bool					isAlive(void) const;
		void					setAlive(bool live);

	protected:
		

	private:

		int				_x;
		int				_y;
		std::string		_art;
		bool			_live;

		static const int				_DEFAULT_X;
		static const int				_DEFAULT_Y;
		static const std::string		_DEFAULT_ART;

};

#endif
