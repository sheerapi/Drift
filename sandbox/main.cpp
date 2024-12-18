#include "components/Window.h"
#include "core/Application.h"
#include "core/LayoutEnums.h"
#include "utils/Vector2.h"

using namespace Drift;

auto main(int argc, const char** argv) -> int
{
	auto* app = new Application("com.drift.sandbox");

	auto window = app->AttachView<Window>("Sandbox");

	auto* root = window->GetCurrentActivity()
					 ->AttachRoot(std::make_shared<Element>())
					 ->FlexDirection(FlexDirection::Column)
					 ->JustifyContent(JustifyContent::SpaceBetween)
					 ->ReceivesInput(false);

	auto* container1 = root->AddChild<Element>()
						   ->HeightPercent(100)
						   ->FlexShrink(1)
						   ->Padding(20)
						   ->FlexDirection(FlexDirection::Row)
						   ->ReceivesInput(false);

	auto* container1_sub1 = container1->AddChild<Element>()
								->FlexGrow(1)
								->Padding(20)
								->FlexDirection(FlexDirection::Column)
								->Gap(20)
								->ReceivesInput(false)
								->Overflow(Overflow::Hidden);
								
	for (int i = 0; i < 24; i++)
	{
		container1_sub1->AddChild<Element>()->Height(120)->WidthPercent(100);
	}

	auto* container1_sub = container1->AddChild<Element>()
							   ->FlexGrow(1)
							   ->FlexDirection(FlexDirection::Column)
							   ->MarginLeft(20)
							   ->Gap(20)
							   ->ReceivesInput(false);

	container1_sub->AddChild<Element>()->FlexGrow(1);
	container1_sub->AddChild<Element>()->FlexGrow(2);

	auto* container2 = root->AddChild<Element>()
						   ->Height(48)
						   ->JustifyContent(JustifyContent::SpaceBetween)
						   ->AlignItems(AlignItems::Center)
						   ->PaddingHorizontal(16)
						   ->ReceivesInput(false);

	for (size_t i = 0; i < 5; i++)
	{
		container2->AddChild<Element>()->Width(24)->Height(24);
	}

	return app->Present();
}