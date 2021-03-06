#include "Gravity.hpp"
Gravity::Gravity() { process(); }
void Gravity::process() {
  int frame = 0;
  float u = INIT_SPEED;
  float v;
  float acceleration = -20.0;
  float timem;
  float timDivider = 6;
  int loops;
  while (true) {
    timem = ((float)frame / timDivider);
    v = u + (acceleration * timem);
    float position = ((v * v) - (u * u)) / (2 * acceleration);
    position *= distanceMul;
    if (position > maxDist) {
      maxDist = position; 
    }
    if (v <= (-1 * u)) {
      break;
      /*increment floating point*/
    }
    ++frame;
  }
  loops = frame;
  m_max_frame = (int)(frame);
  varGravityPositions = new float[frame];
  u = INIT_SPEED;
  for (int i = 0; i < loops; i++) {
    timem = ((float)i / timDivider);
    v = u + (acceleration * timem);
    float position = ((v * v) - (u * u)) / (2 * acceleration);
    if (position == -0) {
      position = 0;
    }
    /*Scaling distance*/
    position *= distanceMul;
    if (position < 0) {
      std::cerr << "Position: " << position  << " lower than expected. Error" << std::endl;
    }
    varGravityPositions[i] = position;
  }
}
