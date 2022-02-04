from conans import ConanFile

class CaptainAsteroidConan(ConanFile):
    name = "CaptainAsteroid"
    version = "0.1"
    requires = (
        "fmt/[>=8.0.1]",
        "spdlog/[>=1.9.2]",
        "entityx/[>=1.3.0]"
    )
    settings = "os", "compiler", "arch", "build_type"
    exports = "*"
    generators = "cmake_find_package_multi"
    build_policy = "missing"
