#pragma once
#include "opencv2/core.hpp"
#include <vector>
#include <utility>

extern const double fovHoriz;
extern const double fovVert;
extern const cv::Size goalSz;

typedef std::pair< double, std::vector<cv::Point> > scoredContour;

extern std::vector<scoredContour> boulder_pipeline(cv::Mat input, bool suppress_output=false, bool window_output=false);
extern cv::Mat boulder_preprocess_pipeline(cv::Mat input, bool suppress_output=false, bool live_output=false);

extern cv::Mat goal_preprocess_pipeline(cv::Mat input, bool suppress_output=false, bool live_output=false);
extern scoredContour goal_pipeline(cv::Mat input, bool suppress_output=false, bool window_output=false);

extern double goal_pipeline_full(cv::Mat input);

extern double getDistance(cv::Size targetSize, cv::Size fovSize);
extern double getDistance(double observedHeight, double targetHeight, double frameHeight, double fovAngle);
extern double getAngleOffCenter(double midpointX, double frameWidth, double fovAngle);
extern double getFOVAngleHoriz(cv::Size observedSize, cv::Size targetSize, cv::Size fovSize, double distance);
extern double getFOVAngleVert(cv::Size observedSize, cv::Size targetSize, cv::Size fovSize, double distance);
