#pragma once
#include "modules/skshaper/include/SkShaper.h"
#include "core/Macros.h"

namespace Drift::Internals
{
	class dt_api TextRunLayoutHandler : public SkShaper::RunHandler
	{
	public:
		struct Line
		{
			float Width;
			float Height;
		};

		explicit TextRunLayoutHandler(float maxWidth, float lineHeight, float spacing)
			: _fMaxWidth(maxWidth), _fLineHeight(lineHeight), _fLetterSpacing(spacing)
		{
		}

		void beginLine() override
		{
			_currentLineWidth = 0;
		}

		void runInfo(const RunInfo& info) override
		{
		}

		void commitRunInfo() override
		{
		}

		void commitLine() override
		{
			Lines.push_back({_currentLineWidth, _fLineHeight});
			TotalHeight += _fLineHeight;
		}

		auto runBuffer(const RunInfo& info) -> Buffer override
		{
			_glyphs.resize(info.glyphCount);
			_positions.resize(info.glyphCount);
			_clusters.resize(info.glyphCount);

			return Buffer{
				_glyphs.data(),
				_positions.data(),
				nullptr,
				_clusters.data(),
			};
		}

		void commitRunBuffer(const RunInfo& info) override
		{
			for (size_t i = 0; i < info.glyphCount; ++i)
			{
				_currentLineWidth += _positions[i].x() + _fLetterSpacing;

				if (_currentLineWidth > _fMaxWidth)
				{
					commitLine();
					beginLine();
					_currentLineWidth = _positions[i].x();
				}
			}
		}

		std::vector<Line> Lines;
		float TotalHeight = 0;

	private:
		float _currentLineWidth = 0;
		float _fMaxWidth;
		float _fLineHeight;
        float _fLetterSpacing;
		std::vector<SkGlyphID> _glyphs;
		std::vector<SkPoint> _positions;
		std::vector<uint32_t> _clusters;
	};
}