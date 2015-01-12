/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FtRetro.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffourati <ffourati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/11 16:10:09 by ffourati          #+#    #+#             */
/*   Updated: 2015/01/12 04:01:26 by ffourati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <ncurses.h>
#include <unistd.h>
#include <sys/time.h>
#include <signal.h>
#include "FtRetro.hpp"
#include "GameEntity.hpp"
#include "Ship.hpp"
#include "Enemy.hpp"

const int					FtRetro::_DEFAULT_TARGET_FPS = 15;
const int					FtRetro::_N_FRIEZE_ENTITIES = 104;
const int					FtRetro::_ENEMY_POOL_SIZE = 100;
FtRetro*					FtRetro::_instance = NULL;


/////////////////////////////////////////////////////////////////////////////
//////
/////	Coplien core.
////
///
///////////////////////////////////////////////////////////////////////


/* CTOR */								FtRetro::FtRetro() :
	_targetFPS(_DEFAULT_TARGET_FPS),
	_lastFrameDT_usec(0),
	_playerShip(Ship()),
	_topFrieze(new GameEntity[_N_FRIEZE_ENTITIES]),
	_bottomFrieze(new GameEntity[_N_FRIEZE_ENTITIES]),
	_running(false),
	_runningTimeDT_sec(0),
	_faulty(false),
	_enemyPool(new Enemy[_ENEMY_POOL_SIZE]),
	_enemySlots(new int[_ENEMY_POOL_SIZE])
{
	for (int i = 0; i < _ENEMY_POOL_SIZE; i++)
	{
		_enemySlots[i] = 0;
	}
}

/* Copy CTOR */							FtRetro::FtRetro(FtRetro const & from)
{
	// SHOULD NOT BE USED
	*this = from;
}

/* DTOR */								FtRetro::~FtRetro()
{
	struct sigaction				sa;

	sa.__sigaction_u.__sa_handler = SIG_DFL;
	sa.sa_mask = sigsetmask(0);
	sa.sa_flags = 0;

	sigaction(SIGINT, &sa, NULL);

	endwin();

	_running = false;

	delete[] _topFrieze;
	_topFrieze = NULL;
	delete[] _bottomFrieze;
	_bottomFrieze = NULL;
	delete[] _enemySlots;
	_enemySlots = NULL;
	delete[] _enemyPool;
	_enemyPool = NULL;
}


FtRetro&								FtRetro::operator= (const FtRetro& from)
{
	if (&from != this)
	{
		// SHOULD NOT GET HERE.
		GameEntity*			cpTopFreize = new GameEntity[_N_FRIEZE_ENTITIES];
		GameEntity*			cpBottomFreize = new GameEntity[_N_FRIEZE_ENTITIES];
		int*				cpEnemySlots = new int[_ENEMY_POOL_SIZE];
		Enemy*				cpEnemyPool = new Enemy[_ENEMY_POOL_SIZE];

		if (!cpBottomFreize || !cpTopFreize || !cpEnemySlots || !cpEnemyPool)
		{
			_faulty = true;
			std::abort();
		}

		for (int i = _N_FRIEZE_ENTITIES - 1; i >= 0; i--)
		{
			cpTopFreize[i] = from._topFrieze[i];
			cpBottomFreize[i] = from._bottomFrieze[i];
		}

		for (int i = _ENEMY_POOL_SIZE - 1; i >= 0; i--)
		{
			cpEnemyPool[i] = from._enemyPool[i];
			cpEnemySlots[i] = from._enemySlots[i];
		}

		delete[] _topFrieze;
		_topFrieze = cpTopFreize;
		delete[] _bottomFrieze;
		_bottomFrieze = cpBottomFreize;
		delete[] _enemyPool;
		_enemyPool = cpEnemyPool;
		delete[] _enemySlots;
		_enemySlots = cpEnemySlots;

		_targetFPS = from.getTargetFPS();
		_lastFrameDT_usec = from.getLastFrameDT_usec();
		_playerShip = from.getPlayerShip();
		_running = from.isRunning();
		_runningTimeDT_sec = from.getRunningTimeDT_sec();
		_faulty = from.isFaulty();
	}

	return *this;
}

/////////////////////////////////////////////////////////////////////////////
//////
/////	Accessors.
////
///
///////////////////////////////////////////////////////////////////////

int										FtRetro::getTargetFPS(void) const
{
	return _targetFPS;
}

Ship&									FtRetro::getPlayerShip(void) const
{
	return this->getPlayerShip();
}


int										FtRetro::getDefaultTargetFPS(void)
{
	return _DEFAULT_TARGET_FPS;
}

bool									FtRetro::isFaulty(void) const
{
	return _faulty;
}

bool									FtRetro::isRunning(void) const
{
	return (_running && !_faulty);
}

int										FtRetro::getMinimumFrameLag_usec(void) const
{
	return (1000000 / _targetFPS);
}

int										FtRetro::getLastFrameDT_usec(void) const
{
	return _lastFrameDT_usec;
}

time_t									FtRetro::getRunningTimeDT_sec(void) const
{
	return _runningTimeDT_sec;
}

void									FtRetro::handleKillersigs(int sig)
{
	(void)sig;
	FtRetro::getInstance()->_running = false;
}


/////////////////////////////////////////////////////////////////////////////
//////
/////	Application life cycle.
////
///
///////////////////////////////////////////////////////////////////////

FtRetro*								FtRetro::initializeInstance(void)
{
	struct sigaction					sa;

	if (_instance != NULL)
	{
		return NULL;
	}

	sa.__sigaction_u.__sa_handler = &FtRetro::handleKillersigs;
	sa.sa_mask = sigsetmask(0);
	sa.sa_flags = SA_RESETHAND;

	if (sigaction(SIGINT, &sa, NULL) == -1)
	{
		std::cerr << "sigaction() failed at " << __func__ << std::endl;
		std::abort();
	}

	std::srand(std::time(NULL));

	initscr();
	raw();
	noecho();
	keypad(stdscr, TRUE);
	curs_set(FALSE);
	nodelay(stdscr, TRUE);
	cbreak();

	_instance = new FtRetro();

	if (!_instance)
	{
		std::abort();
	}

	return _instance;
}


FtRetro*								FtRetro::getInstance(void)
{
	return _instance;
}


void									FtRetro::finalizeInstance(void)
{
	if (_instance)
	{
		_instance->stop();

		delete _instance;
		_instance = NULL;
	}
}


/////////////////////////////////////////////////////////////////////////////
//////
/////	Main loop.
////
///
///////////////////////////////////////////////////////////////////////

int										FtRetro::run(void)
{
	struct timeval						tvLastFrame, tvCurrentFrame;

	if (_faulty)
		return -1;


	if (gettimeofday(&tvCurrentFrame, NULL) == -1)
	{
		return static_cast<int>((_faulty = true));
	}
	else
	{
		tvLastFrame = tvCurrentFrame;
	}

	this->buildFriezes();

	_running = true;
	_runningTimeDT_sec = 0;

	while (_running)
	{
		int						minDT_usec = this->getMinimumFrameLag_usec();
		int						dt_usec = 0;
		int						extraDT_usec = 0;

		tvLastFrame = tvCurrentFrame;


		if (_playerShip.isAlive())
		{
			erase();

			this->spawnEnemies();
			this->updateEnemies();
			this->drawEnemiesAndMissiles();
			this->drawFriezes();
			this->draw(_playerShip);


			refresh();
		}
		this->acquireInput();

		flushinp();

		if (gettimeofday(&tvCurrentFrame, NULL) == -1)
		{
			return static_cast<int>((_faulty = true));
		}

		dt_usec = static_cast<int>(tvCurrentFrame.tv_usec - tvLastFrame.tv_usec)
			+ static_cast<int>((tvCurrentFrame.tv_sec - tvLastFrame.tv_sec) * 1000000L);


		// Enforce max FPS if there's no update lag.
		if (minDT_usec - dt_usec > 0)
		{
			extraDT_usec = minDT_usec - dt_usec;
			usleep(extraDT_usec);
		}

		_lastFrameDT_usec = dt_usec  + extraDT_usec;
		_runningTimeDT_sec += tvCurrentFrame.tv_sec - tvLastFrame.tv_sec;
	}

	return static_cast<int>(_faulty);
}

void								FtRetro::stop(void)
{
	_running = false;
}


/////////////////////////////////////////////////////////////////////////////
//////
/////	Main loop functions.
////
///
///////////////////////////////////////////////////////////////////////

void								FtRetro::acquireInput(void)
{
	int ch;

	ch = getch();

	switch (ch)
	{
		case KEY_RIGHT:
			_playerShip.setY(_playerShip.getY() + 1);
			break;
		case KEY_DOWN:
			_playerShip.setX(_playerShip.getX() + 1);
			break;
		case KEY_LEFT:
			_playerShip.setY(_playerShip.getY() - 1);
			break;
		case KEY_UP:
			_playerShip.setX(_playerShip.getX() - 1);
			break;
		case 033:
		case 'q':
			this->stop();
			break;
		case ' ':
			_playerShip.fire();
			break;
		default:	
			break;
	}
}

void					FtRetro::draw(GameEntity& g) const
{
	mvprintw(g.getX(), g.getY(), g.getArt().c_str());
	return;
}

void					FtRetro::buildFriezes(void) const
{
	for ( unsigned int i = 0; i < _N_FRIEZE_ENTITIES; i++)
	{
		_topFrieze[i].setY(i);
		_bottomFrieze[i].setY(i);
		if (i % 8 < 5) {
			_topFrieze[i].setX(i % 8);
			_bottomFrieze[i].setX(30 - (i % 8));
		}
		else {
			_topFrieze[i].setX(8 - i % 8);
			_bottomFrieze[i].setX(30 - (8 - i % 8));
		}
	}
}

void					FtRetro::drawFriezes(void)
{
	int					yTop, yBottom;

	for(int i = 0 ; i < _N_FRIEZE_ENTITIES; i++)
	{
		if (_topFrieze[i].collidesWith(_playerShip) || _bottomFrieze[i].collidesWith(_playerShip))
		{
			_playerShip.die();
		}

		yTop = _topFrieze[i].getY() - 1 < 0 ? _N_FRIEZE_ENTITIES : _topFrieze[i].getY() - 1;
		yBottom = _bottomFrieze[i].getY() - 1 < 0 ? _N_FRIEZE_ENTITIES : _bottomFrieze[i].getY() - 1;

		_topFrieze[i].setY(yTop);
		_bottomFrieze[i].setY(yBottom);

		this->draw(_topFrieze[i]);
		this->draw(_bottomFrieze[i]);
	}
}

void					FtRetro::spawnEnemies(void)
{
	int r;	
	int difficultyLevel = _runningTimeDT_sec / 3;

	if (difficultyLevel <= 0)
		difficultyLevel = 1;

	if ((r = rand() % (_ENEMY_POOL_SIZE / difficultyLevel)) != 0)
	{
		return;
	}

	for (int e = 0; e < _ENEMY_POOL_SIZE; e++) 
	{
		if (_enemySlots[e] == 0) 
		{
			int i = rand() % (_ENEMY_POOL_SIZE / 5) + 5;

			_enemySlots[e] = 1;
			_enemyPool[e] = Enemy(i, _N_FRIEZE_ENTITIES, "#");
			_enemyPool[e].setAlive(true);
			break;
		}
	}
}

void					FtRetro::updateEnemies(void)
{
	for (int i = 0; i < _ENEMY_POOL_SIZE; i++)
	{
		if (!_enemySlots[i])
			continue;
		_enemyPool[i].setY(_enemyPool[i].getY() - 1);
		if (_enemyPool[i].getY() == 0) {
			_enemyPool[i].die();
			_enemySlots[i] = 0;
		}
		for (int j = 0; j < 150; j++) 
		{
			if (_runningTimeDT_sec % 3 == 2)
			{
				_enemyPool[i].fire();
			}
			if (!(_playerShip.m_slots[j]))
				continue;
			if (_enemyPool[i].collidesWith(_playerShip.missile[j]))
			{
				_enemyPool[i].die();
				_playerShip.missile[j].die();
				_enemySlots[i] = 0;
				_playerShip.m_slots[j] = 0;
			}
		}
	}
}

void					FtRetro::drawEnemiesAndMissiles(void) 
{
	for (int i=0; i < 150;i++)
	{
		GameEntity&		rPlayerMissile = _playerShip.missile[i];
		int&			rPlMissileSlot = _playerShip.m_slots[i];
		Enemy&			rEnemy = _enemyPool[i];


		if (rPlMissileSlot)
		{
			rPlayerMissile.setY(rPlayerMissile.getY() + 1);
			if (rPlayerMissile.getY() > 103)
			{
				rPlayerMissile.die();
				rPlMissileSlot = 0;
			}
			if (rPlayerMissile.isAlive())
				this->draw(rPlayerMissile);
		}

		if (i < _ENEMY_POOL_SIZE && _enemySlots[i] && rEnemy.isAlive())
		{
			if (rEnemy.collidesWith(_playerShip))
			{
				_playerShip.die();
			}

			for (int j = 0; j < 150; j++)
			{
				GameEntity&			rEneMissile = rEnemy.missile[j];
				int&				rEneMissileSlot = rEnemy.m_slots[j];

				if (rEneMissileSlot)
				{
					rEneMissile.setY(rEneMissile.getY() - 2);
					if (rEneMissile.collidesWith(_playerShip))
					{
						_playerShip.die();
					}
					if (rEneMissile.getY() <= 0)
					{
						rEneMissile.die();
						rEneMissileSlot = 0;
					}
					if (rEneMissile.isAlive())
						this->draw(rEneMissile);
				}
			}
			this->draw(rEnemy);
		}
	}
}

