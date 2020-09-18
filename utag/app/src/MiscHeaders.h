#pragma once

#include <vector>
#include <iostream>
#include <iomanip>
#include <stdio.h>
#include <regex>
#include <string>
#include <map>

#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>

#if defined(__cplusplus) && __cplusplus >= 201703L && defined(__has_include)
#if __has_include(<filesystem>)
#define GHC_USE_STD_FS
#include <filesystem>
namespace fs = std::filesystem;
#endif
#endif
#ifndef GHC_USE_STD_FS
#include <ghc/filesystem.hpp>
namespace fs = ghc::filesystem;
#endif

// TAGLIB
#include <tag.h>
#include <fileref.h>
#include <tpropertymap.h>
#include <tlist.h>
#include <tfile.h>
