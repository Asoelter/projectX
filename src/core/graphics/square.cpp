#include "square.h"

#include <vector>
#include "../graphics/shader.h"

namespace core::graphics
{

std::unique_ptr<Shader> Square::shader_ = nullptr; 

Square::Square(float dimension, const math::Point<float>& pos, const Color& color)
    : offset_(0.0f, 0.0f)
{
    std::vector<float> vertices = {
        pos.x - (dimension / 2.0f), pos.y - (dimension / 2.0f), //bottom left
        pos.x + (dimension / 2.0f), pos.y - (dimension / 2.0f), //bottom right
        pos.x + (dimension / 2.0f), pos.y + (dimension / 2.0f), //top right
        pos.x - (dimension / 2.0f), pos.y + (dimension / 2.0f), //top left
    };

    std::vector<unsigned> indices = {
        0, 1, 2, //bottom left triangle
        2, 3, 0  //bottom right triangle
    };

    mesh_ = std::make_unique<Mesh<float>>(vertices, indices);

    if(!shader_)
    {
        shader_ = std::make_unique<Shader>("src/res/shaders/solid.vs", 
                                           "src/res/shaders/solid.fs");
    }

    shader_->bind();
    shader_->setUniformVec4f("inColor", math::vec4<float>::fromArray(color.data));
}

void Square::draw() const
{
    shader_->bind();
    mesh_->draw();
}

void Square::move(const math::vec2<float>& direction)
{
    shader_->bind();
    offset_.x += direction.x;
    offset_.y += direction.y;
    shader_->setUniformVec2f("translation", offset_);
}

}
