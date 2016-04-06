//
//  Block.hpp
//  Game
//
//  Created by Pepe Becker on 3/9/16.
//  Copyright © 2016 Pepe Becker. All rights reserved.
//

#ifndef Block_hpp
#define Block_hpp

#include <stdio.h>
#include "Model.hpp"

const GLuint RIGHT_FACE = 0;
const GLuint LEFT_FACE = 1;
const GLuint TOP_FACE = 2;
const GLuint BOTTOM_FACE = 3;
const GLuint BACK_FACE = 4;
const GLuint FRONT_FACE = 5;

class Block : public Model {
private:
    GLboolean drawFace[6];
    
public:
    Block();
    
    void buildModel();
    void showFace(GLuint face);
    void hideFace(GLuint face);
};

#endif /* Block_hpp */
