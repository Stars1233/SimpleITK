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
#include "sitkEuler3DTransform.h"
#include "sitkTransformHelper.hxx"

#include "itkEuler3DTransform.h"

namespace itk::simple
{

Euler3DTransform::~Euler3DTransform() = default;

// construct identity
Euler3DTransform::Euler3DTransform()
  : Transform(3, sitkEuler)
{
  Self::InternalInitialization(Self::GetITKBase());
}

Euler3DTransform::Euler3DTransform(const std::vector<double> & fixedCenter,
                                   double                      angleX,
                                   double                      angleY,
                                   double                      angleZ,
                                   const std::vector<double> & translation)
  : Transform(3, sitkEuler)

{
  Self::InternalInitialization(Self::GetITKBase());

  this->SetCenter(fixedCenter);
  this->SetRotation(angleX, angleY, angleZ);
  this->SetTranslation(translation);
}

Euler3DTransform::Euler3DTransform(const Euler3DTransform & arg)
  : Transform(arg)
{
  Self::InternalInitialization(Self::GetITKBase());
}

Euler3DTransform::Euler3DTransform(const Transform & arg)
  : Transform(arg)
{
  Self::InternalInitialization(Self::GetITKBase());
}


Euler3DTransform &
Euler3DTransform::operator=(const Euler3DTransform & arg)
{
  Superclass::operator=(arg);
  return *this;
}


/** fixed parameter */
void
Euler3DTransform::SetCenter(const std::vector<double> & params)
{
  this->MakeUnique();
  this->m_pfSetCenter(params);
}

std::vector<double>
Euler3DTransform::GetCenter() const
{
  return this->m_pfGetCenter();
}

double
Euler3DTransform::GetAngleX() const
{
  return this->m_pfGetAngleX();
}

double
Euler3DTransform::GetAngleY() const
{
  return this->m_pfGetAngleY();
}

double
Euler3DTransform::GetAngleZ() const
{
  return this->m_pfGetAngleZ();
}

/** parameter */
void
Euler3DTransform::SetRotation(double angleX, double angleY, double angleZ)
{
  this->MakeUnique();
  this->m_pfSetRotation(angleX, angleY, angleZ);
}

void
Euler3DTransform::SetTranslation(const std::vector<double> & params)
{
  this->MakeUnique();
  this->m_pfSetTranslation(params);
}

std::vector<double>
Euler3DTransform::GetTranslation() const
{
  return this->m_pfGetTranslation();
}


void
Euler3DTransform::SetComputeZYX(bool _arg)
{
  this->MakeUnique();
  this->m_pfSetComputeZYX(_arg);
}

bool
Euler3DTransform::GetComputeZYX() const
{
  return this->m_pfGetComputeZYX();
}

std::vector<double>
Euler3DTransform::GetMatrix() const
{
  return this->m_pfGetMatrix();
}

void
Euler3DTransform::SetMatrix(const std::vector<double> & params, double tolerance)
{
  this->MakeUnique();
  this->m_pfSetMatrix(params, tolerance);
}

void
Euler3DTransform::SetPimpleTransform(std::unique_ptr<PimpleTransformBase> && pimpleTransform)
{
  Superclass::SetPimpleTransform(std::move(pimpleTransform));
  Self::InternalInitialization(this->GetITKBase());
}

void
Euler3DTransform::InternalInitialization(itk::TransformBase * transform)
{

  using TransformType = itk::Euler3DTransform<double>;
  TransformType * t = dynamic_cast<TransformType *>(transform);

  // explicitly remove all function pointer with reference to prior transform
  this->m_pfSetCenter = nullptr;
  this->m_pfGetCenter = nullptr;
  this->m_pfSetTranslation = nullptr;
  this->m_pfGetTranslation = nullptr;
  this->m_pfSetRotation = nullptr;
  this->m_pfGetAngleX = nullptr;
  this->m_pfGetAngleY = nullptr;
  this->m_pfGetAngleZ = nullptr;
  this->m_pfSetComputeZYX = nullptr;
  this->m_pfGetComputeZYX = nullptr;
  this->m_pfGetMatrix = nullptr;
  this->m_pfSetMatrix = nullptr;

  if (t && (typeid(*t) == typeid(TransformType)))
  {
    this->InternalInitialization(t);
    return;
  }
  else
  {
    sitkExceptionMacro("Transform is not of type " << this->GetName() << "!");
  }
}


template <class TransformType>
void
Euler3DTransform::InternalInitialization(TransformType * t)
{
  SITK_TRANSFORM_SET_MPF(Center, typename TransformType::InputPointType, double);
  SITK_TRANSFORM_SET_MPF(Translation, typename TransformType::OutputVectorType, double);
  SITK_TRANSFORM_SET_MPF_GetMatrix();
  SITK_TRANSFORM_SET_MPF_SetMatrix();

  this->m_pfSetRotation = [t](auto && PH1, auto && PH2, auto && PH3) {
    t->SetRotation(
      std::forward<decltype(PH1)>(PH1), std::forward<decltype(PH2)>(PH2), std::forward<decltype(PH3)>(PH3));
  };
  this->m_pfGetAngleX = [t] { return t->GetAngleX(); };
  this->m_pfGetAngleY = [t] { return t->GetAngleY(); };
  this->m_pfGetAngleZ = [t] { return t->GetAngleZ(); };
  this->m_pfSetComputeZYX = [t](auto && PH1) { t->SetComputeZYX(std::forward<decltype(PH1)>(PH1)); };
  this->m_pfGetComputeZYX = [t] { return t->GetComputeZYX(); };
}

} // namespace itk::simple
