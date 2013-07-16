FILE(REMOVE_RECURSE
  "../lcmtypes/c"
  "../lcmtypes/java"
  "../lcmtypes/python"
  "CMakeFiles/lcmgen_java"
)

# Per-language clean rules from dependency scanning.
FOREACH(lang)
  INCLUDE(CMakeFiles/lcmgen_java.dir/cmake_clean_${lang}.cmake OPTIONAL)
ENDFOREACH(lang)
