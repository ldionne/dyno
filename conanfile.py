import conans

class Dyno(conans.ConanFile):
  settings = "os", "compiler", "build_type", "arch"
  requires = "boost_hana/1.66.0@bincrafters/stable", "boost_callable_traits/1.66.0@bincrafters/stable"

  def imports(self):
    self.copy("*.hpp", dst="include", src="include")

  def build(self):
    cmake = conans.CMake(self)
    cmake.configure()
    cmake.build()
