#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <memory>
#include <optional>
#include <vector>

#include "color.h"
#include "drawable.h"
#include "mesh.h"
#include "shader.h"
#include "texture.h"

#include "../math/point.h"
#include "../math/vec2.h"

namespace core::graphics
{
class Rectangle
{
public:
    Rectangle(float width, float height,
              const math::Point<float>& pos, 
              const Color& color);

    Rectangle(float width, float height,
              const math::Point<float>& pos,
              const TextureBlock& texture);

    ~Rectangle();

    void draw() const;
    void move(const math::vec2<float>& direction);
    void moveTo(const math::Point<float>& position);
    void setColor(const Color& color);

    [[nodiscard]]
    math::Point<float> position() const;

    float width() const { return width_; }
    float height() const { return height_; }

public:
    static void createShaders();
private:
    static std::unique_ptr<Shader> shader_;

    static const char * vertexPath;
    static const char * fragmentPath;

private:
    using vec2f     = math::vec2<float>;
    using Pointf    = math::Point<float>;
    using MeshT     = std::unique_ptr<Mesh<float>>;
    using ColorT    = std::optional<Color>;
    using TextureT  = TextureBlock;

    float        width_;
    float        height_;
    vec2f        offset_;
    const Pointf initialPosition_;
    MeshT        mesh_;
    ColorT       color_;
    TextureT     textures_;
};
}

REGISTER_DRAWABLE(core::graphics::Rectangle);

#endif //RECTANGLE_H
