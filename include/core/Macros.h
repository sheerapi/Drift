#pragma once

#define dt_verboseFlag Drift::Application::main->GetEnvironmentInfo().Verbose

#if defined _WIN32 || defined __CYGWIN__
#	ifdef DT_IMPORT
#		ifdef __GNUC__
#			define dt_api __attribute__((dllimport))
#		else
#			define dt_api                                                               \
				__declspec(dllimport) // Note: actually gcc seems to also supports this
									  // syntax.
#		endif
#	else
#		ifdef __GNUC__
#			define dt_api __attribute__((dllexport))
#		else
#			define dt_api                                                               \
				__declspec(dllexport) // Note: actually gcc seems to also supports this
									  // syntax.
#		endif
#	endif
#	define dt_apiLocal
#else
#	if __GNUC__ >= 4
#		define dt_api __attribute__((visibility("default")))
#		define dt_apiLocal __attribute__((visibility("hidden")))
#	else
#		define dt_api
#		define dt_apiLocal
#	endif
#endif

// forgive me for what ur abt to see ryt now lolol

#define dt_yogaPropertySimple(name)                                                      \
	auto name(Styling::Value val) -> Element*;                                           \
	auto name() -> float;

#define dt_yogaPropertySimpleNoValue(name)                                                      \
	auto name(float val) -> Element*;                                           \
	auto name() -> float;

#define dt_yogaPropertyValueDef(name)                                                    \
	auto Element::name(Styling::Value val) -> Element*                                   \
	{                                                                                    \
		AddStyle<Styling::name>(val);                                                    \
		return this;                                                                     \
	}                                                                                    \
	auto Element::name() -> float                                                        \
	{                                                                                    \
		return GetStyle<Styling::name>()->GetValue();                                    \
	}

#define dt_yogaPropertySimpleDef(name)                                                   \
	auto Element::name(float val) -> Element*                                   \
	{                                                                                    \
		AddStyle<Styling::name>(val);                                                    \
		return this;                                                                     \
	}                                                                                    \
	auto Element::name() -> float                                                        \
	{                                                                                    \
		return GetStyle<Styling::name>()->GetValue();                                    \
	}

#define dt_yogaPropertyEnumDef(name, type, ygType)                                       \
	auto Element::name(type val) -> Element*                                             \
	{                                                                                    \
		YGNodeStyleSet##name(_ygNode, (ygType)((int)val));                               \
		return this;                                                                     \
	}                                                                                    \
	auto Element::name() -> type                                                         \
	{                                                                                    \
		return (type)((int)YGNodeStyleGet##name(_ygNode));                               \
	}

#define dt_yogaPropertyType(name, type)                                                  \
	auto name(type val) -> Element*;                                                     \
	auto name() -> type;

#define dt_yogaPropertyEdge(name)                                                        \
	auto name##Left(float val)->Element*;                                                \
	auto name##Left()->float;                                                            \
	auto name##Right(float val)->Element*;                                               \
	auto name##Right()->float;                                                           \
	auto name##Top(float val)->Element*;                                                 \
	auto name##Top()->float;                                                             \
	auto name##Bottom(float val)->Element*;                                              \
	auto name##Bottom()->float;                                                          \
	auto name##Horizontal(float val)->Element*;                                          \
	auto name##Horizontal()->float;                                                      \
	auto name##Vertical(float val)->Element*;                                            \
	auto name##Vertical()->float;                                                        \
	auto name(float val) -> Element*;                                                    \
	auto name() -> float;

#define dt_yogaPropertyEdgeDef(name)                                                     \
	auto Element::name##Left(float val)->Element*                                        \
	{                                                                                    \
		YGNodeStyleSet##name(_ygNode, YGEdge::YGEdgeLeft, val);                          \
		return this;                                                                     \
	}                                                                                    \
	auto Element::name##Left()->float                                                    \
	{                                                                                    \
		return YGNodeStyleGet##name(_ygNode, YGEdge::YGEdgeLeft).value;                  \
	}                                                                                    \
	auto Element::name##Right(float val)->Element*                                       \
	{                                                                                    \
		YGNodeStyleSet##name(_ygNode, YGEdge::YGEdgeRight, val);                         \
		return this;                                                                     \
	}                                                                                    \
	auto Element::name##Right()->float                                                   \
	{                                                                                    \
		return YGNodeStyleGet##name(_ygNode, YGEdge::YGEdgeRight).value;                 \
	}                                                                                    \
	auto Element::name##Top(float val)->Element*                                         \
	{                                                                                    \
		YGNodeStyleSet##name(_ygNode, YGEdge::YGEdgeTop, val);                           \
		return this;                                                                     \
	}                                                                                    \
	auto Element::name##Top()->float                                                     \
	{                                                                                    \
		return YGNodeStyleGet##name(_ygNode, YGEdge::YGEdgeLeft).value;                  \
	}                                                                                    \
	auto Element::name##Bottom(float val)->Element*                                      \
	{                                                                                    \
		YGNodeStyleSet##name(_ygNode, YGEdge::YGEdgeBottom, val);                        \
		return this;                                                                     \
	}                                                                                    \
	auto Element::name##Bottom()->float                                                  \
	{                                                                                    \
		return YGNodeStyleGet##name(_ygNode, YGEdge::YGEdgeBottom).value;                \
	}                                                                                    \
	auto Element::name##Horizontal(float val)->Element*                                  \
	{                                                                                    \
		YGNodeStyleSet##name(_ygNode, YGEdge::YGEdgeHorizontal, val);                    \
		return this;                                                                     \
	}                                                                                    \
	auto Element::name##Horizontal()->float                                              \
	{                                                                                    \
		return YGNodeStyleGet##name(_ygNode, YGEdge::YGEdgeHorizontal).value;            \
	}                                                                                    \
	auto Element::name##Vertical(float val)->Element*                                    \
	{                                                                                    \
		YGNodeStyleSet##name(_ygNode, YGEdge::YGEdgeVertical, val);                      \
		return this;                                                                     \
	}                                                                                    \
	auto Element::name##Vertical()->float                                                \
	{                                                                                    \
		return YGNodeStyleGet##name(_ygNode, YGEdge::YGEdgeVertical).value;              \
	}                                                                                    \
	auto Element::name(float val) -> Element*                                            \
	{                                                                                    \
		YGNodeStyleSet##name(_ygNode, YGEdge::YGEdgeAll, val);                           \
		return this;                                                                     \
	}                                                                                    \
	auto Element::name() -> float                                                        \
	{                                                                                    \
		return YGNodeStyleGet##name(_ygNode, YGEdge::YGEdgeAll).value;                   \
	}

#define dt_yogaPropertyEdgeNoValueDef(name)                                              \
	auto Element::name##Left(float val)->Element*                                        \
	{                                                                                    \
		YGNodeStyleSet##name(_ygNode, YGEdge::YGEdgeLeft, val);                          \
		return this;                                                                     \
	}                                                                                    \
	auto Element::name##Left()->float                                                    \
	{                                                                                    \
		return YGNodeLayoutGet##name(_ygNode, YGEdge::YGEdgeLeft);                       \
	}                                                                                    \
	auto Element::name##Right(float val)->Element*                                       \
	{                                                                                    \
		YGNodeStyleSet##name(_ygNode, YGEdge::YGEdgeRight, val);                         \
		return this;                                                                     \
	}                                                                                    \
	auto Element::name##Right()->float                                                   \
	{                                                                                    \
		return YGNodeLayoutGet##name(_ygNode, YGEdge::YGEdgeRight);                      \
	}                                                                                    \
	auto Element::name##Top(float val)->Element*                                         \
	{                                                                                    \
		YGNodeStyleSet##name(_ygNode, YGEdge::YGEdgeTop, val);                           \
		return this;                                                                     \
	}                                                                                    \
	auto Element::name##Top()->float                                                     \
	{                                                                                    \
		return YGNodeLayoutGet##name(_ygNode, YGEdge::YGEdgeLeft);                       \
	}                                                                                    \
	auto Element::name##Bottom(float val)->Element*                                      \
	{                                                                                    \
		YGNodeStyleSet##name(_ygNode, YGEdge::YGEdgeBottom, val);                        \
		return this;                                                                     \
	}                                                                                    \
	auto Element::name##Bottom()->float                                                  \
	{                                                                                    \
		return YGNodeLayoutGet##name(_ygNode, YGEdge::YGEdgeBottom);                     \
	}                                                                                    \
	auto Element::name##Horizontal(float val)->Element*                                  \
	{                                                                                    \
		YGNodeStyleSet##name(_ygNode, YGEdge::YGEdgeHorizontal, val);                    \
		return this;                                                                     \
	}                                                                                    \
	auto Element::name##Horizontal()->float                                              \
	{                                                                                    \
		return YGNodeLayoutGet##name(_ygNode, YGEdge::YGEdgeHorizontal);                 \
	}                                                                                    \
	auto Element::name##Vertical(float val)->Element*                                    \
	{                                                                                    \
		YGNodeStyleSet##name(_ygNode, YGEdge::YGEdgeVertical, val);                      \
		return this;                                                                     \
	}                                                                                    \
	auto Element::name##Vertical()->float                                                \
	{                                                                                    \
		return YGNodeLayoutGet##name(_ygNode, YGEdge::YGEdgeVertical);                   \
	}                                                                                    \
	auto Element::name(float val) -> Element*                                            \
	{                                                                                    \
		YGNodeStyleSet##name(_ygNode, YGEdge::YGEdgeAll, val);                           \
		return this;                                                                     \
	}                                                                                    \
	auto Element::name() -> float                                                        \
	{                                                                                    \
		return YGNodeLayoutGet##name(_ygNode, YGEdge::YGEdgeAll);                        \
	}
