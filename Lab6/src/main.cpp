// #include <SFML/Graphics.hpp>
#include <camera/FPCamera.hpp>
#include <camera/TPCamera.hpp>
#include <engine/Scene.hpp>
#include <logic/EveryNSec.hpp>
#include <logic/FrameEvent.hpp>
#include <logic/IntersectEvent.hpp>
#include <logic/KeyboardEvent.hpp>
#include <objects/Cube.hpp>
#include <objects/Flat.hpp>
#include <objects/Model.hpp>
#include <random>

int getRandomInt(int min, int max) {
    static std::random_device rd; // Инициализация случайного устройства
    static std::mt19937 gen(rd()); // Генератор случайных чисел Mersenne Twister

    std::uniform_int_distribution<int> dist(
        min, max); // Распределение в диапазоне [min, max]
    return dist(gen);
}

constexpr int WIN_SCORE = 10;

int main() {
    cge::Scene scene("Snowman Building");

    sf::Image snow;
    snow.loadFromFile(
        "/home/kruyneg/Загрузки/97254d5affed41beacf00447e40beac2_obj/"
        "RGB_8fb6e0e87ae74415933749a8f0e562b1_Substance_graph_basecolor.png");
    sf::Image walltex;
    walltex.loadFromFile(
        "/home/kruyneg/Изображения/50-free-textures-4+normalmaps/179.JPG");
    cge::Flat floor("floor", snow, {0, 0, 1}, {1, 0, 0});
    floor.scale(glm::vec3(10));
    cge::Flat global_floor("floor", snow, {0, 0, 1}, {1, 0, 0});
    global_floor.translate({0, -0.01, 1});
    global_floor.scale(glm::vec3(100));

    cge::Cube wall1("wall", walltex), wall2("wall", walltex),
        wall3("wall", walltex), wall4("wall", walltex);
    wall1.scale({1, 1, 11});
    wall1.translate({-5, 0, 0});
    wall2.scale({11, 1, 1});
    wall2.translate({0, 0, 5});
    wall3.scale({1, 1, 11});
    wall3.translate({5, 0, 0});
    wall4.scale({11, 1, 1});
    wall4.translate({0, 0, -5});

    cge::Model character(
        "/home/kruyneg/Загрузки/uploads_files_4174453_textures/"
        "uploads_files_4174453_Snowman.obj");
    // cge::Camera cam(glm::vec3(-2, 1, -2), glm::vec3(0));
    cge::CameraSettings custom = cge::CameraSettings::Default;
    // custom.ortho = true;
    cge::TPCamera cam(10.0f, custom);
    // cge::Model character("/home/kruyneg/Загрузки/"
    //                 "97254d5affed41beacf00447e40beac2_obj/model.obj");
    // character.scale(glm::vec3(0.01));

    cge::Model snowflake(
        "/home/kruyneg/Загрузки/uploads_files_4202298_Snowflake/Snowflake.obj");
    snowflake.translate({1, 4, 0});

    cam.bind(&character);

    character.translate({0, -character.getBoundingBox().first.y, 0});

    uint score = 0;
    cge::FrameEvent falling([&snowflake]() {
        // Получаем текущую позицию снежинки
        auto pos = snowflake.getPosition();

        // Сначала смещаем снежинку вниз в мировой системе координат

        // Затем выполняем вращение вокруг её собственной оси
        // snowflake.translate(-pos); // Перемещаем снежинку к началу координат
        // snowflake.rotateY(glm::radians(5.0f)); // Вращаем вокруг оси Y
        // snowflake.translate(pos); // Возвращаем снежинку обратно на место
        snowflake.translate(glm::vec3{0, -0.05, 0});
    });
    cge::IntersectEvent fall_to_floor(
        &global_floor, &snowflake, [&score, &global_floor, &snowflake]() {
            if (score < WIN_SCORE) {
                auto oldpos = snowflake.getPosition();
                snowflake.translate(-oldpos);
                snowflake.translate(
                    {getRandomInt(-4, 4), 10, getRandomInt(-4, 4)});
            }
        });
    cge::IntersectEvent character_catch(
        &character, &snowflake, [&snowflake, &character, &score]() {
            if (score < WIN_SCORE) {
                auto oldpos = snowflake.getPosition();
                snowflake.translate(-oldpos);
                snowflake.translate(
                    {getRandomInt(-4, 4), 10, getRandomInt(-4, 4)});
                character.scale(glm::vec3(1.1));
                ++score;
            }
        });

    cge::IntersectEvent check_wall1(&character, &wall1, [&character, &wall1]() {
        auto depth = cge::intersectionDepth(character.getBoundingBox(),
                                            wall1.getBoundingBox());
        glm::vec3 correction(0.0f);
        correction.x = depth.x;
        character.translate(correction);
    });
    cge::IntersectEvent check_wall2(&character, &wall2, [&character, &wall2]() {
        auto depth = cge::intersectionDepth(character.getBoundingBox(),
                                            wall2.getBoundingBox());
        glm::vec3 correction(0.0f);
        correction.z = depth.z;
        character.translate(-correction);
    });
    cge::IntersectEvent check_wall3(&character, &wall3, [&character, &wall3]() {
        auto depth = cge::intersectionDepth(character.getBoundingBox(),
                                            wall3.getBoundingBox());
        glm::vec3 correction(0.0f);
        correction.x = depth.x;
        character.translate(-correction);
    });
    cge::IntersectEvent check_wall4(&character, &wall4, [&character, &wall4]() {
        auto depth = cge::intersectionDepth(character.getBoundingBox(),
                                            wall4.getBoundingBox());
        glm::vec3 correction(0.0f);
        correction.z = depth.z;
        character.translate(correction);
    });

    cge::KeyboardEvent move1(sf::Keyboard::W, [&cam, &character]() {
        auto scale = character.getScale();
        character.scale(1.0f / character.getScale());
        auto dir = cam.getDirection();
        dir = glm::normalize(glm::vec3{dir.x, 0, dir.z});
        character.translate(dir * 0.1f);
        character.scale(scale);
    });
    cge::KeyboardEvent move2(sf::Keyboard::A, [&cam, &character]() {
        auto scale = character.getScale();
        character.scale(1.0f / character.getScale());
        auto dir = cam.getDirection();
        dir = glm::normalize(glm::vec3{dir.x, 0, dir.z});
        dir = glm::vec3(
            glm::rotate(glm::mat4(1), glm::radians(90.0f), glm::vec3(0, 1, 0)) *
            glm::vec4(dir, 1));
        character.translate(dir * 0.1f);
        character.scale(scale);
    });
    cge::KeyboardEvent move3(sf::Keyboard::S, [&cam, &character]() {
        auto scale = character.getScale();
        character.scale(1.0f / character.getScale());
        auto dir = cam.getDirection();
        dir = glm::normalize(glm::vec3{dir.x, 0, dir.z});
        dir = glm::vec3(glm::rotate(glm::mat4(1), glm::radians(180.0f),
                                    glm::vec3(0, 1, 0)) *
                        glm::vec4(dir, 1));
        character.translate(dir * 0.1f);
        character.scale(scale);
    });
    cge::KeyboardEvent move4(sf::Keyboard::D, [&cam, &character]() {
        auto scale = character.getScale();
        character.scale(1.0f / character.getScale());
        auto dir = cam.getDirection();
        dir = glm::normalize(glm::vec3{dir.x, 0, dir.z});
        dir = glm::vec3(glm::rotate(glm::mat4(1), glm::radians(-90.0f),
                                    glm::vec3(0, 1, 0)) *
                        glm::vec4(dir, 1));
        character.translate(dir * 0.1f);
        character.scale(scale);
    });

    cge::MouseEvent me([&cam](float ox, float oy, float zoom) {
        cam.processMouse(ox, oy);
        cam.processZoom(zoom);
    });

    cge::Event winning{[&score]() { return score >= WIN_SCORE; },
                       [&scene]() {
                           scene.background({getRandomInt(0, 255),
                                             getRandomInt(0, 255),
                                             getRandomInt(0, 255)});
                       }};

    cge::DirectLight sky_light({0, -0.5, -0.5}, glm::uvec3{250, 250, 255} / 2u);
    cge::PointLight l({0, 3, 0}, glm::uvec3(255));

    scene.add(floor)
        .add(global_floor)
        .add(character)
        .add(sky_light)
        .add(sky_light)
        // .add(l)
        .add(wall1)
        .add(wall2)
        .add(wall3)
        .add(wall4)
        .add(snowflake)
        .use(cam)
        .background({200, 200, 255})
        .handle(falling)
        .handle(fall_to_floor)
        .handle(character_catch)
        .handle(move1)
        .handle(move2)
        .handle(move3)
        .handle(move4)
        .handle(check_wall1)
        .handle(check_wall2)
        .handle(check_wall3)
        .handle(check_wall4)
        .handle(winning)
        .handle(me);

    scene.run();
}