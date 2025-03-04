#!/usr/bin/env python

import sys
import os
sys.path.append("../../../../build_tools/scripts")
import base

base.configure_common_apps()

os.chdir("./common")

if not base.is_dir("./freetype-2.10.4"):
  base.download("https://netcologne.dl.sourceforge.net/project/freetype/freetype2/2.10.4/ft2104.zip", "./freetype-2.10.4.zip")
  base.extract("./freetype-2.10.4.zip", "./")
  base.delete_file("./freetype-2.10.4.zip")

# fetch harfbuzz
if not base.is_dir("harfbuzz"):
  base.cmd("git", ["clone", "https://github.com/harfbuzz/harfbuzz.git"])
  os.chdir("harfbuzz")
  base.cmd("git", ["checkout", "8d1b000a3edc90c12267b836b4ef3f81c0e53edc"])
  os.chdir("../")

  qmake_content_lines = []
  qmake_content_lines.append("CONFIG -= qt")
  qmake_content_lines.append("TARGET = harfbuzz")
  qmake_content_lines.append("TEMPLATE = lib")
  qmake_content_lines.append("CONFIG += staticlib")
  qmake_content_lines.append("")
  qmake_content_lines.append("CORE_ROOT_DIR = $$PWD/../../../../../core")
  qmake_content_lines.append("PWD_ROOT_DIR = $$PWD")
  qmake_content_lines.append("include($$CORE_ROOT_DIR/Common/base.pri)")
  qmake_content_lines.append("")
  qmake_content_lines.append("SRC_DIR = $$PWD/harfbuzz/src")
  qmake_content_lines.append("")

  qmake_content_lines.append("DEFINES += HAVE_FREETYPE")
  qmake_content_lines.append("FREETYPE_VERSION=2.10.4")
  qmake_content_lines.append("FREETYPE_PATH = $$PWD/freetype-$$FREETYPE_VERSION")
  qmake_content_lines.append("INCLUDEPATH += \\")
  qmake_content_lines.append("  $$FREETYPE_PATH/include \\")
  qmake_content_lines.append("  $$FREETYPE_PATH/include/freetype \\")
  qmake_content_lines.append("  $$FREETYPE_PATH/include/freetype/internal")

  qmake_content_lines.append("")
  qmake_content_lines.append("INCLUDEPATH += \\")
  qmake_content_lines.append("  $$SRC_DIR \\")
  qmake_content_lines.append("")

  all_files = os.listdir("./harfbuzz/src")
  headers_files = []
  sources_files = []

  headers_exclude = []

  sources_exclude = []
  sources_exclude.append("main.cc")
  sources_exclude.append("failing-alloc.c")

  for item in all_files:
    arr_split = os.path.splitext(item)
    if len(arr_split) == 0:
      continue
    ext = arr_split[-1]
    if (ext == ".h") or (ext == ".hh") or (ext == ".c") or (ext == ".cc"):
      if (0 == os.path.basename(item).find("test")):
        sources_exclude.append(item)

  for item in all_files:
    arr_split = os.path.splitext(item)
    if len(arr_split) == 0:
      continue
    ext = arr_split[-1]
    if (ext == ".h") or (ext == ".hh"):
      headers_files.append(item)
    if (ext == ".c") or (ext == ".cc"):
      sources_files.append(item)

  qmake_content_lines.append("HEADERS += \\")
  for item in headers_files:
    if item in headers_exclude:
      continue
    qmake_content_lines.append("  $$SRC_DIR/" + item + " \\")
  qmake_content_lines[-1] = qmake_content_lines[-1].replace(" \\", "")

  qmake_content_lines.append("")
  qmake_content_lines.append("SOURCES += \\")
  for item in sources_files:
    if item in sources_exclude:
      continue
    qmake_content_lines.append("  $$SRC_DIR/" + item + " \\")
  qmake_content_lines[-1] = qmake_content_lines[-1].replace(" \\", "")

  qmake_content_lines.append("")

  if len(headers_exclude) != 0:
    qmake_content_lines.append("#HEADERS += \\")
    for item in headers_exclude:
      qmake_content_lines.append("#  $$SRC_DIR/" + item + " \\")
    qmake_content_lines[-1] = qmake_content_lines[-1].replace(" \\", "")
    qmake_content_lines.append("")

  if len(sources_exclude) != 0:
    qmake_content_lines.append("#SOURCES += \\")
    for item in sources_exclude:
      qmake_content_lines.append("#  $$SRC_DIR/" + item + " \\")
    qmake_content_lines[-1] = qmake_content_lines[-1].replace(" \\", "")
    qmake_content_lines.append("")
  else:
    qmake_content_lines.append("")

  if (base.is_file("./harfbuzz.pri")):
    base.delete_file("./harfbuzz.pri")

  with open("./harfbuzz.pri", "w") as file:
    file.write("\n".join(qmake_content_lines))

  if (base.is_file("./harfbuzz.pro")):
    base.delete_file("./harfbuzz.pro")

  with open("./harfbuzz.pro", "w") as file:
    file.write("\n".join(qmake_content_lines))

os.chdir("../")