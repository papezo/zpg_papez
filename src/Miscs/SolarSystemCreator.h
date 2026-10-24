#pragma once

#include <memory>
#include "Graphics/DrawableObject.h"

/*
    Additional class for creating a solar system so there's not a big mess in SceneCreator class
*/

class SolarSystemCreator
{
public:
    static auto createMoon(Camera& camera) -> std::unique_ptr<DrawableObject>;
    static auto createBlackHole(Camera& camera) -> std::unique_ptr<DrawableObject>;
    static auto createEarth(Camera& camera) -> std::unique_ptr<DrawableObject>;
    static auto createSun(Camera& camera) -> std::unique_ptr<DrawableObject>;
    static auto createMercury(Camera& camera) -> std::unique_ptr<DrawableObject>;
    static auto createVenus(Camera& camera) -> std::unique_ptr<DrawableObject>;
    static auto createMars(Camera& camera) -> std::unique_ptr<DrawableObject>;

    static auto createSignature(Camera& camera) -> std::unique_ptr<DrawableObject>;
};