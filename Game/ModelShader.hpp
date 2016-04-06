//
//  ModelShader.hpp
//  Game
//
//  Created by Pepe Becker on 3/5/16.
//  Copyright © 2016 Pepe Becker. All rights reserved.
//

#ifndef ModelShader_hpp
#define ModelShader_hpp

#include <stdio.h>
#include "ShaderProgram.hpp"

class ModelShader : public ShaderProgram {
public:
    ModelShader();
    
    void getAllUniformLocations();
    void bindAttributes();
};

#endif /* ModelShader_hpp */
