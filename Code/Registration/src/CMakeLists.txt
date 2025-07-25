set(
  SimpleITKRegistrationSource
  sitkImageRegistrationMethod.cxx
  sitkImageRegistrationMethod_CreateOptimizer.cxx
  sitkImageRegistrationMethod_CreateMetric.cxx
)

set(
  use_itk_modules
  ITKCommon
  ITKLabelMap
  ITKOptimizersv4
  ITKMetricsv4
  ITKRegistrationMethodsv4
)
find_package(
  ITK
  REQUIRED
  COMPONENTS
    ${use_itk_modules}
  OPTIONAL_COMPONENTS
    GenericLabelInterpolator
)

add_library(SimpleITKRegistration ${SimpleITKRegistrationSource})
sitk_target_use_itk(SimpleITKRegistration PRIVATE ${ITK_MODULES_REQUESTED})

# The BasicFiltersLibrary is needed of the Cast filter
target_link_libraries(
  SimpleITKRegistration
  PUBLIC
    SimpleITKCommon
    SimpleITK_ITKCommon
)
if(SimpleITK_EXPLICIT_INSTANTIATION)
  target_link_libraries(SimpleITKRegistration PRIVATE SimpleITKExplicit)
endif()

target_include_directories(
  SimpleITKRegistration
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/Code/Registration/include>
    $<INSTALL_INTERFACE:${SimpleITK_INSTALL_INCLUDE_DIR}>
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_compile_options(
  SimpleITKRegistration
  PUBLIC
    ${SimpleITK_PUBLIC_COMPILE_OPTIONS}
  PRIVATE
    ${SimpleITK_PRIVATE_COMPILE_OPTIONS}
)
target_compile_features(SimpleITKRegistration PUBLIC cxx_std_17)

sitk_install_exported_target( SimpleITKRegistration )
