#pragma once
#include "core/Logger.h"
#include "core/SkCanvas.h"
#include "core/SkSurface.h"
#include "gpu/ganesh/GrBackendSurface.h"
#include "gpu/ganesh/gl/GrGLInterface.h"
#include "gpu/ganesh/GrDirectContext.h"
#include <memory>

namespace Drift::Graphics
{
    class RendererContext
    {
    public:
		inline static std::shared_ptr<RendererContext> main{nullptr};

		SkCanvas* Canvas;
		sk_sp<const GrGLInterface> GLInterface;
		sk_sp<GrDirectContext> GrContext;
		sk_sp<SkSurface> Surface;
		GrBackendRenderTarget RenderTarget;

		RendererContext(int fbWidth, int fbHeight);
		void RefreshContext(int newWidth, int newHeight);

    private:
        int _width;
        int _height;

		GrGLFramebufferInfo _fbInfo;
	};
}

#define dt_renderContext Drift::Graphics::RendererContext::main
#define dt_canvas Drift::Graphics::RendererContext::main->Canvas