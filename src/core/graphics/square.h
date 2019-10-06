#ifndef SQUARE_H
#define SQUARE_H

#include <memory>

#include "../math/point.h"
#include "../math/vec2.h"

#include "../graphics/mesh.h"
#include "../graphics/shader.h"

namespace core::graphics
{
class Square
{
public:
    Square(float dimension, const math::Point<float>& pos);

    void draw() const;
    void move(const math::vec2<float>& direction);
private:
    static std::unique_ptr<Shader> shader_;
private:
    float dimension_;
    math::vec2<float> offset_;
    std::unique_ptr<Mesh<float>> mesh_;
};
}

#endif //SQUARE_H
