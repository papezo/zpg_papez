#include "Models/SolarSystem/moon.h"
#include "Models/SolarSystem/earth.h"
#include "Models/SolarSystem/mercury_vertices.h"
#include "Models/SolarSystem/venus_vertices.h"
#include "Models/SolarSystem/mars_vertices.h"
#include "Models/SolarSystem/sun.h"
#include "Models/SolarSystem/black_hole_vertices.h"
#include "Models/PAP0123.h"

#include "Graphics/Scene.h"
#include "Graphics/Model.h"
#include "Graphics/DrawableObject.h"

#include "Transformations/CompositeTransform.h"
#include "Transformations/StaticTransformations.h"
#include "Transformations/DynamicRotate.h"

#include "SolarSystemCreator.h"

auto SolarSystemCreator::createSignature(Camera& camera) -> std::unique_ptr<DrawableObject>
{
    auto signatureModel = std::make_shared<Model>(login, sizeof(login) / sizeof(float), 6);
    auto signatureShader = std::make_shared<ShaderProgram>("Shaders/basic.vert", "Shaders/basic.frag");

    camera.addObserver(signatureShader);

    auto signObject = std::make_unique<DrawableObject>(signatureModel, signatureShader);
    auto composite = std::make_shared<CompositeTransform>();

    composite->add(std::make_shared<Translate>(1400.0f, 0.0f, -3000.0f));
    composite->add(std::make_shared<Scale>(400.0f));

    signObject->setTransformation(composite);
    return signObject;
}

auto SolarSystemCreator::createMoon(Camera& camera) -> std::unique_ptr<DrawableObject>
{
    auto moonModel = std::make_shared<Model>(moon, sizeof(moon) / sizeof(float), 9);
    auto moonShader = std::make_shared<ShaderProgram>("Shaders/Lighting/lighting_diffPos.vert", "Shaders/Lighting/phong.frag");

    moonShader->use();
    moonShader->setUniform("lightPosition", 0.0f, 0.0f, 0.0f);
    moonShader->setUniform("lightColor", 1.0f, 1.0f, 1.0f);
    moonShader->setUniform("shiness", 32.0);

    camera.addObserver(moonShader);

    auto moonObject = std::make_unique<DrawableObject>(moonModel, moonShader);

    auto composite = std::make_shared<CompositeTransform>();

    // this has to be same as first rotation of earth!
    // its for moon to rotate same as earth by the sun
    composite->add(std::make_shared<DynamicRotate>(0.0f, 0.1f, glm::vec3(0.0f, 1.0f, 0.0f)));
    composite->add(std::make_shared<Translate>(700.0f, 0.0f, 0.0f)); // earth & sun distance
    composite->add(std::make_shared<DynamicRotate>(0.0f, 0.1f, glm::vec3(0.0f, 1.0f, 0.0f)));  // Moon & Earth rotation
    composite->add(std::make_shared<Translate>(150.0f, 0.0f, 0.0f)); // Moon & sun distance
    composite->add(std::make_shared<Scale>(15.0f));

    moonObject->setTransformation(composite);

    return moonObject;
}

auto SolarSystemCreator::createBlackHole(Camera& camera) -> std::unique_ptr<DrawableObject>
{
    auto blackHoleMod = std::make_shared<Model>(blackHoleVertices, sizeof(blackHoleVertices) / sizeof(float), 9);
    auto blackHoleShader = std::make_shared<ShaderProgram>("Shaders/planet.vert", "Shaders/planet.frag");

    camera.addObserver(blackHoleShader);

    auto blackHoleObj = std::make_unique<DrawableObject>(blackHoleMod, blackHoleShader);
    auto composite = std::make_shared<CompositeTransform>();

    composite->add(std::make_shared<Translate>(0.0f, 120.0f, -3000.0f));
    composite->add(std::make_shared<DynamicRotate>(0.0f, 0.1f, glm::vec3(0.0f, 0.0f, 1.0f)));

    composite->add(std::make_shared<Scale>(1000.0f));
    blackHoleObj->setTransformation(composite);

    return blackHoleObj;
}


auto SolarSystemCreator::createEarth(Camera& camera) -> std::unique_ptr<DrawableObject>
{
    auto earthModel = std::make_shared<Model>(earth, sizeof(earth) / sizeof(float), 9);
    auto earthShader = std::make_shared<ShaderProgram>("Shaders/Lighting/lighting_diffPos.vert", "Shaders/Lighting/phong.frag");

    earthShader->use();
    earthShader->setUniform("lightPosition", 0.0f, 0.0f, 0.0f);
    earthShader->setUniform("lightColor", 1.0f, 1.0f, 1.0f);
    earthShader->setUniform("shiness", 32.0);

    camera.addObserver(earthShader);

    auto earthObject = std::make_unique<DrawableObject>(earthModel, earthShader);

    auto composite = std::make_shared<CompositeTransform>();

    composite->add(std::make_shared<DynamicRotate>(0.0f, 0.1f, glm::vec3(0, 1, 0)));// Earth & Sun rotation
    composite->add(std::make_shared<Translate>(700.0f, 0.0f, 0.0f));
    composite->add(std::make_shared<DynamicRotate>(0.0f, 0.1f, glm::vec3(0, 1, 0))); // Earth rotation by its axis
    composite->add(std::make_shared<Scale>(20.0f));

    earthObject->setTransformation(composite);

    return earthObject;
}

auto SolarSystemCreator::createSun(Camera& camera) -> std::unique_ptr<DrawableObject>
{
    auto sunModel = std::make_shared<Model>(sun, sizeof(sun) / sizeof(float), 9);
    auto sunShader = std::make_shared<ShaderProgram>("Shaders/basic.vert", "Shaders/basic.frag");

    camera.addObserver(sunShader);

    auto sunObject = std::make_unique<DrawableObject>(sunModel, sunShader);

    auto composite = std::make_shared<CompositeTransform>();

    composite->add(std::make_shared<Translate>(0.0f, 0.0f, 0.0f));
    composite->add(std::make_shared<DynamicRotate>(0.0f, 0.2f, glm::vec3(0.0f, 1.0f, 0.0f)));
    composite->add(std::make_shared<Scale>(50.0f));

    sunObject->setTransformation(composite);

    return sunObject;
}

auto SolarSystemCreator::createMercury(Camera& camera) -> std::unique_ptr<DrawableObject> {
    auto mercuryModel = std::make_shared<Model>(mercury, sizeof(mercury) / sizeof(float), 9);
    auto mercuryShader = std::make_shared<ShaderProgram>("Shaders/Lighting/lighting.vert", "Shaders/Lighting/phong.frag");

    mercuryShader->use();
    mercuryShader->setUniform("lightPosition", 0.0f, 0.0f, 0.0f);
    mercuryShader->setUniform("lightColor", 1.0f, 1.0f, 1.0f);
    mercuryShader->setUniform("shiness", 32.0);

    camera.addObserver(mercuryShader);

    auto mercuryObj = std::make_unique<DrawableObject>(mercuryModel, mercuryShader);

    auto composite = std::make_shared<CompositeTransform>();

    composite->add(std::make_shared<DynamicRotate>(0.0f, 0.4f, glm::vec3(0, 1, 0)));

    composite->add(std::make_shared<Translate>(200.0f, 0.0f, 0.0f));

    // rotation by its own axis
    composite->add(std::make_shared<DynamicRotate>(0.0f, 0.03f, glm::vec3(0, 1, 0)));

    composite->add(std::make_shared<Rotate>(80.0f, glm::vec3(1, 0, 0)));

    composite->add(std::make_shared<Scale>(15.0f));
    mercuryObj->setTransformation(composite);

    return mercuryObj;
}

auto SolarSystemCreator::createVenus(Camera& camera) -> std::unique_ptr<DrawableObject> {
    auto venusModel = std::make_shared<Model>(venus, sizeof(venus) / sizeof(float), 9);
    auto venusShader = std::make_shared<ShaderProgram>("Shaders/Lighting/lighting.vert", "Shaders/Lighting/phong.frag");

    venusShader->use();
    venusShader->setUniform("lightPosition", 0.0f, 0.0f, 0.0f);
    venusShader->setUniform("lightColor", 1.0f, 1.0f, 1.0f);
    venusShader->setUniform("shiness", 32.0);

    camera.addObserver(venusShader);

    auto venusObj = std::make_unique<DrawableObject>(venusModel, venusShader);

    auto composite = std::make_shared<CompositeTransform>();

    composite->add(std::make_shared<DynamicRotate>(0.0f, 0.16f, glm::vec3(0, 1, 0)));
    composite->add(std::make_shared<Translate>(400.0f, 0.0f, 0.0f));
    composite->add(std::make_shared<DynamicRotate>(0.0f, 0.16f, glm::vec3(0, 1, 0)));
    composite->add(std::make_shared<Rotate>(80.0f, glm::vec3(1, 0, 0)));

    composite->add(std::make_shared<Scale>(20.0f));

    venusObj->setTransformation(composite);

    return venusObj;
}

auto SolarSystemCreator::createMars(Camera& camera) -> std::unique_ptr<DrawableObject> {
    auto marsModel = std::make_shared<Model>(mars, sizeof(mars) / sizeof(float), 9);
    auto marsShader = std::make_shared<ShaderProgram>("Shaders/Lighting/lighting.vert", "Shaders/Lighting/phong.frag");
    camera.addObserver(marsShader);

    marsShader->use();
    marsShader->setUniform("lightPosition", 0.0f, 0.0f, 0.0f);
    marsShader->setUniform("lightColor", 1.0f, 1.0f, 1.0f);
    marsShader->setUniform("shiness", 32.0);

    auto marsObj = std::make_unique<DrawableObject>(marsModel, marsShader);

    auto composite = std::make_shared<CompositeTransform>();

    composite->add(std::make_shared<DynamicRotate>(0.0f, 0.053f, glm::vec3(0, 1, 0)));

    composite->add(std::make_shared<Translate>(1000.0f, 0.0f, 0.0f));

    composite->add(std::make_shared<DynamicRotate>(0.0f, 0.5f, glm::vec3(0, 1, 0)));
    composite->add(std::make_shared<Rotate>(80.0f, glm::vec3(1, 0, 0)));

    composite->add(std::make_shared<Scale>(20.0f));
    marsObj->setTransformation(composite);

    return marsObj;
}
