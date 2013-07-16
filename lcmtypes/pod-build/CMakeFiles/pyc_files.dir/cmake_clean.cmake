FILE(REMOVE_RECURSE
  "../lcmtypes/c"
  "../lcmtypes/java"
  "../lcmtypes/python"
  "CMakeFiles/pyc_files"
  "../lcmtypes/python/lcmtypes/__init__.pyc"
  "../lcmtypes/python/lcmtypes/edge_t.pyc"
  "../lcmtypes/python/lcmtypes/environment_t.pyc"
  "../lcmtypes/python/lcmtypes/graph_t.pyc"
  "../lcmtypes/python/lcmtypes/region_3d_t.pyc"
  "../lcmtypes/python/lcmtypes/state_t.pyc"
  "../lcmtypes/python/lcmtypes/trajectory_t.pyc"
  "../lcmtypes/python/lcmtypes/vertex_t.pyc"
)

# Per-language clean rules from dependency scanning.
FOREACH(lang)
  INCLUDE(CMakeFiles/pyc_files.dir/cmake_clean_${lang}.cmake OPTIONAL)
ENDFOREACH(lang)
