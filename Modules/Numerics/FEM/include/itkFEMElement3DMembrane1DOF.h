/*=========================================================================
*
* Copyright Insight Software Consortium
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
* http://www.apache.org/licenses/LICENSE-2.0.txt
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*
*=========================================================================*/

#ifndef itkFEMElement3DMembrane1DOF_h
#define itkFEMElement3DMembrane1DOF_h

#include "itkFEMElementBase.h"
#include "itkFEMMaterialLinearElasticity.h"

namespace itk
{
namespace fem
{
/**
 * \class Element3DMembrane1DOF
 * \brief Class that is used to define a membrane energy problem in 3D space.
 *
 * This class only defines the physics of the problem. Use his class together
 * with element classes that specify the geometry to fully define the element.
 *
 * You can specify one template parameter:
 *
 *   TBaseClass - Class from which Element3DMembrane1DOF is derived. TBaseClass must
 *                be derived from the Element base class. This enables you
 *                to use this class at any level of element definition.
 *                If not specified, it defaults to the Element base class.
 * \ingroup ITKFEM
 */
template <typename TBaseClass = Element>
class ITKFEM_TEMPLATE_EXPORT Element3DMembrane1DOF : public TBaseClass
{
public:
  /** Standard class typedefs. */
  typedef Element3DMembrane1DOF    Self;
  typedef TBaseClass               Superclass;
  typedef SmartPointer<Self>       Pointer;
  typedef SmartPointer<const Self> ConstPointer;

  /** Run-time type information (and related methods). */
  itkTypeMacro(Element3DMembrane1DOF, TBaseClass);

  // Repeat the required typedefs and enums from parent class
  typedef typename Superclass::Float      Float;
  typedef typename Superclass::MatrixType MatrixType;
  typedef typename Superclass::VectorType VectorType;

  /**
   * Default constructor only clears the internal storage
   */
  Element3DMembrane1DOF();

  // ////////////////////////////////////////////////////////////////////////
  /*
   * Methods related to the physics of the problem.
   */

  /**
   * Compute the B matrix.
   */
  virtual void GetStrainDisplacementMatrix(MatrixType & B, const MatrixType & shapeDgl) const ITK_OVERRIDE;

  /**
   * Compute the D matrix.
   */
  virtual void GetMaterialMatrix(MatrixType & D) const ITK_OVERRIDE;

  /**
   * Compute the mass matrix specific for 3D membrane problems.
   */
  void GetMassMatrix(MatrixType & Me) const ITK_OVERRIDE;

  /**
   * 3D membrane elements have 3 DOFs per node.
   */
  virtual unsigned int GetNumberOfDegreesOfFreedomPerNode(void) const ITK_OVERRIDE
  {
    return 3;
  }

  /** Get the Stiffness matrix */
  virtual void GetStiffnessMatrix(MatrixType & Ke) const ITK_OVERRIDE;

  /**
   * Get/Set the material properties for the element
   */
  virtual Material::ConstPointer GetMaterial(void) const ITK_OVERRIDE
  {
    return dynamic_cast<const Material *>(m_Mat.GetPointer());
  }

  virtual void SetMaterial(Material::ConstPointer mat_) ITK_OVERRIDE
  {
    m_Mat =
      dynamic_cast<const MaterialLinearElasticity *>( mat_.GetPointer() );
  }

protected:

  virtual void PrintSelf(std::ostream& os, Indent indent) const ITK_OVERRIDE;

  /**
   * Pointer to material properties of the element
   */
  MaterialLinearElasticity::ConstPointer m_Mat;

};  // class Element3DMembrane1DOF

}
}  // end namespace itk::fem

#ifndef ITK_MANUAL_INSTANTIATION
#include "itkFEMElement3DMembrane1DOF.hxx"
#endif

#endif  // #ifndef itkFEMElement3DMembrane1DOF_h
