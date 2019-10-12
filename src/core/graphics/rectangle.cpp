#include "rectangle.h"

#include <vector>
#include "../graphics/shader.h"

namespace core::graphics
{

std::unique_ptr<Shader> Rectangle::shader_ = nullptr; 

Rectangle::Rectangle(float width, float height,
                     const math::Point<float>& pos, 
                     const Color& color)
    : offset_(0.0f, 0.0f)
    , color_(color)
{
    std::vector<float> vertices = {
        pos.x - (width/ 2.0f), pos.y - (height/ 2.0f), //bottom left
        pos.x + (width/ 2.0f), pos.y - (height / 2.0f), //bottom right
        pos.x + (width/ 2.0f), pos.y + (height / 2.0f), //top right
        pos.x - (width/ 2.0f), pos.y + (height / 2.0f), //top left
    };

    std::vector<unsigned> indices = {
        0, 1, 2, //bottom left triangle
        2, 3, 0  //top right triangle
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

Rectangle::~Rectangle() = default;

void Rectangle::draw() const
{
    shader_->bind();
    shader_->setUniformVec4f("inColor", math::vec4<float>::fromArray(color_.data));
    shader_->setUniformVec2f("translation", offset_);
    mesh_->draw();
}

void Rectangle::move(const math::vec2<float>& direction)
{
    offset_.x += direction.x;
    offset_.y += direction.y;
}
}
