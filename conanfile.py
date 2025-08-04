from conan import ConanFile

class MyProjectConan(ConanFile):
    name = "MyProject"
    version = "0.1"
    settings = "os", "arch", "compiler", "build_type"
    
    requires = [
        "glfw/3.4",
        "glad/0.1.36",
        "stb/cci.20240531",
        "glm/1.0.1"
    ]

    generators = ["CMakeDeps", "CMakeToolchain"]

    def layout(self):
        self.folders.source = "."
        #self.folders.build = "build"

