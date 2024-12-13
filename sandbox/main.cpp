#include "components/Window.h"
#include "core/Application.h"
#include "core/LayoutEnums.h"

using namespace Drift;

auto main(int argc, const char** argv) -> int
{
	auto* app = new Application("com.drift.sandbox");

	auto window = app->AttachView<Window>("Sandbox", 800, 600);

	auto* root = window->GetCurrentActivity()
					 ->AttachRoot(std::make_shared<Element>())
					 ->FlexDirection(FlexDirection::Column)
					 ->Gap(20)
					 ->Padding(20);

	auto* container1 = root->AddChild<Element>()->Height(100)->Gap(10);
	container1->AddChild<Element>()->FlexGrow(1);
	container1->AddChild<Element>()->FlexGrow(1);
	container1->AddChild<Element>()->FlexGrow(1);

	auto* container2 = root->AddChild<Element>()->Height(200)->Gap(10);
	container2->AddChild<Element>()->FlexGrow(1);

	auto* container2_sub = container2->AddChild<Element>()
							   ->FlexGrow(2)
							   ->FlexDirection(FlexDirection::Column)
							   ->Gap(10);
	container2_sub->AddChild<Element>()->FlexGrow(1);
	container2_sub->AddChild<Element>()->FlexGrow(2);

	auto* container3 = root->AddChild<Element>()
						   ->Height(150)
						   ->AlignItems(AlignItems::Center)
						   ->JustifyContent(JustifyContent::SpaceBetween)
						   ->Padding(10);

	container3->AddChild<Element>()->Width(50)->Height(50);
	container3->AddChild<Element>()->Width(75)->Height(75);
	container3->AddChild<Element>()->Width(100)->Height(100);

	auto* container4 =
		root->AddChild<Element>()->FlexWrap(Wrap::Wrap)->Gap(10)->Height(200)->WidthPercent(100);

	for (size_t i = 0; i < 8; i++)
	{
		container4->AddChild<Element>()->HeightPercent(45)->FlexBasis(container4->GetPercentWidth(25)
	- 10);
	}

	Application::ForceGlobalLayoutRefresh();
	app->GetEventLoop()->PrintViewTree();

	return app->Present();
}