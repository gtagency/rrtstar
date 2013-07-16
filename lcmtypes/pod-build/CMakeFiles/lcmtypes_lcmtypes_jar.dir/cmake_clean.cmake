FILE(REMOVE_RECURSE
  "../lcmtypes/c"
  "../lcmtypes/java"
  "../lcmtypes/python"
  "CMakeFiles/lcmtypes_lcmtypes_jar"
  "lcmtypes_lcmtypes.jar"
  "../lcmtypes/java/lcmtypes/edge_t.class"
  "../lcmtypes/java/lcmtypes/environment_t.class"
  "../lcmtypes/java/lcmtypes/graph_t.class"
  "../lcmtypes/java/lcmtypes/region_3d_t.class"
  "../lcmtypes/java/lcmtypes/state_t.class"
  "../lcmtypes/java/lcmtypes/trajectory_t.class"
  "../lcmtypes/java/lcmtypes/vertex_t.class"
)

# Per-language clean rules from dependency scanning.
FOREACH(lang)
  INCLUDE(CMakeFiles/lcmtypes_lcmtypes_jar.dir/cmake_clean_${lang}.cmake OPTIONAL)
ENDFOREACH(lang)
