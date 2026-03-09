#include <Geode/Geode.hpp>
#include <Geode/DefaultInclude.hpp>
using namespace geode::prelude;

$execute{
    auto result = file::createDirectory(Mod::get()->getSaveDir() / "levels");
}   