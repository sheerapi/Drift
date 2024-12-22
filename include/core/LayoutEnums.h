#pragma once

namespace Drift
{
    enum class Align
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

    enum class Direction
    {
		Column,
		ColumnReverse,
		Row,
		RowReverse
	};

    enum class Justify
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

    enum class WrapType
    {
		NoWrap,
		Wrap,
		WrapReverse
	};

    enum class OverflowType
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

	enum class BoxSizingType
	{
		BorderBox,
		ContentBox
	};
}