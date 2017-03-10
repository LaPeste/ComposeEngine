//
//  Renderer.hpp
//  GameEngine2D
//
//  Created by Andrea Catalini on 23/07/16.
//  Copyright © 2016 Andrea Catalini. All rights reserved.
//

#ifndef _RENDERER_HPP_
#define _RENDERER_HPP_

#include "stdafx.h"
#include "System.hpp"

#define RENDERER_MASK Components::APPEARANCE

class Renderer : public System<Appearance>
{
public:
    Renderer(World& world);
    ~Renderer();
    
private:
	void Render(World& world, const unsigned long int entityIndex) override;

    void Draw(World& world, const unsigned long entityIndex, sf::RenderWindow& window);
    
};

#endif /* _RENDERER_HPP_ */
