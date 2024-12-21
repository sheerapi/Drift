#include "components/Window.h"
#include "core/Application.h"
#include "core/LayoutEnums.h"
#include "styles/RenderingStyles.h"
#include "styles/Style.h"

using namespace Drift;

auto main(int argc, const char** argv) -> int
{
	auto* app = new Application("com.drift.sandbox");

	auto window = app->AttachView<Window>("Sandbox");

	auto* root = window->GetCurrentActivity()
					 ->AttachRoot(std::make_shared<Element>())
					 ->FlexDirection(FlexDirection::Column)
					 ->JustifyContent(JustifyContent::SpaceBetween);

	auto* result = root->AddChild<Element>()
					   ->ReceivesInput(false)
					   ->Padding(4)
					   ->HeightPercent(30)
					   ->FlexGrow(0)
					   ->FlexShrink(0);

	auto* panel = root->AddChild<Element>()
					  ->FlexGrow(1)
					  ->FlexShrink(1)
					  ->Padding(10)
					  ->FlexDirection(FlexDirection::Column)
					  ->FlexBasisPercent(0)
					  ->ReceivesInput(false)
					  ->Gap(5)
					  ->FlexWrap(Drift::Wrap::Wrap);

	for (int i = 0; i < 5; i++)
	{
		auto* row = panel->AddChild<Element>()->WidthPercent(100)->FlexGrow(1)->FlexDirection(
			FlexDirection::Row)->ReceivesInput(false)->Gap(5)->JustifyContent(JustifyContent::SpaceBetween);

		for (int idx = 0; idx < (i == 4 ? 3 : 4); idx++)
		{
			auto* btn = row->AddChild<Element>()->HeightPercent(100)->FlexGrow(1);

			if (i == 4 && idx == 2)
			{
				btn->WidthPercent(25.5);
			}
		}
	}

	result->AddStyle<Styling::BackgroundColor>(Color::FromHex(0x282828));

	result->On("click", [result](auto event){
		result->AddStyle<Styling::BackgroundColor>(Color::RandomColor());
	});

	result->On("unclick", [result](auto event){
		result->AddStyle<Styling::BackgroundColor>(Color::FromHex(0x282828));
	});

	return app->Present();
}