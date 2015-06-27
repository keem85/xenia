/**
 ******************************************************************************
 * Xenia : Xbox 360 Emulator Research Project                                 *
 ******************************************************************************
 * Copyright 2013 Ben Vanik. All rights reserved.                             *
 * Released under the BSD license - see LICENSE in the root for more details. *
 ******************************************************************************
 */

#ifndef XENIA_VFS_VIRTUAL_FILE_SYSTEM_H_
#define XENIA_VFS_VIRTUAL_FILE_SYSTEM_H_

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include "xenia/vfs/device.h"
#include "xenia/vfs/entry.h"

namespace xe {
namespace vfs {

class VirtualFileSystem {
 public:
  VirtualFileSystem();
  ~VirtualFileSystem();

  bool RegisterDevice(std::unique_ptr<Device> device);

  bool RegisterSymbolicLink(std::string path, std::string target);
  bool UnregisterSymbolicLink(std::string path);

  std::unique_ptr<Entry> ResolvePath(const std::string& path);
  X_STATUS Open(std::unique_ptr<Entry> entry, KernelState* kernel_state,
                Mode mode, bool async, XFile** out_file);

 private:
  std::vector<std::unique_ptr<Device>> devices_;
  std::unordered_map<std::string, std::string> symlinks_;
};

}  // namespace vfs
}  // namespace xe

#endif  // XENIA_VFS_VIRTUAL_FILE_SYSTEM_H_
