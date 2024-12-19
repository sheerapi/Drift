#include "components/Window.h"
#include "core/Application.h"
#include "core/LayoutEnums.h"
#include "events/InputSystem.h"
#include "events/ShortcutManager.h"

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
		auto row = panel->AddChild<Element>()->WidthPercent(100)->FlexGrow(1)->FlexDirection(
			FlexDirection::Row)->ReceivesInput(false)->Gap(5)->JustifyContent(JustifyContent::SpaceBetween);

		for (int y = 0; y < (i == 4 ? 3 : 4); y++)
		{
			auto btn = row->AddChild<Element>()->HeightPercent(100)->FlexGrow(1);

			btn->On("unclick", [](auto event) { dt_info("H"); });

			if (i == 4 && y == 2)
			{
				btn->WidthPercent(25.5);
			}
		}
	}

	Application::ForceGlobalLayoutRefresh();
	app->GetEventLoop()->PrintViewTree();

	return app->Present();
}