#pragma once
#include <string>

const float TO_PIXEL = 245;
const int NUM_PLANETS = 4;

std::string PLANETS[NUM_PLANETS] = { "Mercury", "Venus", "Earth", "Mars" };

float PLANETS_DISTANCE[NUM_PLANETS] = { 0.4f, 0.72f, 1.0f, 1.5f };

double PLANETS_DURATION[NUM_PLANETS] = { 87.97f, 224.65f, 365.0f, 687.0f };

float MOVEMENT_SPEED = 10000.0f;