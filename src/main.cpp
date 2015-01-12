/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdelpey <bdelpey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/10 14:26:53 by bdelpey           #+#    #+#             */
/*   Updated: 2015/01/12 01:04:46 by ffourati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "FtRetro.hpp"

int							main(int, char**)
{
	FtRetro*				gameInstance = FtRetro::initializeInstance();
	int						exitcode = 0;

	if (gameInstance == NULL)
	{
		std::cerr << "Game instance failed to initialize !" << std::endl;
		exitcode = 1;
	}
	else
	{
		if ((exitcode = gameInstance->run()) != 0 || gameInstance->isFaulty())
		{
			std::cerr << "GameInstance went faulty." << std::endl;
		}
	}

	FtRetro::finalizeInstance();
	

	return exitcode;
}

