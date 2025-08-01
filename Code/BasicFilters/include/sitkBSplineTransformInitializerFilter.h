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
#ifndef sitkBSplineTransformInitializerFilter_h
#define sitkBSplineTransformInitializerFilter_h

/*
 * WARNING: DO NOT EDIT THIS FILE!
 * THIS FILE IS AUTOMATICALLY GENERATED BY THE SIMPLEITK BUILD PROCESS.
 * Please look at sitkImageFilterTemplate.h.in to make changes.
 */

#include <memory>

#include "sitkBasicFilters.h"
#include "sitkImageFilter.h"
#include "sitkBSplineTransform.h"

namespace itk::simple
{

/**\class BSplineTransformInitializerFilter
\brief BSplineTransformInitializerFilter is a helper class intended to
initialize the control point grid such that it has a physically
consistent definition. It sets the transform domain origin, physical
dimensions and direction from information obtained from the image. It
also sets the mesh size if asked to do so by calling
SetTransformDomainMeshSize() before calling InitializeTransform().

\author Luis Ibanez Nick Tustison
\sa itk::simple::BSplineTransformInitializer for the procedural interface
\sa itk::BSplineTransformInitializer for the Doxygen on the original ITK class.
 */
class SITKBasicFilters_EXPORT BSplineTransformInitializerFilter : public ProcessObject
{
public:
  using Self = BSplineTransformInitializerFilter;

  /** Default Constructor that takes no arguments and initializes
   * default parameters */
  BSplineTransformInitializerFilter();

  /** Destructor */
  ~BSplineTransformInitializerFilter() override;

  /** Define the pixels types supported by this filter */
  using PixelIDTypeList = AllPixelIDTypeList;


  /**
   * Allow the user to set the mesh size of the transform via the initializer even though the initializer does not do
   * anything with that information. Default = 1^ImageDimension.
   */
  void
  SetTransformDomainMeshSize(const std::vector<uint32_t> & TransformDomainMeshSize)
  {
    this->m_TransformDomainMeshSize = TransformDomainMeshSize;
  }

  /**
   */
  std::vector<uint32_t>
  GetTransformDomainMeshSize() const
  {
    return this->m_TransformDomainMeshSize;
  }

  /**
   * The order of the bspline in the output BSplineTransform. This
   * value effects the number of control points.
   */
  void
  SetOrder(unsigned int order)
  {
    this->m_Order = order;
  }
  unsigned int
  GetOrder() const
  {
    return this->m_Order;
  }

  /** Name of this class */
  std::string
  GetName() const override
  {
    return std::string("BSplineTransformInitializerFilter");
  }

  /** Print ourselves out */
  std::string
  ToString() const override;


  /** Execute the filter on the input image */
  BSplineTransform
  Execute(const Image & image1);

private:
  /** Setup for member function dispatching */

  typedef BSplineTransform (Self::*MemberFunctionType)(const Image & image1);
  template <class TImageType>
  BSplineTransform
  ExecuteInternal(const Image & image1);
  template <unsigned int NDimension, unsigned int NOrder>
  BSplineTransform
  ExecuteInternalWithOrder(const Image & image1);


  friend struct detail::MemberFunctionAddressor<MemberFunctionType>;

  static const detail::MemberFunctionFactory<MemberFunctionType> &
  GetMemberFunctionFactory();

  std::vector<uint32_t> m_TransformDomainMeshSize{ std::vector<uint32_t>(3, 1u) };
  unsigned int          m_Order{ 3u };
};


/**
 * \brief BSplineTransformInitializerFilter is a helper class
 * intended to initialize the control point grid such that it has
 * a physically consistent definition. It sets the transform
 * domain origin, physical dimensions and direction from
 * information obtained from the image. It also sets the mesh size
 * if asked to do so by calling SetTransformDomainMeshSize() before
 * calling InitializeTransform().
 *
 * This function directly calls the execute method of BSplineTransformInitializerFilter
 * in order to support a procedural API
 *
 * \sa itk::simple::BSplineTransformInitializerFilter for the object oriented interface
 */
SITKBasicFilters_EXPORT BSplineTransform
BSplineTransformInitializer(const Image &                 image1,
                            const std::vector<uint32_t> & transformDomainMeshSize = std::vector<uint32_t>(3, 1u),
                            unsigned int                  order = 3u);

} // namespace itk::simple
#endif
