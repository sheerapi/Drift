#pragma once

namespace Drift
{
    enum class AlignItems
    {
		Auto,
		FlexStart,
		Center,
		FlexEnd,
		Stretch,
		Baseline,
		SpaceBetween,
		SpaceAround,
		SpaceEvenly
	};

    enum class FlexDirection
    {
		Column,
		ColumnReverse,
		Row,
		RowReverse
	};

    enum class JustifyContent
    {
		Start,
		Center,
		End,
		SpaceBetween,
		SpaceAround,
		SpaceEvenly
	};

    enum class PositionType
    {
		Static,
		Relative,
		Absolute
	};

    enum class Wrap
    {
		NoWrap,
		Wrap,
		WrapReverse
	};

    enum class Overflow
    {
		Visible,
		Hidden,
		Scroll
	};

    enum class DisplayType
    {
		Flex,
		None,
		Contents
	};

	enum class NodeType
	{
		Default,
		Text
	};
}