#ifndef _chi_volumemesher_h
#define _chi_volumemesher_h

#include "../chi_mesh.h"
#include "../Cell/cell.h"

#define VOLUMEMESHER_LINEMESH1D 1
#define VOLUMEMESHER_PREDEFINED2D 3
#define VOLUMEMESHER_EXTRUDER 4

struct chi_mesh::CellIndexMap
{
  int mapped_from;
  int mapped_to;
  int mapped_level;

  CellIndexMap()
  {
    mapped_from  = -1;
    mapped_to    = -1;
    mapped_level = -1;
  }
  CellIndexMap(int from,int to)
  {
    mapped_from  = from;
    mapped_to    = to;
    mapped_level = -1;
  }
};

//######################################################### Class def
/**Parent volume mesher class.*/
class chi_mesh::VolumeMesher
{
private:
  std::vector<double> zcuts;

public:
  struct VOLUME_MESHER_OPTIONS
  {
    bool force_polygons;
    bool mesh_global;
    int  partition_z;

    VOLUME_MESHER_OPTIONS()
    {
      force_polygons = true;
      mesh_global = false;
      partition_z = 1;
    }
  };
  VOLUME_MESHER_OPTIONS options;
public:
  std::vector<chi_mesh::CellIndexMap*> cell_ordering;
  std::vector<chi_mesh::NodeIndexMap*> node_ordering;
  std::vector<int>                     reverse_node_ordering;
public:
  //01 Utils
  void                CreatePolygonCells(chi_mesh::SurfaceMesh* surface_mesh,
                                         chi_mesh::MeshContinuum* vol_continuum,
                                         bool delete_surface_mesh_elements=false,
                                         bool force_local=false);
  std::pair<int,int>  GetCellXYPartitionID(chi_mesh::Cell *cell);
  std::tuple<int,int,int>
                      GetCellXYZPartitionID(chi_mesh::Cell *cell);
  void                GetBoundaryCells(chi_mesh::MeshContinuum* vol_continuum);
  void                SetMatIDFromLogical(chi_mesh::LogicalVolume* log_vol,
                                          bool sense, int mat_id);
  void                SetBndryIDFromLogical(chi_mesh::LogicalVolume* log_vol,
                                          bool sense, int bndry_id);
  //02
  virtual void Execute();
  int          MapNode(int iref);
  int          ReverseMapNode(int i);
  

};

#endif