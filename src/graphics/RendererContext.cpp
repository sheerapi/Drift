#include "graphics/RendererContext.h"
#include "core/Logger.h"
#include "gpu/ganesh/GrBackendSurface.h" // IWYU pragma: keep
#include "gpu/ganesh/SkSurfaceGanesh.h"
#include "gpu/ganesh/gl/GrGLBackendSurface.h"
#include "gpu/ganesh/gl/GrGLDirectContext.h"
#include "core/SkColorSpace.h" // IWYU pragma: keep
#include <GL/gl.h>

namespace Drift::Graphics
{
	RendererContext::RendererContext(int fbWidth, int fbHeight)
	{
		_width = fbWidth;
		_height = fbHeight;

		GLInterface = GrGLMakeNativeInterface();
		if (!GLInterface)
		{
			dt_coreError("Failed to create GLInterface instance!");
			return;
		}

		GrContext = GrDirectContexts::MakeGL(GLInterface);
		if (!GrContext)
		{
			dt_coreError("Failed to create GrContext instance!");
			return;
		}

		_fbInfo.fFBOID = 0;
		_fbInfo.fFormat = GL_RGBA8;

		RenderTarget = GrBackendRenderTargets::MakeGL(fbWidth, fbHeight, 0, 0, _fbInfo);

		SkSurfaceProps surfaceProps;
		Surface = SkSurfaces::WrapBackendRenderTarget(
			GrContext.get(), RenderTarget, kBottomLeft_GrSurfaceOrigin,
			kRGBA_8888_SkColorType, nullptr, &surfaceProps);

		if (!Surface)
		{
			dt_coreError("Failed to create SkSurface instance!");
			return;
		}

		Canvas = Surface->getCanvas();
	}

	void RendererContext::RefreshContext(int newWidth, int newHeight)
	{
		if (_width == newWidth && _height == newHeight)
		{
			return;
		}

		_width = newWidth;
		_height = newHeight;

		SkSurfaceProps surfaceProps;

		RenderTarget = GrBackendRenderTargets::MakeGL(_width, _height, 0, 0, _fbInfo);
		Surface = SkSurfaces::WrapBackendRenderTarget(
			GrContext.get(), RenderTarget, kBottomLeft_GrSurfaceOrigin,
			kRGBA_8888_SkColorType, nullptr, &surfaceProps);

        Canvas = Surface->getCanvas();
	}
}