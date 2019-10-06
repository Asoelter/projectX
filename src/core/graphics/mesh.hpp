/*namespace core::graphics
{

template
    <
    typename T, 
    typename = std::enable_if_t<std::is_arithmetic<T>::value()>
    >
Mesh<T>::Mesh(std::vector<T>         data, 
              std::vector<unsigned>  elementBuffer,
              std::vector<unsigned>  offsets)
{
    glGenBuffers(1, &vao_);
    glGenBuffers(1, &vbo_);
    glGenBuffers(1, &ebo_);

    glBindVertexArray(vao_);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo_);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo_);

    glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(T), data.data(), GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, elementBuffer.size() * sizeof(unsigned), 
                 elementBuffer.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
}

template
    <
    typename T, 
    typename = std::enable_if_t<std::is_arithmetic<T>::value()>
    >
void Mesh<T>::draw() const
{
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

}*/
