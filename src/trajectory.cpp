#include <vector>
#include <pair>
#include <algorithm>

#include "trajectory.h"
#include "Integrator.h"

static bool cmpTrajPtHeight( trajPt p1, trajPt p2) { return (p1.first.pos.y < p2.second.pos.y); };

trajPt trajectory::findMaxHeight() {
  vector<trajPt>::iterator maxElem = std::max_element(points.begin(), points.end(), cmpTrajPtHeight);
  
  return *maxElem;
}
