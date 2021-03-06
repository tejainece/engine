// Copyright 2016 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "flow/layers/shader_mask_layer.h"

namespace flow {

ShaderMaskLayer::ShaderMaskLayer() {
}

ShaderMaskLayer::~ShaderMaskLayer() {
}

void ShaderMaskLayer::Paint(PaintContext& context) {
  TRACE_EVENT0("flutter", "ShaderMaskLayer::Paint");
  SkAutoCanvasRestore save(&context.canvas, false);
  context.canvas.saveLayer(&paint_bounds(), nullptr);
  PaintChildren(context);

  SkPaint paint;
  paint.setXfermodeMode(transfer_mode_);
  paint.setShader(shader_);
  context.canvas.translate(mask_rect_.left(), mask_rect_.top());
  context.canvas.drawRect(
      SkRect::MakeWH(mask_rect_.width(), mask_rect_.height()), paint);
}

}  // namespace flow
