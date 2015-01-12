/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FtRetro.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffourati <ffourati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/11 16:11:04 by ffourati          #+#    #+#             */
/*   Updated: 2015/01/12 02:43:07 by ffourati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Ship.hpp"
#include "Enemy.hpp"

class FtRetro
{
	public:

		FtRetro&					operator= (const FtRetro& from);

		int							getTargetFPS(void) const;
		static int					getDefaultTargetFPS(void);
		int							getMinimumFrameLag_usec(void) const;
		time_t						getRunningTimeDT_sec(void) const;
		bool						isFaulty(void) const;
		bool						isRunning(void) const;

		int							run(void);
		void						stop(void);

		static FtRetro*				initializeInstance(void);
		static FtRetro*				getInstance(void);
		static void					finalizeInstance(void);

	protected:

		int							getLastFrameDT_usec(void) const;
		Ship&						getPlayerShip(void) const;

	private:

		int							_targetFPS;
		int							_lastFrameDT_usec;
		Ship						_playerShip;
		GameEntity*					_topFrieze;
		GameEntity*					_bottomFrieze;
		bool						_running;
		time_t						_runningTimeDT_sec;
		bool						_faulty;
		Enemy*						_enemyPool;
		int*						_enemySlots;

		static const int			_DEFAULT_TARGET_FPS;
		static const int			_N_FRIEZE_ENTITIES;
		static const int			_ENEMY_POOL_SIZE;
		static FtRetro*				_instance;

		FtRetro();
		FtRetro(int atFPS);
		FtRetro(const FtRetro &from);
		~FtRetro();

		static void					handleKillersigs(int sig);

		/////////////////////////////////////////////////////////////////////////////
		//////
		/////	Main loop functions.
		////
		///
		///////////////////////////////////////////////////////////////////////

		void					acquireInput(void);
		void					draw(GameEntity& g) const;
		void					buildFriezes(void) const;
		void					drawFriezes(void);
		void					spawnEnemies(void);
		void					updateEnemies(void);
		void					drawEnemiesAndMissiles(void);

};

