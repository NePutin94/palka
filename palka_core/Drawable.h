//
// Created by NePutin on 7/25/2021.
//

#ifndef PALKA_DRAWABLE_H
#define PALKA_DRAWABLE_H

namespace palka
{
    class Renderer;
    class Drawable
    {
    private:
        virtual void draw(Renderer& win) const = 0;
        mutable struct{
            bool hasBindBuffer = false;
            //GLuint VAO = 0;
            //GLuint VBO = 0;
        }DrawData;
    public:
        virtual ~Drawable()
        {}

        friend class Renderer;
    };
}
#endif //PALKA_DRAWABLE_H
