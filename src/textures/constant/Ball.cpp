#include "Ball.hpp"

Ball::Ball(std::string path, SDL_Renderer*& m_renderer) : Texture(path, m_renderer) {
}

Ball::Ball(SDL_Renderer*& m_renderer) : Texture(m_renderer) {
}

Ball::~Ball() {
}
