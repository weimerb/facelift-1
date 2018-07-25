facelift_add_interface(BenchmarkModelInterface INTERFACE_DEFINITION_FOLDER ${CMAKE_CURRENT_SOURCE_DIR}/interface)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

facelift_add_qml_plugin(BenchmarkModelsPluginCpp
   URI benchmark.models
   OUTPUT_BASE_DIRECTORY imports/cpp
   SOURCES plugin/BenchmarkModelsPlugin.cpp
   HEADERS plugin/BenchmarkModelsPlugin.h
   LINK_LIBRARIES BenchmarkModelInterface
)
