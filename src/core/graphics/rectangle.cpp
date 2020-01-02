#include "rectangle.h"

#include <vector>

#include "shader.h"

#include "../../util/handmade_util.h"

namespace core::graphics
{

std::unique_ptr<Shader> Rectangle::shader_  = nullptr; 
const char * Rectangle::vertexPath          = "src/res/shaders/solid.vs";
const char * Rectangle::fragmentPath        = "src/res/shaders/solid.fs";

namespace 
{

std::vector<float> initVertices(const math::Point<float>& pos, float width, float height)
{
    return {
        pos.x - (width / 2.0f), pos.y - (height / 2.0f), //bottom left
        pos.x + (width / 2.0f), pos.y - (height / 2.0f), //bottom right
        pos.x + (width / 2.0f), pos.y + (height / 2.0f), //top right
        pos.x - (width / 2.0f), pos.y + (height / 2.0f), //top left
    };
}

std::vector<float> initTexCoords()
{
    return {
        0, 0, //bottom left
        1, 0, //bottom right
        1, 1, //top right
        0, 1  //top left
    };
}

std::vector<unsigned> initElementBuffer()
{
    return {
        0, 1, 2, //bottom left triangle
        2, 3, 0  //top right triangle
    };
}

}

Rectangle::Rectangle(float width, float height,
                     const math::Point<float>& pos, 
                     const Color& color)
    : width_(width)
    , height_(height)
    , offset_(0.0f, 0.0f)
    , initialPosition_(pos)
    , color_(color)
    , textures_()
{
    const std::vector<float> vertices = initVertices(pos, width_, height_);
    const std::vector<unsigned> indices = initElementBuffer();

    mesh_ = std::make_unique<Mesh<float>>(vertices, indices);

    createShaders();
    shader_->bind();

    shader_->setUniformVec4f("inColor", math::vec4<float>::fromArray(color.data));
}

Rectangle::Rectangle(float width, float height,
          const math::Point<float>& pos,
          const TextureBlock& textures)
    : width_(width)
    , height_(height)
    , offset_(0.0f, 0.0f)
    , initialPosition_(pos)
    , color_(std::nullopt)
    , textures_(textures)
{
    const std::vector<float> vertices   = initVertices(pos, width_, height_);
    const std::vector<float> texCoords  = initTexCoords();
    const std::vector<unsigned> indices = initElementBuffer();

    const auto data = Mesh<float>::merge(vertices, texCoords, 2, 2);

    MeshDescriptor descriptor;
    descriptor.valuesPerIndex = {2, 2};
    descriptor.offsets        = {0, 2};
    descriptor.elementBuffer  = indices;

    mesh_ = std::make_unique<Mesh<float>>(data, descriptor);

    createShaders();
    shader_->bind();
}

Rectangle::~Rectangle() = default;

void Rectangle::draw() const
{
    shader_->bind();
    shader_->setUniformVec2f("translation", offset_);
    shader_->setUniform1i("textureCount", textures_.size());

    if(color_)
    {
        shader_->setUniformVec4f("inColor", math::vec4<float>::fromArray(color_->data));
    }

    textures_.bind();

    mesh_->draw();
    shader_->setUniform1i("textureCount", 0); //clean up so non-textured items don't try to use textures
}

void Rectangle::move(const math::vec2<float>& direction)
{
    offset_.x += direction.x;
    offset_.y += direction.y;
}

void Rectangle::moveTo(const math::Point<float>& position)
{
    offset_.x = position.x - initialPosition_.x;
    offset_.y = position.y - initialPosition_.y;
}

void Rectangle::setColor(const Color& color) 
{
    color_ = color;
}

[[nodiscard]]
math::Point<float> Rectangle::position() const
{
    return initialPosition_ + offset_;
}

void Rectangle::createShaders()
{
    if(!shader_)
    {
        shader_ = std::make_unique<Shader>(vertexPath, fragmentPath);
        shader_->bind();
    }
}

}
