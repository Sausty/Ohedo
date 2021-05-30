#ifndef OHEDO_NOISE_H
#define OHEDO_NOISE_H

#include <Ohedo/Utils/Types.h>

void Ohedo_NoiseSeed(i32 seed);
i32 Ohedo_Noise2(i32 x, i32 y);
f32 Ohedo_Lerp(f32 x, f32 y, f32 s);
f32 Ohedo_SmoothInterpolation(f32 x, f32 y, f32 s);
f32 Ohedo_Noise2D(f32 x, f32 y);
f32 Ohedo_Perlin2D(f32 x, f32 y, f32 freq, i32 depth);

#endif