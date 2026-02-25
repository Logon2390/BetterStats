#include <Geode/Geode.hpp>
using namespace geode::prelude;

$execute{
    auto result = file::createDirectory(Mod::get()->getSaveDir() / "levels");
}   