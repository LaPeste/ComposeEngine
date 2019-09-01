//
//  Appearance.hpp
//  GameEngine2D
//
//  Created by Andrea Catalini on 22/07/16.
//  Copyright © 2016 Andrea Catalini. All rights reserved.
//

#ifndef _APPEARANCE_HPP_
#define _APPEARANCE_HPP_

#include "stdafx.h"
#include "Components/Component.hpp"

class AnimationData;

class Appearance : public Component<Appearance>
{
public:
    Appearance(World& world, const unsigned long int entityIndex, std::string spritePath, sf::IntRect initialAppearance = sf::IntRect());
    ~Appearance() override;
    
    //TODO maybe make them private and make them setable only from constructor?
    std::string SpritePath;

    //! returns null if not loaded
    sf::Sprite* const GetSprite() const; 
    void SetSprite(std::unique_ptr<const sf::Sprite>& m_sprite);
    bool IsTextureLoaded() const;
    
private:
    std::unique_ptr<sf::Sprite> m_sprite;
    sf::Texture* texture;
    
};

#endif /* _APPEARANCE_HPP_ */
