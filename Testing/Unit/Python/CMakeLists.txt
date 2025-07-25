#
# Python Tests
#
sitk_add_pytest_test(
  Test.ImageTests
  "${CMAKE_CURRENT_SOURCE_DIR}/sitkImageTests.py"
)

sitk_add_pytest_test(
  Test.BasicFiltersTests
  "${CMAKE_CURRENT_SOURCE_DIR}/sitkBasicFilterTests.py"
)

sitk_add_pytest_test(
  Test.TransformTests
  "${CMAKE_CURRENT_SOURCE_DIR}/sitkTransformTests.py"
)

sitk_add_pytest_test(
  Test.ImageIndexing
  "${CMAKE_CURRENT_SOURCE_DIR}/sitkImageIndexingTest.py"
)

sitk_add_pytest_test(
  Test.ExternalViewer
  "${CMAKE_CURRENT_SOURCE_DIR}/sitkExternalViewerTest.py"
)

sitk_add_pytest_test(
  Test.FlatStaticMethod
  "${CMAKE_CURRENT_SOURCE_DIR}/sitkFlatStaticMethod.py"
)

sitk_add_pytest_test(
  Test.GetGDCMSeriesIDs
  "${CMAKE_CURRENT_SOURCE_DIR}/sitkGetGDCMSeriesIDs.py"
)

# Numpy test.
sitk_add_pytest_test(
  Test.Numpy
  "${CMAKE_CURRENT_SOURCE_DIR}/sitkNumpyArrayConversionTest.py"
)

sitk_add_pytest_test(
  Test.ProcessObject
  "${CMAKE_CURRENT_SOURCE_DIR}/sitkProcessObjectTest.py"
)

sitk_add_pytest_test(
  Test.ConcurrentImageRead
  "${CMAKE_CURRENT_SOURCE_DIR}/ConcurrentImageRead.py"
)

sitk_add_pytest_test(
  Test.ImageReadWrite
  "${CMAKE_CURRENT_SOURCE_DIR}/sitkImageReadWrite.py"
)

if(SimpleITK_USE_ELASTIX)
  sitk_add_pytest_test(
    Test.TransformixImageFilterTest
    "${CMAKE_CURRENT_SOURCE_DIR}/sitkTransformixImageFilterTest.py"
  )
endif()

if(TEST Python.Test.ConcurrentImageRead AND APPLE)
  set_tests_properties(
    Python.Test.ConcurrentImageRead
    PROPERTIES
      LABELS
        "UNSTABLE"
  )
endif()

sitk_add_pytest_test(
  Test.ArrayView
  "${CMAKE_CURRENT_SOURCE_DIR}/sitkGetArrayViewFromImageTest.py"
)
