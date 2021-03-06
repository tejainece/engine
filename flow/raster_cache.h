// Copyright 2016 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef FLOW_RASTER_CACHE_H_
#define FLOW_RASTER_CACHE_H_

#include <memory>
#include <unordered_map>

#include "base/macros.h"
#include "skia/ext/refptr.h"
#include "third_party/skia/include/core/SkSize.h"
#include "third_party/skia/include/core/SkImage.h"
#include "flow/instrumentation.h"

namespace flow {

class RasterCache {
 public:
  RasterCache();
  ~RasterCache();

  sk_sp<SkImage> GetPrerolledImage(
      GrContext* context, SkPicture* picture, const SkMatrix& ctm);
  void SweepAfterFrame();

  void Clear();

 private:
  struct Entry {
    Entry();
    ~Entry();

    bool used_this_frame = false;
    int access_count = 0;
    SkISize physical_size;
    sk_sp<SkImage> image;
  };

  using Cache = std::unordered_map<uint32_t, Entry>;
  Cache cache_;

  DISALLOW_COPY_AND_ASSIGN(RasterCache);
};

}  // namespace flow

#endif  // FLOW_RASTER_CACHE_H_
