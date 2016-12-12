#include "Bob.hpp"
Bob::Bob(SDL_Renderer*& m_renderer) : m_renderer(m_renderer) {
  // for (int i = 1; i <= bob_animation_frames; ++i) {
  bobs_frames.push_back(std::make_shared<Ball>("assets/bob_therunner.png", m_renderer));
  //}
  bobs_shadows.push_back(std::make_shared<Ball>("assets/shadow1.png", m_renderer));
  for (int i = 0; i <= shadow_frames + 1; ++i) {
    // std::cerr << i << std::endl;
    if (i != 0) {
      ball_shadows.push_back(std::make_shared<Ball>("assets/shadow" + std::to_string(i) + ".png", m_renderer));
      bobs_shadows.push_back(ball_shadows[i - 1]);
    }
    bobs_shadows[i]->set_blend_mode(SDL_BLENDMODE_BLEND);
    bobs_shadows[i]->set_alpha(shadow_blend);
  }
  for (int i = shadow_frames - 1; i >= 0; --i) {
    bobs_shadows.push_back(ball_shadows[i]);
  }
  this->gravity.process();
}

void Bob::set_jump() {
  jump = true;
  if (jump_counter) {
    ++jump_counter;
  }
}

void Bob::run() {
  SDL_Rect clip;
  clip.w = bob_dimension;
  clip.h = clip.w;
  clip.y = ((bob_animation_counter / 5) / 4) * clip.w;
  clip.x = ((bob_animation_counter / 5) % 4) * clip.w;
  if (jump) {
    float grav_pos = gravity.varGravityPositions[jump_counter];
    bobs_shadows[(jump_counter / ((gravity.m_max_frame + 1) / shadow_frames_consolidated))]->render(
        25, SCREEN_HEIGHT - 120);
    bobs_frames[0]->render(20, bob_height - gravity.varGravityPositions[jump_counter], &clip);
    ++jump_counter;
    if (jump_counter >= gravity.m_max_frame) {
      jump_counter = 0;
      jump = false;
    }
  } else {
    bobs_shadows[0]->render(25, SCREEN_HEIGHT - 120);
    // bobs_frames[bob_animation_counter / 5]->render(20, bob_height);
    bobs_frames[0]->render(20, bob_height, &clip);
  }
  // Bob counter
  bob_animation_counter++;
  bob_animation_counter %= 40;
}

void Bob::clear() {
  for (auto ball : bobs_frames) {
    if (ball) {
      ball->clear();
    }
  }
}
