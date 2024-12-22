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

#define dt_yogaPropertySimpleNoValue(name)                                               \
	auto name(float val) -> Element*;                                                    \
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
	auto Element::name(float val) -> Element*                                            \
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
		AddStyle<Styling::name>(val);                                                    \
		return this;                                                                     \
	}                                                                                    \
	auto Element::name() -> type                                                         \
	{                                                                                    \
		return GetStyle<Styling::name>()->GetValue();                                    \
	}

#define dt_yogaPropertyType(name, type)                                                  \
	auto name(type val) -> Element*;                                                     \
	auto name() -> type;

#define dt_yogaPropertyEdge(name)                                                        \
	auto name##Left(Styling::Value val)->Element*;                                       \
	auto name##Left()->float;                                                            \
	auto name##Right(Styling::Value val)->Element*;                                      \
	auto name##Right()->float;                                                           \
	auto name##Top(Styling::Value val)->Element*;                                        \
	auto name##Top()->float;                                                             \
	auto name##Bottom(Styling::Value val)->Element*;                                     \
	auto name##Bottom()->float;                                                          \
	auto name##Horizontal(Styling::Value val)->Element*;                                 \
	auto name##Horizontal()->float;                                                      \
	auto name##Vertical(Styling::Value val)->Element*;                                   \
	auto name##Vertical()->float;                                                        \
	auto name(Styling::Value val) -> Element*;                                           \
	auto name(Styling::Value top, Styling::Value left, Styling::Value bottom,            \
			  Styling::Value right) -> Element*;                                         \
	auto name() -> float;

#define dt_yogaPropertyEdgeNoValueDef(name)                                              \
	auto Element::name##Left(Styling::Value val)->Element*                               \
	{                                                                                    \
		auto style = GetStyle<Styling::name>()->GetValue();                              \
		AddStyle<Styling::name>(style.Y, style.Width, style.Height, val);                \
		return this;                                                                     \
	}                                                                                    \
	auto Element::name##Left()->float                                                    \
	{                                                                                    \
		return GetStyle<Styling::name>()->GetValue().X.Resolve(this);                    \
	}                                                                                    \
	auto Element::name##Right(Styling::Value val)->Element*                              \
	{                                                                                    \
		auto style = GetStyle<Styling::name>()->GetValue();                              \
		AddStyle<Styling::name>(style.Y, val, style.Height, style.X);                    \
		return this;                                                                     \
	}                                                                                    \
	auto Element::name##Right()->float                                                   \
	{                                                                                    \
		return GetStyle<Styling::name>()->GetValue().Width.Resolve(this);                \
	}                                                                                    \
	auto Element::name##Top(Styling::Value val)->Element*                                \
	{                                                                                    \
		auto style = GetStyle<Styling::name>()->GetValue();                              \
		AddStyle<Styling::name>(val, style.Width, style.Height, style.X);                \
		return this;                                                                     \
	}                                                                                    \
	auto Element::name##Top()->float                                                     \
	{                                                                                    \
		return GetStyle<Styling::name>()->GetValue().Y.Resolve(this);                    \
	}                                                                                    \
	auto Element::name##Bottom(Styling::Value val)->Element*                             \
	{                                                                                    \
		auto style = GetStyle<Styling::name>()->GetValue();                              \
		AddStyle<Styling::name>(style.Y, style.Width, val, style.X);                     \
		return this;                                                                     \
	}                                                                                    \
	auto Element::name##Bottom()->float                                                  \
	{                                                                                    \
		return GetStyle<Styling::name>()->GetValue().Height.Resolve(this);               \
	}                                                                                    \
	auto Element::name##Horizontal(Styling::Value val)->Element*                         \
	{                                                                                    \
		auto style = GetStyle<Styling::name>()->GetValue();                              \
		AddStyle<Styling::name>(style.Y, val, style.Height, val);                        \
		return this;                                                                     \
	}                                                                                    \
	auto Element::name##Horizontal()->float                                              \
	{                                                                                    \
		auto style = GetStyle<Styling::name>()->GetValue();                              \
		return style.X.Resolve(this) + style.Width.Resolve(this);                        \
	}                                                                                    \
	auto Element::name##Vertical(Styling::Value val)->Element*                           \
	{                                                                                    \
		auto style = GetStyle<Styling::name>()->GetValue();                              \
		AddStyle<Styling::name>(val, style.Width, val, style.X);                         \
		return this;                                                                     \
	}                                                                                    \
	auto Element::name##Vertical()->float                                                \
	{                                                                                    \
		auto style = GetStyle<Styling::name>()->GetValue();                              \
		return style.Y.Resolve(this) + style.Height.Resolve(this);                       \
	}                                                                                    \
	auto Element::name(Styling::Value val) -> Element*                                   \
	{                                                                                    \
		AddStyle<Styling::name>(val, val, val, val);                                     \
		return this;                                                                     \
	}                                                                                    \
	auto Element::name(Styling::Value top, Styling::Value right, Styling::Value bottom,  \
					   Styling::Value left) -> Element*                                  \
	{                                                                                    \
		AddStyle<Styling::name>(top, right, bottom, left);                               \
		return this;                                                                     \
	}                                                                                    \
	auto Element::name() -> float                                                        \
	{                                                                                    \
		auto style = GetStyle<Styling::name>()->GetValue();                              \
		return style.X.Resolve(this) + style.Y.Resolve(this) +                           \
			   style.Width.Resolve(this) + style.Height.Resolve(this);                   \
	}
