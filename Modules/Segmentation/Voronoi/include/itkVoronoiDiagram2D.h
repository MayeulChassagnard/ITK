/*=========================================================================
 *
 *  Copyright Insight Software Consortium
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
#ifndef itkVoronoiDiagram2D_h
#define itkVoronoiDiagram2D_h


#include "itkMesh.h"
#include "itkDefaultDynamicMeshTraits.h"
#include "itkPolygonCell.h"
#include <vector>

namespace itk
{
/** \class VoronoiDiagram2D
 * \brief Implements the 2-Dimensional Voronoi Diagram.
 *
 * Given a set of seed points, the Voronoi Diagram partitions the plane into
 * regions, each region is a collection of all pixels that is closest to one
 * particular seed point than to other seed points.
 * VoronoiDiagram2D is a mesh structure for storing the Voronoi Diagram,
 * can be Generated by itkVoronoiDiagram2DGenerator.
 *
 * Template parameters for VoronoiDiagram2D:
 *
 * TCoordType = The type associated with the coordniation of the seeds and
 * the resulting vertices.
 *
 * \ingroup MeshObjects
 * \ingroup ITKVoronoi
 */
template< typename TCoordType >
class ITKVoronoi_TEMPLATE_EXPORT VoronoiDiagram2D:
  public Mesh< TCoordType, 2,
               DefaultDynamicMeshTraits< TCoordType, 2, 2, TCoordType > >
{
public:
  /** Standard class typedefs. */
  typedef VoronoiDiagram2D                                                                Self;
  typedef Mesh< TCoordType, 2, DefaultDynamicMeshTraits< TCoordType, 2, 2, TCoordType > > Superclass;
  typedef SmartPointer< Self >                                                            Pointer;
  typedef SmartPointer< const Self >                                                      ConstPointer;

  /** Method for creation through the object factory. */
  itkNewMacro(Self);

  /** Standard part of every itk Object. */
  itkTypeMacro(VoronoiDiagram2D, Mesh);

  /** Define the mesh traits. */
  typedef DefaultDynamicMeshTraits< TCoordType, 2, 2, TCoordType > MeshTraits;

  /** Dimensions of the points and topology. */
  itkStaticConstMacro(PointDimension, unsigned int,
                      MeshTraits::PointDimension);
  itkStaticConstMacro(MaxTopologicalDimension, unsigned int,
                      MeshTraits::MaxTopologicalDimension);

  /** Typedefs from itkMesh */
  typedef typename MeshTraits::PixelType
                                          PixelType;
  typedef typename MeshTraits::CoordRepType
                                          CoordRepType;
  typedef typename MeshTraits::InterpolationWeightType
                                          InterpolationWeightType;
  typedef typename MeshTraits::PointIdentifier
                                          PointIdentifier;
  typedef typename MeshTraits::CellIdentifier
                                          CellIdentifier;
  typedef typename MeshTraits::CellFeatureIdentifier
                                          CellFeatureIdentifier;
  typedef typename MeshTraits::PointType
                                          PointType;
  typedef typename MeshTraits::PointsContainer
                                          PointsContainer;
  typedef typename MeshTraits::CellTraits
                                          CellTraits;
  typedef typename MeshTraits::CellsContainer
                                          CellsContainer;
  typedef typename MeshTraits::PointCellLinksContainer
                                          PointCellLinksContainer;
  typedef typename MeshTraits::CellLinksContainer
                                          CellLinksContainer;
  typedef typename MeshTraits::PointDataContainer
                                          PointDataContainer;
  typedef typename MeshTraits::CellDataContainer
                                          CellDataContainer;
  typedef typename MeshTraits::CellAutoPointer
                                          genericCellPointer;
  typedef BoundingBox< PointIdentifier, itkGetStaticConstMacro(PointDimension), CoordRepType,
                       PointsContainer >  BoundingBoxType;
  typedef typename PointsContainer::Pointer
                                          PointsContainerPointer;
  typedef typename CellsContainer::Pointer
                                          CellsContainerPointer;
  typedef typename CellLinksContainer::Pointer
                                          CellLinksContainerPointer;
  typedef typename PointDataContainer::Pointer
                                          PointDataContainerPointer;
  typedef typename CellDataContainer::Pointer
                                          CellDataContainerPointer;
  typedef typename BoundingBoxType::Pointer
                                          BoundingBoxPointer;
  typedef typename PointsContainer::ConstIterator
                                          PointsContainerConstIterator;
  typedef typename PointsContainer::Iterator
                                          PointsContainerIterator;
  typedef typename CellsContainer::ConstIterator
                                          CellsContainerConstIterator;
  typedef typename CellsContainer::Iterator
                                          CellsContainerIterator;
  typedef typename CellLinksContainer::ConstIterator
                                          CellLinksContainerIterator;
  typedef typename PointDataContainer::ConstIterator
                                          PointDataContainerIterator;
  typedef typename CellDataContainer::ConstIterator
                                          CellDataContainerIterator;
  typedef typename PointCellLinksContainer::const_iterator
                                          PointCellLinksContainerIterator;

  typedef CellFeatureIdentifier                       CellFeatureCount;
  typedef typename Superclass::CellType               CellType;
  typedef typename Superclass::CellAutoPointer        CellAutoPointer;
  typedef PolygonCell< CellType >                     PolygonCellType;
  typedef Point< int, 2 >                             EdgeInfo;
  typedef std::deque< EdgeInfo >                      EdgeInfoDQ;
  typedef typename CellType::MultiVisitor             CellMultiVisitorType;
  typedef std::vector< PointType >                    SeedsType;
  typedef typename SeedsType::iterator                SeedsIterator;
  typedef LineCell< CellType >                        Edge;
  typedef typename Edge::SelfAutoPointer              EdgeAutoPointer;
  typedef std::list< PointType >                      PointList;
  typedef std::vector< int >                          INTvector;
  typedef typename INTvector::iterator                NeighborIdIterator;
  typedef PointsContainerIterator                     VertexIterator;
  /** Get the number of Voronoi seeds. */
  itkGetConstMacro(NumberOfSeeds, unsigned int);

  /** Input the seeds information, will overwrite if seeds already
   * exists. */
  void SetSeeds(int num, SeedsIterator begin);

  /** The boundary that encloses the whole Voronoi diagram. */
  void SetBoundary(PointType vorsize);

  void SetOrigin(PointType vorsize);

  /** Iterators for the neighborhood cells around the given cell. */
  NeighborIdIterator NeighborIdsBegin(int seeds);

  NeighborIdIterator NeighborIdsEnd(int seeds);

  /** Iterators for all the vertices of the voronoi diagram. */
  VertexIterator VertexBegin();

  VertexIterator VertexEnd();

  /** Return the given indexed seed. */
  PointType GetSeed(int SeedID);

  /** Return the required cell pointer. */
  void GetCellId(CellIdentifier cellId, CellAutoPointer &);

  /** Return the given vertex of the voronoi diagram. */
  void GetPoint(int pId, PointType *answer);

  class VoronoiEdge
  {
public:
    PointType m_Left;
    PointType m_Right;
    int       m_LeftID;
    int       m_RightID;
    int       m_LineID;
    VoronoiEdge(){}
    ~VoronoiEdge(){}
  };

  /** The iterator for Voronoi edges, */
  typedef typename std::vector< VoronoiEdge >::iterator VoronoiEdgeIterator;

  /** The Iterator of all the edges for the Voronoi diagram. */
  VoronoiEdgeIterator EdgeBegin();

  VoronoiEdgeIterator EdgeEnd();

  /** Find the two seed point that around the given edge. */
  EdgeInfo GetSeedsIDAroundEdge(VoronoiEdge *task);

  /********************************************************/

  void Reset();

  void InsertCells();

  void AddCellNeighbor(EdgeInfo x)
  {
    m_CellNeighborsID[x[0]].push_back(x[1]);
    m_CellNeighborsID[x[1]].push_back(x[0]);
  }

  void ClearRegion(int i)
  {
    m_VoronoiRegions[i]->ClearPoints();
  }

  void VoronoiRegionAddPointId(int id, int x)
  {
    m_VoronoiRegions[id]->AddPointId(x);
  }

  void BuildEdge(int id)
  {
    m_VoronoiRegions[id]->BuildEdges();
  }

  void LineListClear()
  {
    m_LineList.clear();
  }

  void EdgeListClear()
  {
    m_EdgeList.clear();
  }

  void VertexListClear()
  {
    if ( this->m_PointsContainer.IsNull() )
      {
      this->m_PointsContainer = PointsContainer::New();
      }

    this->m_PointsContainer->Initialize();
  }

  int LineListSize()
  {
    return static_cast< int >( m_LineList.size() );
  }

  int EdgeListSize()
  {
    return static_cast< int >( m_EdgeList.size() );
  }

  int VertexListSize()
  {
    return static_cast< int >(this->m_PointsContainer->Size());
  }

  void AddLine(EdgeInfo x)
  {
    m_LineList.push_back(x);
  }

  void AddEdge(VoronoiEdge x)
  {
    m_EdgeList.push_back(x);
  }

  void AddVert(PointType x)
  {
    this->m_PointsContainer->InsertElement(this->m_PointsContainer->Size(), x);
  }

  EdgeInfo GetLine(int id)
  {
    return m_LineList[id];
  }

  VoronoiEdge GetEdge(int id)
  {
    return m_EdgeList[id];
  }

  PointType GetVertex(int id)
  {
    return this-> m_PointsContainer->ElementAt(id);
  }

  EdgeInfo GetEdgeEnd(int id)
  {
    EdgeInfo x;

    x[0] = m_EdgeList[id].m_LeftID;
    x[1] = m_EdgeList[id].m_RightID;
    return x;
  }

  int GetEdgeLineID(int id)
  {
    return m_EdgeList[id].m_LineID;
  }

protected:
  VoronoiDiagram2D();
  ~VoronoiDiagram2D();
  virtual void PrintSelf(std::ostream & os, Indent indent) const ITK_OVERRIDE;

private:
  ITK_DISALLOW_COPY_AND_ASSIGN(VoronoiDiagram2D);

  SeedsType                         m_Seeds;
  unsigned int                      m_NumberOfSeeds;
  std::vector< PolygonCellType * >  m_VoronoiRegions;
  PointType                         m_VoronoiBoundary;
  PointType                         m_VoronoiBoundaryOrigin;
  std::vector< std::vector< int > > m_CellNeighborsID;

  std::vector< EdgeInfo >    m_LineList;
  std::vector< VoronoiEdge > m_EdgeList;
};

} // end namespace itk

#ifndef ITK_MANUAL_INSTANTIATION
#include "itkVoronoiDiagram2D.hxx"
#endif

#endif
