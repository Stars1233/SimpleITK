/*=========================================================================
*
*  Copyright NumFOCUS
*
*  Licensed under the Apache License, Version 2.0 (the "License");
*  you may not use this file except in compliance with the License.
*  You may obtain a copy of the License at
*
*         http://www.apache.org/licenses/LICENSE-2.0.txt
*
*  Unless required by applicable law or agreed to in writing, software
*  distributed under the License is distributed on an "AS IS" BASIS,
*  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
*  See the License for the specific language governing permissions and
*  limitations under the License.
*
*=========================================================================*/
%module(directors="1") SimpleITK

// Remove some warnings
#pragma SWIG nowarn=362,503,401,389,516,511

// Use STL support
%include <std_vector.i>
%include <std_string.i>
%include <std_map.i>
#if SWIGPYTHON || SWIGRUBY
%include <std_complex.i>
#endif
// Use C99 int support
%include <stdint.i>

// Use exceptions
%include "exception.i"

// Customize exception handling
%exception {
  try {
    $action
  } catch( std::exception &ex ) {
    const size_t e_size = 10240;
    char error_msg[e_size];
// TODO this should be replaces with some try compile stuff

%#ifdef _MSC_VER
    _snprintf_s( error_msg, e_size, e_size, "Exception thrown in SimpleITK $symname: %s", ex.what() );
%#else
    snprintf( error_msg, e_size, "Exception thrown in SimpleITK $symname: %s", ex.what() );
%#endif

    SWIG_exception( SWIG_RuntimeError, error_msg );
  } catch( ... ) {
    SWIG_exception( SWIG_UnknownError, "Unknown exception thrown in SimpleITK $symname" );
  }
}

// Global Tweaks to sitk::Image
%ignore itk::simple::Image::GetITKBase( void );
%ignore itk::simple::Image::GetITKBase( void ) const;

#if !defined(SWIGCSHARP)
%ignore itk::simple::Image::GetBufferAsInt8();
%ignore itk::simple::Image::GetBufferAsUInt8();
%ignore itk::simple::Image::GetBufferAsInt16();
%ignore itk::simple::Image::GetBufferAsUInt16();
%ignore itk::simple::Image::GetBufferAsInt32();
%ignore itk::simple::Image::GetBufferAsUInt32();
%ignore itk::simple::Image::GetBufferAsInt64();
%ignore itk::simple::Image::GetBufferAsUInt64();
%ignore itk::simple::Image::GetBufferAsFloat();
%ignore itk::simple::Image::GetBufferAsDouble();

%ignore itk::simple::Image::GetBufferAsInt8( ) const;
%ignore itk::simple::Image::GetBufferAsUInt8( ) const;
%ignore itk::simple::Image::GetBufferAsInt16( ) const;
%ignore itk::simple::Image::GetBufferAsUInt16( ) const;
%ignore itk::simple::Image::GetBufferAsInt32( ) const;
%ignore itk::simple::Image::GetBufferAsUInt32( ) const;
%ignore itk::simple::Image::GetBufferAsInt64( ) const;
%ignore itk::simple::Image::GetBufferAsUInt64( ) const;
%ignore itk::simple::Image::GetBufferAsFloat( ) const;
%ignore itk::simple::Image::GetBufferAsDouble( ) const;

#endif


#if !(defined(SWIGCSHARP) || defined(SWIGJAVA))
%ignore itk::simple::Image::GetBufferAsVoid();
%ignore itk::simple::Image::GetBufferAsVoid() const;
#endif


// This section is copied verbatim into the generated source code.
// Any include files, definitions, etc. need to go here.
%{
#include <SimpleITK.h>
#include <sitkImageOperators.h>

%}

%apply std::string { itk::simple::PathType };

// Help SWIG handle std vectors
namespace std
{
  %template(VectorBool) vector<bool>;
  %template(VectorUInt8) vector<uint8_t>;
  %template(VectorInt8) vector<int8_t>;
  %template(VectorUInt16) vector<uint16_t>;
  %template(VectorInt16) vector<int16_t>;
  %template(VectorUInt32) vector<uint32_t>;
  %template(VectorInt32) vector<int32_t>;
  %template(VectorUInt64) vector<uint64_t>;
  %template(VectorInt64) vector<int64_t>;
  %template(VectorFloat) vector<float>;
  %template(VectorDouble) vector<double>;
  %template(VectorOfImage) vector< itk::simple::Image >;
  %template(VectorOfTransform) vector< itk::simple::Transform >;
  %template(VectorUIntList) vector< vector<unsigned int> >;
  %template(VectorString) vector< std::string >;

  %template(DoubleDoubleMap) map<double, double>;
}

// Language Specific Sections
#if SWIGCSHARP
%include CSharp.i
#endif
#if SWIGJAVA
%include Java.i
#endif
#if SWIGTCL
%include Tcl.i
#endif
#if SWIGPYTHON
%include Python.i
#endif
#if SWIGLUA
%include Lua.i
#endif
#if SWIGR
%include R.i
#endif
#if SWIGRUBY
  %include Ruby.i
#endif


// define these preprocessor directives to nothing for the swig interface
#define SITKCommon_EXPORT
#define SITKCommon_HIDDEN
#define SITKBasicFilters0_EXPORT
#define SITKBasicFilters0_HIDDEN
#define SITKBasicFilters_EXPORT
#define SITKBasicFilters_HIDDEN
#define SITKIO_EXPORT
#define SITKIO_HIDDEN
#define SITKRegistration_EXPORT
#define SITKRegistration_HIDDEN

#define SITKElastix_EXPORT
#define SITKElastix_HIDDEN


// Any new classes need to have an "%include" statement to be wrapped.

// Common
%include "sitkConfigure.h"
%include "sitkVersion.h"
%include "sitkPathType.h"
%include "sitkPixelIDValues.h"
%include "sitkInterpolator.h"
%include "sitkImage.h"
%include "sitkObjectOwnedBase.h"
%include "sitkCommand.h"
%include "sitkLogger.h"
%include "sitkKernel.h"
%include "sitkEvent.h"
%include "sitkRandomSeed.h"

// Transforms
%include "sitkTransform.h"
%include "sitkBSplineTransform.h"
%include "sitkDisplacementFieldTransform.h"
%include "sitkAffineTransform.h"
%include "sitkEuler3DTransform.h"
%include "sitkEuler2DTransform.h"
%include "sitkScaleTransform.h"
%include "sitkScaleSkewVersor3DTransform.h"
%include "sitkComposeScaleSkewVersor3DTransform.h"
%include "sitkScaleVersor3DTransform.h"
%include "sitkSimilarity2DTransform.h"
%include "sitkSimilarity3DTransform.h"
%include "sitkTranslationTransform.h"
%include "sitkVersorTransform.h"
%include "sitkVersorRigid3DTransform.h"
%include "sitkCompositeTransform.h"


// Basic Filter Base
%include "sitkProcessObject.h"
%include "sitkImageFilter.h"

// IO
%include "sitkShow.h"
%include "sitkImageFileWriter.h"
%include "sitkImageSeriesWriter.h"
%include "sitkImageReaderBase.h"
%include "sitkImageSeriesReader.h"
%include "sitkImageFileReader.h"
%include "sitkImageViewer.h"

 // Basic Filters
%include "sitkHashImageFilter.h"
%include "sitkBSplineTransformInitializerFilter.h"
%include "sitkCenteredTransformInitializerFilter.h"
%include "sitkCenteredVersorTransformInitializerFilter.h"
%include "sitkLandmarkBasedTransformInitializerFilter.h"
%include "sitkCastImageFilter.h"
%include "sitkExtractImageFilter.h"
%include "sitkPasteImageFilter.h"
%include "sitkAdditionalProcedures.h"

#ifdef SITK_USE_ELASTIX
%{
#include <sitkElastixImageFilter.h>
#include <sitkTransformixImageFilter.h>
%}

// Elastix and Transformix
%template( ParameterMap ) std::map< std::string, std::vector< std::string > >;
%template( VectorOfParameterMap ) std::vector< std::map< std::string, std::vector< std::string > > >;
%include "sitkElastixImageFilter.h"
%include "sitkTransformixImageFilter.h"
#endif

// Registration
%include "sitkImageRegistrationMethod.h"


// Auto-generated headers
%include "SimpleITKBasicFiltersGeneratedHeaders.i"
