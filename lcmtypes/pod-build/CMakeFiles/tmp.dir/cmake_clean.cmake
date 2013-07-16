FILE(REMOVE_RECURSE
  "../lcmtypes/c"
  "../lcmtypes/java"
  "../lcmtypes/python"
  "CMakeFiles/tmp"
)

# Per-language clean rules from dependency scanning.
FOREACH(lang)
  INCLUDE(CMakeFiles/tmp.dir/cmake_clean_${lang}.cmake OPTIONAL)
ENDFOREACH(lang)
